#pragma once

#include "Renderer/GraphicsContext.h"

namespace Engine
{
	namespace OpenGL
	{
		class Context : public Engine::GraphicsContext
		{
		public:

			#ifdef ENGINE_WINDOWS
			Context(GLFWwindow* window);
			#endif

			~Context();

			void Initialize() override;
			void SwapBuffers() override;
			std::string GetAPIVersion() const override;

		private:
			GLFWwindow* mWindow;
		};
	}
}