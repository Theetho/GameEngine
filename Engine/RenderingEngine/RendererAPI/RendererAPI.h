#pragma once

namespace Engine
{
	class VertexArray;

	enum class API { None, OpenGL, DirectX, Vulkan };
	enum class DrawMode { DEFAULT, TRIANGLES, TRIANGLE_STRIP, PATCHES };

	class CRendererAPI
	{
	public:
		// Return the rendering API of the engine
		static API GetAPI();
		// Return the renderer depending on the API
		static Ref<CRendererAPI> Get();
		// Set the draw mode
		void SetDrawMode(DrawMode draw_mode);

		/// Abstract methods
		// Clear the screen or framebuffer binds to the rendering API
		virtual void Clear() const = 0;
		// Make a draw call to the GPU with the data in the vertex array
		virtual void Draw(VertexArray* vertex_array) const = 0;
		virtual void Draw(Ref<VertexArray> vertex_array) const = 0;
		// Set the clear color
		virtual void SetClearColor(const Color& color) const = 0;
		// Set the viewport dimensions
		virtual void SetViewport(unsigned int width, unsigned int height) const = 0;
		// Retrieve the max texture units that can be bound together
		virtual int GetMaxTextureUnits() const = 0;
	protected:
		/// Abstract methods
		// Return the draw mode depending on the API
		virtual unsigned int GetDrawMode() const = 0;
		DrawMode mDrawMode;
		static API sApi;
		static Ref<CRendererAPI> sInstance;
	};
}

