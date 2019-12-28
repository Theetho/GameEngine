#pragma once

#include "Component/Component.h"
#include "Component//RigidBody.h"
#include "GameObject/GameObject.h"
#include "Renderer/Buffer/VertexArray.h"
#include "Include/Maths.h"

namespace Engine
{
	// Declaration
	class Collision;

	class Collider : public Component
	{
	public:
		Collider(GameObject& game_object, const Vec3& center);
		Collider(const Collider& collider);
		Collider(const Collider&& collider) noexcept;
		Collider& operator=(const Collider& collider);
		Collider& operator=(const Collider&& collider) noexcept;
		virtual ~Collider();

		virtual void OnUpdate(const double& delta) override;
		virtual void AttachRigidBody(RigidBody* rigid_body);

		virtual const Vec3&      GetCenter() const;
		virtual const Vec3&      GetMax() const = 0;
		virtual const Vec3&      GetMin() const = 0;
		virtual const RigidBody* GetRigidBody() const;
	protected:
		Vec3	   mCenter;
		Vec3	   mOffset;
		RigidBody* mRigidBody = nullptr;
	};

	// Class that stores data of a collision
	class Collision
	{
	public:
		Collision(bool collide, float distance_up_axis, const Collider* first, const Collider* second);

		bool  IsColliding() const;
		float GetDistanceUpAxis() const;
		const std::pair<const Collider*, const Collider*>& GetColliders() const;
	private:
		// The two colliders that are supposedly colliding
		const std::pair<const Collider*, const Collider*> mColliders;
		// Boolean to tell whether the two colliders are colliding
		const bool  mIsColliding;
		// The distance beetween the two colliders on the up axis
		const float mDistanceUpAxis;
	};
}