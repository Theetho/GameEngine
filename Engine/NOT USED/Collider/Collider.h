#pragma once

#include "Component/Component.h"
#include "Renderer/Rendering/Renderable.h"

namespace Engine
{
	class RigidBody;
	
	class Collider : public Component, public Renderable
	{
	public:
		Collider(GameObject& game_object, const Vec3& center);
		Collider(const Collider& collider);
		Collider(const Collider&& collider) noexcept;
		Collider& operator=(const Collider& collider);
		Collider& operator=(const Collider&& collider) noexcept;
		virtual ~Collider();

		virtual void OnUpdate(const double& delta) override;
		virtual void AttachRigidBody();

		virtual const Vec3&			 GetCenter() const;
		virtual const Vec3&			 GetMax() const;
		virtual const Vec3&			 GetMin() const;
		virtual const Ref<RigidBody> GetRigidBody() const;
	protected:
		Vec3		   mCenter;
		Vec3		   mOffset;
		Ref<RigidBody> mRigidBody = nullptr;

		virtual void UpdateCollisionSystem() = 0;
	};
}