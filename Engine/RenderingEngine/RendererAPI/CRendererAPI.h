#pragma once

namespace Engine
{
	class VertexArray;

	enum class CAPI { None, OpenGL, DirectX, Vulkan };
	enum class CDrawMode { DEFAULT, TRIANGLES, TRIANGLE_STRIP, PATCHES };

	class CRendererAPI
	{
	public:
		// Return the rendering API of the engine
		static CAPI _GetAPI();
		// Return the renderer depending on the API
		static Ref<CRendererAPI> _Get();
		// Set the draw mode
		void _SetDrawMode(CDrawMode draw_mode);

		/// Abstract methods
		// Clear the screen or framebuffer binds to the rendering API
		virtual void _Clear() const = 0;
		// Make a draw call to the GPU with the data in the vertex array
		virtual void _Draw(VertexArray* vertex_array) const = 0;
		virtual void _Draw(Ref<VertexArray> vertex_array) const = 0;
		// Set the clear color
		virtual void _SetClearColor(const Color& color) const = 0;
		// Set the viewport dimensions
		virtual void _SetViewport(unsigned int width, unsigned int height) const = 0;
		// Retrieve the max texture units that can be bound together
		virtual int _GetMaxTextureUnits() const = 0;
	protected:
		/// Abstract methods
		// Return the draw mode depending on the API
		virtual unsigned int _GetDrawMode() const = 0;
		CDrawMode _mDrawMode;
		static CAPI _sApi;
		static Ref<CRendererAPI> _sInstance;
	};
}

