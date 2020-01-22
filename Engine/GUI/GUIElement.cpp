#include "EnginePch.h"
#include "GUIElement.h"
#include "Renderer/Buffer.h"
#include "Renderer/Texture/Texture2D.h"
#include "Renderer/Rendering/RenderCommand.h"
#include "Renderer/Rendering/RendererAPI.h"
#include "API/OpenGL/OpenGLShader.h"

namespace Engine
{
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
				BufferElement(ShaderDataType::Float2, "in_position")
			});
			sVertexArray->AddVertexBuffer(vbo);
		}
	}
	
	GUIElement::~GUIElement()
	{
	}

	void GUIElement::Render(Ref<RenderCommand> render_command, Ref<Shader> shader) const
	{
		if (render_command->GetAPI() == API::OpenGL)
		{
			render_command->SetDrawMode(DrawMode::TRIANGLE_STRIP);
			auto ogl_shader = std::dynamic_pointer_cast<OpenGLShader>(shader);
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
			render_command->SetDrawMode(DrawMode::TRIANGLE);
		}
	}
}