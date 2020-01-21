#include "EnginePch.h"
#include "Water.h"
#include "Core/Application.h"
#include "Core/Window.h"
#include "Core/Camera3D.h"
#include "Renderer/Buffer.h"
#include "Renderer/Rendering.h"
#include "API/OpenGL/OpenGLShader.h"
#include "API/OpenGL/OpenGLFrameBuffer.h"
#include "API/OpenGL/OpenGLTexture2D.h"

#define REFLECTION_WIDTH  640
#define REFLECTION_HEIGHT 360
#define REFRACTION_WIDTH  1280
#define REFRACTION_HEIGHT 720
#define WAVE_SPEED 0.03

namespace Engine
{
	Water::Water(const Vec3& position, const Vec2& dimensions)
		: GameObject(Transform(position + Vec3(dimensions.x / 2.0f, 0.0f, dimensions.y / 2.0f), Vec3(0.0f), Vec3(dimensions.x / 2.0f, 0.0f, dimensions.y / 2.0f)))
		, mWaveMovement(0.0f)
	{
		this->CreateTile();
		mRefraction = FrameBuffer::Create(REFRACTION_WIDTH, REFRACTION_HEIGHT);
		mReflection = FrameBuffer::Create(REFLECTION_WIDTH, REFLECTION_HEIGHT);
		mDUDVMap	= Texture2D::Create("Water/dudvmap.png", "water_dudv");
		mNormalMap	= Texture2D::Create("Water/normalmap.png", "water_normal");
	}
	
	Water::~Water()
	{}

	void Water::OnUpdate(const double& delta)
	{
		mWaveMovement += WAVE_SPEED * delta;
		if (mWaveMovement > 1.0f)
			mWaveMovement -= 1.0f;
	}

	Ref<FrameBuffer> Water::GetRefractionBuffer() const
	{
		return mRefraction;
	}

	Ref<FrameBuffer> Water::GetReflectionBuffer() const
	{
		return mReflection;
	}

	const Vec3& Water::GetPosition() const
	{
		return mTransform.GetPosition();
	}
	
	void Water::CreateTile()
	{
		mVertexArray = VertexArray::Create();
		
		std::vector<float> vertices = { -1, -1, -1, 1, 1, -1, 1, -1, -1, 1, 1, 1 };


		auto vertex_buffer = VertexBuffer::Create(vertices.data(), vertices.size());

		vertex_buffer->SetLayout(BufferLayout({
			BufferElement(ShaderDataType::Float2, "inPosition"),
		}));

		mVertexArray->AddVertexBuffer(vertex_buffer);
	}

	void Water::Prepare(Camera3D& camera)
	{
		if (Renderer::GetAPI() == API::OpenGL)
		{
			glEnable(GL_CLIP_DISTANCE0);
		}


		// Refraction
		Renderer::sSceneData.cliping_plane = Vec4(0, -1, 0, mTransform.GetPosition().y);
		mRefraction->Bind();
		RenderCommand::Clear();
		Renderer::Render(true);
		mRefraction->Unbind();
		
		camera.ReverseOnUpAxis(mTransform.GetPosition());
		
		// Reflection
		Renderer::sSceneData.cliping_plane = Vec4(0, 1, 0, -mTransform.GetPosition().y);
		mReflection->Bind();
		RenderCommand::Clear();
		Renderer::Render(true);
		mReflection->Unbind();

		camera.ReverseOnUpAxis(mTransform.GetPosition());

		if (Renderer::GetAPI() == API::OpenGL)
		{
			glDisable(GL_CLIP_DISTANCE0);
		}
	}

	void Water::Render(Ref<RenderCommand> render_command, Ref<Shader> shader) const
	{
		GameObject::Render(render_command, shader);

		if (render_command->GetAPI() == API::OpenGL)
		{
			auto ogl_shader = std::dynamic_pointer_cast<OpenGLShader>(shader);
			ogl_shader->UploadUniform("uReflection", 0);
			ogl_shader->UploadUniform("uRefraction", 1);
			ogl_shader->UploadUniform("uDUDVMap"   , 2);
			ogl_shader->UploadUniform("uNormalMap" , 3);
			ogl_shader->UploadUniform("uWaveMovement", mWaveMovement);
			mReflection->GetTextureAttachment()->Bind(0);
			mRefraction->GetTextureAttachment()->Bind(1);
			mDUDVMap  ->Bind(2);
			mNormalMap->Bind(3);
		}

		Renderable::Render(mVertexArray, render_command, shader);
	}

}