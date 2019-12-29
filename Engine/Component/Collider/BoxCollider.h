#pragma once

#include "Collider.h"

namespace Engine
{
	class BoxCollider : public Collider
	{
	public:
		BoxCollider(GameObject& game_object, const Vec3& center, const Vec3& bounds);
		BoxCollider(const BoxCollider& box_collider);
		BoxCollider(const BoxCollider&& box_collider) noexcept;
		BoxCollider& operator=(const BoxCollider& box_collider);
		BoxCollider& operator=(const BoxCollider&& box_collider) noexcept;
		~BoxCollider();

		void OnUpdate(const double& delta) override;

		const Vec3& GetMax() const override;
		const Vec3& GetMin() const override;

		void SetScale(const Vec3& scale);
		void SetScale(float scale);
	private:
		float mWidth, mHeight, mDepth;
		// Top Right Front point (width, height, depth) / 2
		Vec3  mMaxExtent;
		// Bottom Left Back point (-width, -height, -depth) / 2
		Vec3  mMinExtent;

		void Render(Ref<RenderCommand> render_command, Ref<Shader> shader) const override;
	};
}