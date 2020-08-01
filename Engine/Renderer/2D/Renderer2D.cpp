#include "EnginePch.h"
#include "Renderer2D.h"
#include "Component/Sprite.h"
#include "GameObject/GameObject.h"
#include "Renderer/Texture/Texture2D.h"
#include "Renderer/Rendering/RenderCommand.h"
#include "Component/Transform.h"
#include "Renderer/Buffer.h"
#include "Renderer/Shader.h"
#include "Core/AssetManager.h"
#include "Core/Camera/Camera2D.h"

namespace Engine 
{
	Renderer2D::Renderer2D()
	{
		mBuffers.vao = VertexArray::Create();

		mBuffers.vbo = VertexBuffer::Create(nullptr, MAX_VERTICES_PER_BATCH * SIZE_OF_VERTEX, Engine::BufferUsage::DYNAMIC);
		mBuffers.vbo->SetLayout({
			BufferElement(ShaderDataType::Float2, "inPosition"),
			BufferElement(ShaderDataType::Float2, "inTextureCoords"),
			BufferElement(ShaderDataType::Float4, "inColor"),
			BufferElement(ShaderDataType::Float,  "inTextureID"),
		});
		mBuffers.vao->AddVertexBuffer(mBuffers.vbo);

		float offset = 0.0f; std::vector<uint> indices;
		for (uint i = 0; i < MAX_INDICES_PER_BATCH; i += 6) {
			indices.push_back(offset + 0);
			indices.push_back(offset + 1);
			indices.push_back(offset + 2);
			indices.push_back(offset + 2);
			indices.push_back(offset + 3);
			indices.push_back(offset + 0);

			offset += 4;
		}
		mBuffers.ibo = IndexBuffer::Create(indices.data(), indices.size());
		mBuffers.vao->AddIndexBuffer(mBuffers.ibo);

		mShader = AssetManager::GetShaderLibrary().Load("../Sandbox/Assets/Shaders/basic2D_32tex.glsl", "2D", false);
		mShader->Bind();
		for (int i = 0; i < mTextures.size(); ++i) {
			mShader->UploadUniform("uTextures[" + std::to_string(i) + "]", i);
		}

		mVertices.reserve(MAX_VERTICES_PER_BATCH * ELEMENT_PER_VERTEX);
	}

	Renderer2D::~Renderer2D()
	{
	}

	void Renderer2D::Submit(GameObject2D* game_object)
	{
		auto sprite = game_object->GetComponent<Sprite>();
		if (!sprite) return;

		auto transform = game_object->GetComponent<Transform2D>();//game_object->GetTransform();

		mBatch.push_back(game_object);

		if (mVertices.size() >= MAX_VERTICES_PER_BATCH * ELEMENT_PER_VERTEX) {
			this->End();
		}

		this->_SetVertices(sprite, transform);
	}

	void Renderer2D::Submit(Ref<GameObject2D> game_object)
	{
		Submit(game_object.get());
	}

	void Renderer2D::Begin(const Camera2D& camera)
	{
		mShader->Bind();
		mShader->UploadUniform("uVP", camera.GetProjectionViewMatrix());
	}

	void Renderer2D::End()
	{
		mBuffers.vbo->SetData(mVertices);
		
		mShader->Bind();
		uint i = 0;
		while (i < mTextures.size() && mTextures[i]) {
			mTextures[i]->Bind(i);
			++i;
		}
		
		mBuffers.vao->Bind();
		RenderCommand::Draw(mBuffers.vao, mIndiceCount);

		mBatch.clear();
		std::fill(mTextures.begin(), mTextures.end(), nullptr);
		mTextureIndex = 0;
		mIndiceCount = 0;
		mVertexIndex = 0;
		mTextures[mTextureIndex++] = Texture2D::GetWhiteTexture();
		mVertices.clear();
	}

	void Renderer2D::_PushVertex(const Vec2& position, const Vec2& uv, const Color& color, uint texture_id)
	{
		mVertices.push_back(position.x);
		mVertices.push_back(position.y);
		mVertices.push_back(uv.x);
		mVertices.push_back(uv.y);
		mVertices.push_back(color.r);
		mVertices.push_back(color.g);
		mVertices.push_back(color.b);
		mVertices.push_back(color.a);
		mVertices.push_back(texture_id);
		// mVertices[mVertexIndex++] = position.x;
		// mVertices[mVertexIndex++] = position.y;
		// mVertices[mVertexIndex++] = uv.x;
		// mVertices[mVertexIndex++] = uv.y;
		// mVertices[mVertexIndex++] = color.r;
		// mVertices[mVertexIndex++] = color.g;
		// mVertices[mVertexIndex++] = color.b;
		// mVertices[mVertexIndex++] = color.a;
		// mVertices[mVertexIndex++] = texture_id;
	}

	void Renderer2D::_SetVertices(Ref<Sprite> sprite, Ref<Transform2D> transform)
	{
		Mat4 transform_matrix = transform->GetModel();
		
		Color color = Color::White;
		float texture_id = 0.0f;
		
		if (sprite->GetTexture()) {
			for (size_t i = 0; i < mTextureIndex; ++i) {
				if (mTextures[i]->GetId() != sprite->GetTexture()->GetId()) continue;

				// Here, the sprite's texture is already stored in the renderer
				texture_id = i;
			}
			// Here the texture is not stored yet
			if (texture_id == 0.0f) {
				texture_id = mTextureIndex;
				mTextures[mTextureIndex++] = sprite->GetTexture();
			}
		}
		color = sprite->GetColor();
		
		std::array<float, 8> positions = {
			 0.0f, -1.0f,
			 1.0f, -1.0f,
			 1.0f, 0.0f,
			 0.0f, 0.0f,
		};

		const Vec2& position = transform->GetPosition();
		const Vec2& size = transform->GetScale();

		this->_PushVertex({ -1 + position.x, -1 + position.y }, { 0.0f, 0.0f }, color, texture_id);
		this->_PushVertex({ -1 + position.x + size.x, -1 + position.y }, { 1.0f, 0.0f }, color, texture_id);
		this->_PushVertex({ -1 + position.x + size.x, -1 + position.y + size.y }, { 1.0f, 1.0f }, color, texture_id);
		this->_PushVertex({ -1 + position.x, -1 + position.y + size.y }, { 0.0f, 1.0f }, color, texture_id);

		mIndiceCount += 6;
	}
}