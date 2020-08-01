#pragma once

#include "Component.h"

namespace Engine 
{
	template <int dimension>
	class GameObject;
	class Color;
	class Texture2D;

	class Sprite : public Component2D
	{
	public:
		Sprite(GameObject<2>& game_object, Ref<Texture2D> texture = nullptr);
		Sprite(GameObject<2>& game_object, const Color& color = Color::White);
		~Sprite();

		inline void SetColor(const Color& color) {
			mColor = color;
		}
		inline void SetTexture(Ref<Texture2D> texture) {
			mTexture = texture;
		}
		
		inline const Color& GetColor() const {
			return mColor;
		}
		inline Ref<Texture2D> GetTexture() const {
			return mTexture;
		}
	private:
		Color mColor;
		Ref<Texture2D> mTexture;

		// Hérité via Component
		virtual void OnUiRender() override;
		virtual void OnUpdate(const double& delta) override;
	};
}