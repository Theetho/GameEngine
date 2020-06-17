#pragma once

#include "EnginePch.h"
#include "Component.h"
#include "Include/GameObject.h"

namespace Engine
{
	/*class CollisionSystem;*/
	//template<int dimension>
	//struct Velocity
	//{
	//	Vec<dimension> regular;
	//	Vec<dimension> angular;
	//};

	template<int dimension>
	class RigidBody : public Component<dimension>
	{
	public:
		RigidBody(GameObject<dimension>& game_object)
			: Component(game_object)
			, mTransform(game_object.GetTransform())
			, mVelocity()
			, mAngularVelocity()
		{
			/*auto box    = std::dynamic_pointer_cast<Collider>(game_object.GetComponent<BoxCollider>());
			auto sphere = std::dynamic_pointer_cast<Collider>(game_object.GetComponent<SphereCollider>());
			if (box)
				box->AttachRigidBody();
			if (sphere)
				sphere->AttachRigidBody();*/
		}
		~RigidBody()
		{}

		inline void SetUseGravity(bool use)
		{
			mUseGravity = use;
		}
		inline bool IsUsingGravity() const
		{
			return mUseGravity;
		}
		inline Vec<dimension>& GetVelocity()
		{
			return mVelocity;
		}
		inline const Vec<dimension>& GetVelocity() const
		{
			return mVelocity;
		}
		inline Vec<dimension>& GetAngularVelocity()
		{
			return mAngularVelocity;
		}
		inline const Vec<dimension>& GetAngularVelocity() const
		{
			return mAngularVelocity;
		}
		inline Transform<dimension>& GetTransform()
		{
			return mTransform;
		}
		inline const Transform<dimension>& GetTransform() const
		{
			return mTransform;
		}
	
		inline void OnUpdate(const double& delta) override
		{
			Vec<dimension>& position = mTransform.GetPosition();
			Vec<dimension>& rotation = mTransform.GetRotation();

			position += mVelocity;
			rotation += mAngularVelocity;


		}
	private:
		bool	   mUseGravity  = true;
		bool	   mIsKinematic = false;
		float	   mMass        = 1.0f;
		Vec<dimension> mVelocity;
		Vec<dimension> mAngularVelocity;

		Transform<dimension>& mTransform;

		inline void OnRightPanel() override
		{
			if (ImGui::CollapsingHeader(ApplyID("Rigidbody"), ImGuiTreeNodeFlags_DefaultOpen))
			{
				ImGui::Indent(ImGui::GetTreeNodeToLabelSpacing());
				ImGui::Checkbox(ApplyID("Gravity"), &mUseGravity);
				ImGui::Checkbox(ApplyID("Kinematic"), &mIsKinematic);
				ImGui::DragFloat(ApplyID("Mass"), &mMass, 0.1f, 0.f, std::numeric_limits<float>::max());
				ImGui::Unindent(ImGui::GetTreeNodeToLabelSpacing());
			}
		}
	};

	template class RigidBody<3>;
	template class RigidBody<2>;

	using RigidBody3D = RigidBody<3>;
	using RigidBody2D = RigidBody<2>;
}

