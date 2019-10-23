#pragma once

#include "Export.h"
#include "Window.h"
#include "LayerStack.h"
#include "Input.h"
#include "Shader.h"
#include "Buffer.h"
#include "VertexArray.h"

namespace Engine
{
	class ENGINE_API Application
	{
	public:
		Application();
		virtual ~Application();

		static Application& get() { return *s_instance; }

		void run();
		void onEvent(Event& event);
		void pushLayer(Layer* layer);
		void popLayer();

		inline Window& getWindow() { return *m_window; }
	private:
		std::unique_ptr<Window> m_window;
		std::shared_ptr<Shader>	m_shader;
		std::shared_ptr<VertexArray>  m_vao;
		std::shared_ptr<VertexArray>  m_squareVao;

		bool					m_running = true;
		LayerStack				m_layerStack;
		double					m_time = 0.0, m_deltaTime = 0.0;
	private:
		static Application* s_instance;
	};

	// Has to be define by the game
	Application* createApplication();
}