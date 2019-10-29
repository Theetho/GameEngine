#include "pch.h"
#include "TheChernoLayer.h"

TheChernoLayer::TheChernoLayer()
 : m_camera()
{
}

TheChernoLayer::~TheChernoLayer()
{
}

void TheChernoLayer::onAttach()
{
	// Triangle
	// VAO
	m_vao.reset(Engine::VertexArray::create());

	// VBO
	float vertices[7 * 3] = {
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
		 0.0f,  0.5f, 0.0f,	0.0f, 0.0f, 1.0f, 1.0f
	};

	Engine::Ref<Engine::VertexBuffer> vbo;
	vbo.reset(Engine::VertexBuffer::create(vertices, sizeof(vertices)));

	vbo->setLayout({
		{ Engine::ShaderDataType::Float3, "in_position" },
		{ Engine::ShaderDataType::Float4, "in_color" }
	});

	m_vao->addVertexBuffer(vbo);

	// IBO
	unsigned int indices[3]{
		0, 1, 2
	};

	Engine::Ref<Engine::IndexBuffer> ibo;
	ibo.reset(Engine::IndexBuffer::create(indices, sizeof(indices) / sizeof(unsigned int)));

	m_vao->addIndexBuffer(ibo);

	// Square

	m_squareVao.reset(Engine::VertexArray::create());

	float squareVertices[7 * 4] = {
		-0.75f, -0.75f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		 0.75f, -0.75f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
		 0.75f,  0.75f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		-0.75f,  0.75f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f
	};

	Engine::Ref<Engine::VertexBuffer> squareVbo;
	squareVbo.reset(Engine::VertexBuffer::create(squareVertices, sizeof(squareVertices)));

	squareVbo->setLayout({
		{ Engine::ShaderDataType::Float3, "in_position" },
		{ Engine::ShaderDataType::Float4, "in_color" }
		});

	m_squareVao->addVertexBuffer(squareVbo);

	unsigned int squareIndices[6]{
		0, 1, 2,
		2, 3, 0
	};

	Engine::Ref<Engine::IndexBuffer> squareIbo;
	squareIbo.reset(Engine::IndexBuffer::create(squareIndices, sizeof(squareIndices) / sizeof(unsigned int)));

	m_squareVao->addIndexBuffer(squareIbo);

	// Shader
	m_shader.reset(Engine::Shader::create("1stV.glsl", "1stF.glsl"));

	Engine::RenderCommand::setClearColor(Engine::Color::Teal);
	Engine::Input::toggleCursor();
}

void TheChernoLayer::onDetach()
{
}

void TheChernoLayer::onUpdate(const double& delta)
{
	m_camera.onUpdate(delta);

	// --- Rendering ---
	Engine::RenderCommand::clear();

	Engine::Renderer::beginScene(m_camera);

	Engine::Renderer::submit(m_shader, m_squareVao);
	Engine::Renderer::submit(m_shader, m_vao);

	Engine::Renderer::endScene();
	// -----------------
}

void TheChernoLayer::onEvent(Engine::Event& event)
{
	m_camera.onEvent(event);
}
