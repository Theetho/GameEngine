#pragma once

#include "Export.h"
#include "Maths/Vec2.h"
#include "Event.h"
#include "GraphicsContext.h"

namespace Engine
{
	class Window
	{
	public:
		using EventCallbackFunction = std::function<void(Event&)>;

		struct WindowData
		{
			std::string				title;
			unsigned int			width;
			unsigned int			height;
			EventCallbackFunction	eventCallback;

			WindowData(
				const std::string& title = "Engine Window",
				const unsigned int& width = 1280,
				const unsigned int& height = 720
			)
				: title(title)
				, width(width)
				, height(height)
			{}
		};
		Window();
		virtual ~Window();

		virtual void  onUpdate(const double& delta) = 0;
		virtual void  resize(const unsigned int& width, const unsigned int& height) = 0;
		
		virtual void* getOSWindow() = 0;

		inline void			setEventCallback(const EventCallbackFunction& eventCallback)
		{
			m_data.eventCallback = eventCallback;
		}
		inline unsigned int getWidth() const
		{
			return m_data.width;
		}
		inline unsigned int getHeight() const
		{
			return m_data.height;
		}
		inline std::string	getTitle() const
		{
			return m_data.title;
		}

		static Window* create(const WindowData& windowData = WindowData());
	protected:
		WindowData	m_data;

		static bool s_GLFWInitialized;
	};

	class WindowWindows : public Window
	{
	public:
		WindowWindows(const WindowData& windowData);
		~WindowWindows();

		void  onUpdate(const double& delta) override;
		void  resize(const unsigned int& width, const unsigned int& height);

		inline void* getOSWindow() { return m_window; }

	private:
		GLFWwindow*			m_window;
		GraphicsContext*	m_context;

		void initialize(const WindowData& windowData);
		void shutdown();
		void setCallbacks();
	};
}

