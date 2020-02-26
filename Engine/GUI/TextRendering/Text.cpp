#include "EnginePch.h"
#include "Renderer/Buffer.h"
#include "Renderer/Rendering.h"
#include "Renderer/Texture/Texture2D.h"
#include "API/OpenGL/Shader.h"
#include "Text.h"
#include "Font.h"

namespace Engine
{
	Font* Text::sFont = nullptr;

	Text::Text()
		: mLabel("")
		, mPosition()
		, mColor(Color::White)
		, mVertexArray(nullptr)
	{
	}

	Text::Text(const std::string& label, const Vec2& position, const Color& color)
		: mLabel(label)
		, mPosition(position.x, position.y, 0.0f)
		, mColor(color)
		, mVertexArray(nullptr)
	{
		this->InitializeVertices();
	}

	Text::Text(const Text& other)
		: CRenderable(other)
		, mLabel(other.mLabel)
		, mPosition(other.mPosition)
		, mColor(other.mColor)
		, mVertexArray(other.mVertexArray)
	{}

	Text::Text(const Text&& other)
		: CRenderable(other)
		, mLabel(other.mLabel)
		, mPosition(other.mPosition)
		, mColor(other.mColor)
		, mVertexArray(other.mVertexArray)
	{}

	Text& Text::operator=(const Text & other)
	{
		_mVertices = other._mVertices;
		_mIndices = other._mIndices;
		_mTextures = other._mTextures;
		mLabel = other.mLabel;
		mPosition = other.mPosition;
		mColor = other.mColor;
		mVertexArray = other.mVertexArray;
		return *this;
	}

	Text& Text::operator=(const Text&& other)
	{
		_mVertices = other._mVertices;
		_mIndices = other._mIndices;
		_mTextures = other._mTextures;
		mLabel = other.mLabel;
		mPosition = other.mPosition;
		mColor = other.mColor;
		mVertexArray = other.mVertexArray;
		return *this;
	}

	void Text::SetGlobalFont(Font* font)
	{
		sFont = font;
	}

	void Text::InitializeVertices()
	{
		if (!sFont)
			return;

		if (!mVertexArray)
			mVertexArray = VertexArray::Create();
		else
			mVertexArray.reset();

		_mTextures.push_back(sFont->GetTextureAtlas());

		std::vector<float> vertices;
		const Vec2& scale = sFont->GetScale();
		float x = mPosition.x;

		for (int i = 0; i < mLabel.size(); ++i)
		{
			auto glyph = ftgl::texture_font_get_glyph(sFont->GetFTFont(), &mLabel[i]);

			if (!glyph)
				continue;

			if (i > 0)
			{
				float kerning = texture_glyph_get_kerning(glyph, &mLabel[i - 1]);
				x += kerning / scale.x;
			}
			
			float x0 = x + (float)glyph->offset_x / scale.x;
			float y0 = mPosition.y + (float)glyph->offset_y / scale.y;
			float x1 = x0 + (float)glyph->width / scale.x;
			float y1 = y0 - (float)glyph->height / scale.y;

			// Top Left vertice
			this->AddVertice(vertices, x0, y0, glyph->s0, glyph->t0);
			// Bottom Left
			this->AddVertice(vertices, x0, y1, glyph->s0, glyph->t1);
			// Top Right
			this->AddVertice(vertices, x1, y1, glyph->s1, glyph->t1);
			// Bottom Right
			this->AddVertice(vertices, x1, y0, glyph->s1, glyph->t0);

			x += glyph->advance_x / scale.x;
		}

		auto vbo = VertexBuffer::Create(vertices.data(), vertices.size());
		vbo->SetLayout(BufferLayout{
			BufferElement(ShaderDataType::Float2, "inPosition"),
			BufferElement(ShaderDataType::Float2, "inTextureCoords"),
			BufferElement(ShaderDataType::Float3, "inColor"),
		});
		mVertexArray->AddVertexBuffer(vbo);

		std::vector<unsigned int> indices;
		for (unsigned int i = 0; i < mLabel.size(); ++i)
		{
			indices.push_back(0 + i * 4);
			indices.push_back(1 + i * 4);
			indices.push_back(2 + i * 4);
			indices.push_back(2 + i * 4);
			indices.push_back(3 + i * 4);
			indices.push_back(0 + i * 4);

			_mIndices.push_back(0 + i * 4);
			_mIndices.push_back(1 + i * 4);
			_mIndices.push_back(2 + i * 4);
			_mIndices.push_back(2 + i * 4);
			_mIndices.push_back(3 + i * 4);
			_mIndices.push_back(0 + i * 4);
		}
		auto ibo = IndexBuffer::Create(indices.data(), indices.size());
		mVertexArray->AddIndexBuffer(ibo);
	}

	void Text::AddVertice(std::vector<float>& vertices, float x, float y, float u, float v)
	{
		vertices.push_back(x);
		vertices.push_back(y);
		vertices.push_back(u);
		vertices.push_back(v);
		vertices.push_back(mColor.r);
		vertices.push_back(mColor.g);
		vertices.push_back(mColor.b);

		Vertex2D vertex;
		vertex.position			   = { x, y };
		vertex.texture_coordinates = { u, v };
		vertex.color			   = mColor;
		vertex.texture_id		   = sFont->GetTextureAtlas()->GetId();
		_mVertices.push_back(vertex);
	}

	/*void Text::Render(Ref<RenderCommand> render_command, Ref<Shader> shader) const
	{
		if (!sFont)
			return;

		if (render_command->GetAPI() == API::OpenGL)
		{
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			auto ogl_shader = std::dynamic_pointer_cast<OpenGL::Shader>(shader);
			ogl_shader->UploadUniform("uFontAtlas", 0);
			sFont->GetTextureAtlas()->Bind();
		}

		Renderable::Render(mVertexArray, render_command, shader);

		if (render_command->GetAPI() == API::OpenGL)
		{
			glDisable(GL_BLEND);
		}
	}*/
}
