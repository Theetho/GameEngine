#pragma once

#include "Export.h"
#include <SFML/Window.hpp>

namespace Engine
{
	class ENGINE_API Window
	{
		sf::Window m_window;

		void create();

	public:
		Window();
		~Window();

		inline sf::Window& get()
		{
			return this->m_window;
		}
		inline void resize(const unsigned int& w, const unsigned int& h)
		{
			this->m_window.setSize(sf::Vector2u(w, h));
		}
		inline bool isOpen()
		{
			return this->m_window.isOpen();
		}
		inline void close()
		{
			this->m_window.close();
		}
	};
}

