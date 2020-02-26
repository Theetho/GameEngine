#include "EnginePch.h"
#include "GUIElement.h"
#include "Renderer/Buffer.h"
#include "Renderer/Texture/Texture2D.h"
#include "Renderer/Rendering/RenderCommand.h"
#include "Renderer/Rendering/RendererAPI.h"
#include "API/OpenGL/Shader.h"

namespace Engine
{
	/*	OPENGL system :
	 * -1,1 ___ 1,1
	 *	 |		 |
	 *   |  0,0  |
	 *   |       |
	 * -1,-1___ 1,-1
	 */


	Ref<VertexArray> GUIElement::sVertexArray = nullptr;

	GUIElement::GUIElement(const Vec2& position, const Vec2& scale, Ref<Texture2D> texture)
		: mTransform(Vec3(position.x, position.y, 0.f), Vec3(0.f, 0.f, 0.f), Vec3(scale.x, scale.y, 0.0))
		, mTexture(texture)
	{
		if (!sVertexArray)
		{
			sVertexArray = VertexArray::Create();
			float vertices[] = { -1.f, 1.f, -1.f, -1.f, 1.f, 1.f, 1.f, -1.f };
			auto vbo = VertexBuffer::Create(vertices, 8);
			vbo->SetLayout({
				BufferElement(ShaderDataType::Float2, "inPosition")
			});
			sVertexArray->AddVertexBuffer(vbo);
			// vec2((inPosition.x + 1.0) / 2.0, 1 - (inPosition.y + 1.0) / 2.0)
			Vertex2D v1, v2, v3, v4;
			v1.position = { -1.f, 1.f }; v2.position = { -1.f, -1.f }; v3.position = { 1.f, 1.f }; v4.position = { 1.f, -1.f };
			v1.position *= scale; v2.position *= scale; v3.position *= scale; v4.position *= scale;
			v1.position += position; v2.position += position; v3.position += position; v4.position += position;
			v1.texture_coordinates = { 0.f, 0.f }; v2.texture_coordinates = { 0.f, 1.f }; v3.texture_coordinates = { 1.f, 0.f }; v4.texture_coordinates = { 1.f, 1.f };
			v1.color = Color::White; v2.color = Color::White; v3.color = Color::White; v4.color = Color::White;
			if (texture)
			{
				v1.texture_id = texture->GetId(); v2.texture_id = texture->GetId(); v3.texture_id = texture->GetId(); v4.texture_id = texture->GetId();
				_mTextures.push_back(texture);
			}
			_mVertices.push_back(v1); _mVertices.push_back(v2); _mVertices.push_back(v3), _mVertices.push_back(v4);
			_mIndices.push_back(0);
			_mIndices.push_back(1);
			_mIndices.push_back(2);
			_mIndices.push_back(2);
			_mIndices.push_back(1);
			_mIndices.push_back(3);
		}
	}
	
	GUIElement::~GUIElement()
	{
	}

	void GUIElement::SetTexture(Ref<Texture2D> texture)
	{
		mTexture = texture;
		_mTextures.clear();
		_mTextures.push_back(texture);
		for (auto& vertex : _mVertices)
		{
			vertex.texture_id = texture->GetId();
		}
	}

	/*void GUIElement::Render(Ref<RenderCommand> render_command, Ref<Shader> shader) const
	{
		if (render_command->GetAPI() == API::OpenGL)
		{
			render_command->SetDrawMode(DrawMode::TRIANGLE_STRIP);
			auto ogl_shader = std::dynamic_pointer_cast<OpenGL::Shader>(shader);
			ogl_shader->UploadUniform("uModel", mTransform.GetModel());
			if (mTexture)
			{
				ogl_shader->UploadUniform("uTexture", 0);
				mTexture->Bind();
			}
		}

		Renderable::Render(sVertexArray, render_command, shader);

		if (render_command->GetAPI() == API::OpenGL)
		{
			render_command->SetDrawMode(DrawMode::TRIANGLES);
		}
	}*/
}