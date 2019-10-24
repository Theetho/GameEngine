#include "EnginePch.h"
#include "Application.h"
#include "Log.h"

#define bind_function(x) std::bind(&x, this, std::placeholders::_1)
#define FPS_CAP 60.0
#ifdef ENGINE_WINDOWS
	#define get_engine_time glfwGetTime()
#endif // ENGINE_WINDOWS


namespace Engine
{
	Application* Application::s_instance = nullptr;

	Application::Application()
		: m_layerStack()
	{
		ENGINE_ASSERT(!s_instance, "Application already created");
		s_instance = this;

		m_window = std::unique_ptr<Window>(Window::create());
		m_window->setEventCallback(
			bind_function(Application::onEvent)
		);

		// VAO
		m_vao.reset(VertexArray::create());

		// VBO
		float vertices[7 * 3] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			 0.0f,  0.5f, 0.0f,	0.0f, 0.0f, 1.0f, 1.0f
		};

		std::shared_ptr<VertexBuffer> vbo;
		vbo.reset(VertexBuffer::create(vertices, sizeof(vertices)));

		vbo->setLayout({
			{ ShaderDataType::Float3, "in_position" },
			{ ShaderDataType::Float4, "in_color" }
		});

		m_vao->addVertexBuffer(vbo);

		// IBO
		unsigned int indices[3]{
			0, 1, 2
		};

		std::shared_ptr<IndexBuffer> ibo;
		ibo.reset(IndexBuffer::create(indices, sizeof(indices) / sizeof(unsigned int)));

		m_vao->addIndexBuffer(ibo);

		m_squareVao.reset(VertexArray::create());

		float squareVertices[7 * 4] = {
			-0.75f, -0.75f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			 0.75f, -0.75f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			 0.75f,  0.75f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			-0.75f,  0.75f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f
		};

		std::shared_ptr<VertexBuffer> squareVbo;
		squareVbo.reset(VertexBuffer::create(squareVertices, sizeof(squareVertices)));

		squareVbo->setLayout({
			{ ShaderDataType::Float3, "in_position" },
			{ ShaderDataType::Float4, "in_color" }
		});

		m_squareVao->addVertexBuffer(squareVbo);

		unsigned int squareIndices[6]{
			0, 1, 2,
			2, 3, 0
		};

		std::shared_ptr<IndexBuffer> squareIbo;
		squareIbo.reset(IndexBuffer::create(squareIndices, sizeof(squareIndices) / sizeof(unsigned int)));

		m_squareVao->addIndexBuffer(squareIbo);

		std::string vertex = R"(
			#version 330 core

			layout(location = 0) in vec3 in_position;
			layout(location = 1) in vec4 in_color;

			out vec4 v_color;

			void main()
			{
				gl_Position = vec4(in_position, 1.0);
				v_color = in_color;
			}
		)";
		std::string fragment = R"(
			#version 330 core

			layout(location = 0) out vec4 out_color;
			in vec4 v_color;

			void main()
			{
				out_color = v_color;
			}
		)";

		m_shader.reset(Shader::create(vertex, fragment));
	}

	Application::~Application()
	{
	}
	void Application::run()
	{
		while (m_running)
		{
			glClearColor(0.7f, 1.f, 0.7f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			m_shader->bind();
			m_squareVao->bind();
			glDrawElements(GL_TRIANGLES, m_squareVao->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);
			m_vao->bind();
			glDrawElements(GL_TRIANGLES, m_vao->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);

			// TO CHANGE
			m_deltaTime = std::max(get_engine_time - m_time, (1.0 / FPS_CAP));
			m_time = get_engine_time;

			m_window->onUpdate(m_deltaTime);

			for (Layer* layer : m_layerStack)
			{
				layer->onUpdate(m_deltaTime);
			}
		}
	}
	void Application::onEvent(Event& event)
	{
		if (event.type == Event::Type::Closed || Input::isKeyPressed(GLFW_KEY_ESCAPE))
		{
			m_running = false;
			event.hasBeenHandled();
		}
		else if (event.type == Event::Type::Resized)
		{
			m_window->resize(event.sizeEvent.width, event.sizeEvent.height);
			glViewport(0, 0, event.sizeEvent.width, event.sizeEvent.height);
			event.hasBeenHandled();
		}
		else
		{
			for (auto layer = m_layerStack.end(); layer != m_layerStack.begin() && !event.isHandled(); --layer)
			{
				(*layer)->onEvent(event);
			}
		}
	}
	void Application::pushLayer(Layer* layer)
	{
		m_layerStack.push(layer);
	}
	void Application::popLayer()
	{
		m_layerStack.pop();
	}
}