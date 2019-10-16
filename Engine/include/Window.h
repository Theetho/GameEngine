#pragma once

#include "Export.h"
#include "Maths/Vec2.h"
#include "Event.h"

namespace Engine
{
	class ENGINE_API Window
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
			{
			}
		};
		virtual ~Window();

		virtual void onUpdate(const double& delta) = 0;

		inline unsigned int getWidth() const
		{
			return m_data.width;
		}
		inline unsigned int getHeight() const
		{
			return m_data.height;
		}
		inline std::string getTitle() const
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

		void onUpdate(const double& delta) override;

	private:
		GLFWwindow* m_window;

		void initialize(const WindowData& windowData);
		void shutdown();
	};
}

