#pragma once

#include "Renderer/Rendering/Renderable.h"
#include "GameObject/Transform.h"

namespace Engine
{
	class VertexArray;
	class Texture2D;

	class GUIElement : public Renderable
	{
	public:
		GUIElement(const Vec2& position, const Vec2& scale, Ref<Texture2D> texture = nullptr);
		~GUIElement();
	private:
		Transform	   mTransform;
		Ref<Texture2D> mTexture;
		static Ref<VertexArray> sVertexArray;

		void Render(Ref<RenderCommand> render_command, Ref<Shader> shader) const override;
	};
}
