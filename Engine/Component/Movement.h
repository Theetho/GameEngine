#pragma once

#include "EnginePch.h"
#include "Core/Input.h"
#include "Component.h"
#include "RigidBody.h"
#include "Include/GUI.h"
#include "Core/Application.h"

namespace Engine
{
	template<int dimension>
	class Movement : public Component<dimension>
	{
	public:
		Movement(GameObject<dimension>& game_object, bool is_reversed)
			: Component(game_object)
			, mRigidBody(game_object.GetComponent<Engine::RigidBody<dimension>>())
			, mIsReversed(is_reversed)
		{}
		~Movement()
		{}

		void OnUpdate(const double& delta)
		{
			if (!mRigidBody)
			{
				if (auto body = mGameObject.GetComponent<RigidBody<dimension>>())
					mRigidBody = body;
				else
					return;
			}

			Ref<Transform<dimension>> transform = mRigidBody->GetTransform();
			Vec<dimension>& velocity = mRigidBody->GetVelocity();
			for (uint i = 0; i < velocity.length(); ++i)
			{
				velocity[i] = 0.0f;
			}

			Vec<dimension>& angular = mRigidBody->GetAngularVelocity();

			if (!mRigidBody->IsUsingGravity())
				velocity[1] = 0.0f;

			angular = Vec<dimension>();

			if (Input::IsKeyPressed(ENGINE_KEY_LEFT_SHIFT))
				mSpeed.current = mSpeed.max;
			else
				mSpeed.current = mSpeed.min;

			if (Input::IsKeyPressed(ENGINE_KEY_W))
			{
				if (!Input::IsKeyPressed(ENGINE_KEY_S))
				{
					velocity[0] += mSpeed.current * delta;
				}
			}
			else if (Input::IsKeyPressed(ENGINE_KEY_S))
			{
				velocity[0] -= mSpeed.current * delta;
			}

			if (Input::IsKeyPressed(ENGINE_KEY_SPACE))
			{
				if (!Input::IsKeyPressed(ENGINE_KEY_LEFT_CONTROL))
				{
					velocity[1] += mSpeed.current * delta;
				}
			}
			else if (Input::IsKeyPressed(ENGINE_KEY_LEFT_CONTROL))
			{
				velocity[1] -= mSpeed.current * delta;
			}

			if (Input::IsKeyPressed(ENGINE_KEY_E))
			{
				angular[1] += (mIsReversed ? mSpeed.angular : -mSpeed.angular) * delta;
			}
			else if (Input::IsKeyPressed(ENGINE_KEY_Q))
			{
				angular[1] += (mIsReversed ? -mSpeed.angular : mSpeed.angular) * delta;
			}

			if (velocity.length() == 3)
			{
				if (Input::IsKeyPressed(ENGINE_KEY_A))
				{
					if (!Input::IsKeyPressed(ENGINE_KEY_D))
					{
						velocity[2] -= mSpeed.current * delta;
					}
				}
				else if (Input::IsKeyPressed(ENGINE_KEY_D))
				{
					velocity[2] += mSpeed.current * delta;
				}

				float theta = glm::radians(mIsReversed ? 180 - transform->GetRotation().y : transform->GetRotation().y);
				float dx = velocity[0] * sin(theta) - velocity[2] * cos(theta);
				float dz = velocity[0] * cos(theta) + velocity[2] * sin(theta);

				velocity[0] = dx; velocity[2] = dz;
			}
		}

		//void SetForwardAxis(const Engine::Vec3& axis);
	private:
		Ref<RigidBody<dimension>> mRigidBody;
		struct Speed
		{
			float current;
			float angular = 100.0f;
			float max = 100.0f;
			float min = 25.0f;
		};
		Speed mSpeed;
		// For camera for example;
		bool mIsReversed;
		
		inline void OnUiRender() override
		{
			if (ImGui::CollapsingHeader(ApplyID("Movement"), ImGuiTreeNodeFlags_DefaultOpen))
			{
				ImGui::Checkbox(ApplyID("Reversed"), &mIsReversed);
				ImGui::Text("Velocity");
				ImGui::DragFloat(ApplyID("Max"), &mSpeed.max, 0.1f, mSpeed.min, std::numeric_limits<float>::max());
				ImGui::DragFloat(ApplyID("Min"), &mSpeed.min, 0.1f, 0.f, mSpeed.max);
				ImGui::DragFloat(ApplyID("Angular"), &mSpeed.angular, 0.1f, 0.0f, std::numeric_limits<float>::max());
			}
		}
	};

	template class Movement<3>;
	template class Movement<2>;

	using Movement3D = Movement<3>;
	using Movement2D = Movement<2>;
}