#pragma once

namespace Engine
{
	class Event;
	class GraphicsContext;

	class Window
	{
	public:
		using EventCallbackFunction = std::function<void(Event&)>;
		struct WindowData
		{
			std::string				title;
			unsigned int			width;
			unsigned int			height;
			EventCallbackFunction	event_callback;

			WindowData(
				const std::string& title = "Engine Window",
				unsigned int width = WindowData::GetDefaultWidth(),
				unsigned int height = WindowData::GetDefaultHeight()
			)
				: title(title)
				, width(width)
				, height(height)
			{}

			static inline unsigned int GetDefaultWidth()
			{
				return 1280;
			}
			static inline unsigned int GetDefaultHeight()
			{
				return 720;
			}
		};

		Window();
		virtual ~Window();

		static Window* Create(const WindowData& window_data = WindowData());
		
		virtual void OnUpdate(const double& delta) = 0;
		virtual void Resize(unsigned int width, unsigned int height) = 0;
		
		virtual void*			   GetOSWindow() = 0;
		virtual unsigned int	   GetWidth() const;
		virtual unsigned int	   GetHeight() const;
		virtual const std::string& GetTitle() const;
		
		virtual void SetFullscreen(bool fullscreen) = 0;
		virtual void SetEventCallback(const EventCallbackFunction& event_callback);
	protected:
		WindowData	mData;
	};

	// Windows window

	class WindowWindows : public Window
	{
	public:
		WindowWindows(const WindowData& window_data);
		~WindowWindows();

		void OnUpdate(const double& delta) override;
		void Resize(unsigned int width, unsigned int height);

		void SetFullscreen(bool set);

		void* GetOSWindow();
	private:
		GLFWwindow*		 mWindow;
		GraphicsContext* mContext;
		static bool		 sGLFWInitialized;

		void Initialize(const WindowData& window_data);
		void Shutdown();
		
		void SetCallbacks();
	};
}

