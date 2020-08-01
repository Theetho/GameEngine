#pragma once

#include "EnginePch.h"
#include "Component.h"
#include "Include/GameObject.h"

namespace Engine
{
	template<int dimension>
	class RigidBody : public Component<dimension>
	{
	public:
		RigidBody(GameObject<dimension>& game_object)
			: Component(game_object)
			, mTransform(game_object.GetComponent<Transform<dimension>>())
			, mVelocity()
			, mAngularVelocity()
		{}

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
		inline Ref<Transform<dimension>> GetTransform()
		{
			return mTransform;
		}
		inline const Ref<Transform<dimension>> GetTransform() const
		{
			return mTransform;
		}
	
		inline void OnUpdate(const double& delta) override
		{
			Vec<dimension>& position = mTransform->GetPosition();
			Vec<dimension>& rotation = mTransform->GetRotation();

			position += mVelocity;
			rotation += mAngularVelocity;


		}
	private:
		bool	   mUseGravity  = true;
		bool	   mIsKinematic = false;
		float	   mMass        = 1.0f;
		Vec<dimension> mVelocity;
		Vec<dimension> mAngularVelocity;

		Ref<Transform<dimension>> mTransform;

		inline void OnUiRender() override
		{
			if (ImGui::CollapsingHeader(ApplyID("Rigidbody"), ImGuiTreeNodeFlags_DefaultOpen))
			{
				ImGui::Checkbox(ApplyID("Gravity"), &mUseGravity);
				ImGui::Checkbox(ApplyID("Kinematic"), &mIsKinematic);
				ImGui::DragFloat(ApplyID("Mass"), &mMass, 0.1f, 0.f, std::numeric_limits<float>::max());
			}
		}
	};

	template class RigidBody<3>;
	template class RigidBody<2>;

	using RigidBody3D = RigidBody<3>;
	using RigidBody2D = RigidBody<2>;
}

