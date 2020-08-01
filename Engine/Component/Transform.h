#pragma once

#include "EnginePch.h"
#include "Util/Matrix.h"
#include "Component.h"

namespace Engine
{
	template<int dimension>
	class Transform : public Component<dimension> // public EditableObject
	{
	public:
		Transform(GameObject<dimension>& game_object) 
			: Component(game_object)
			, mPosition()
			, mRotation(0.0)
			, mScale(1.0)
		{}
		Transform(GameObject<dimension>& game_object, const Vec<dimension>& position, const Vec<dimension>& rotation, const Vec<dimension>& scale)
			: Component(game_object)
			, mPosition(position)
			, mRotation(rotation)
			, mScale(scale)
		{}
		Transform(const Transform<dimension>& transform)
			: Component(transform)
			, mPosition(transform.mPosition)
			, mRotation(transform.mRotation)
			, mScale(transform.mScale)
		{}
		Transform(const Transform<dimension>&& transform) noexcept
			: Component(transform)
			, mPosition(transform.mPosition)
			, mRotation(transform.mRotation)
			, mScale(transform.mScale)
		{}
		Transform& operator=(const Transform<dimension>& transform)
		{
			mPosition = transform.mPosition;
			mRotation = transform.mRotation;
			mScale	  = transform.mScale;

			return *this;
		}
		Transform& operator=(const Transform<dimension>&& transform) noexcept
		{
			mPosition = transform.mPosition;
			mRotation = transform.mRotation;
			mScale	  = transform.mScale;

			return *this;
		}
		inline void OnUpdate(const double& delta) override {}
		inline const Vec<dimension>& GetPosition() const
		{
			return mPosition;
		}
		inline const Vec<dimension>& GetRotation() const
		{
			return mRotation;
		}
		inline const Vec<dimension>& GetScale() const
		{
			return mScale;
		}
		inline Vec<dimension>& GetPosition()
		{
			return mPosition;
		}
		inline Vec<dimension>& GetRotation()
		{
			return mRotation;
		}
		inline Vec<dimension>& GetScale()
		{
			return mScale;
		}
		inline const Mat4 GetModel() const
		{
			return Matrix::Model(mPosition, mRotation, mScale);
		}
		
		inline void SetPosition(const Vec<dimension>& position)
		{
			mPosition = position;
		}
		inline void SetPosition(char axis, float value)
		{
			int indice = axis - 'x';

			if (indice < 0 || indice >= Vec<dimension>::length())
				return;

			mPosition[indice] = value;
		}
		inline void SetRotation(const Vec<dimension>& rotation)
		{
			mRotation = rotation;
		}
		inline void SetRotation(char axis, float value)
		{
			int indice = axis - 'x';

			if (indice < 0 || indice >= Vec<dimension>::length())
				return;

			mRotation[indice] = value;
		}
		inline void SetScale(const Vec<dimension>& scale)
		{
			mScale = scale;
		}
		inline void SetScale(char axis, float value)
		{
			int indice = axis - 'x';

			if (indice < 0 || indice >= Vec<dimension>::length())
				return;

			mScale[indice] = value;
		}
		inline void SetScale(float scale)
		{
			mScale = Vec<dimension>(scale);
		}
	private:
		Vec<dimension> mPosition;
		Vec<dimension> mRotation;
		Vec<dimension> mScale;

		//inline void OnRightPanel() override
		inline void OnUiRender() override
		{
			if (ImGui::CollapsingHeader(ApplyID("Transform"), ImGuiTreeNodeFlags_DefaultOpen))
			{
				ImGui::Text("Position");

				if (dimension == 3) {
					ImGui::DragFloat3(ApplyID("##Position"), (float*)(&mPosition), 0.1f);
					ImGui::Text("Rotation");
					ImGui::SliderFloat3(ApplyID("##Rotation"), (float*)(&mRotation), -360.0f, 360.f);
					ImGui::Text("Scale");
					ImGui::DragFloat3(ApplyID("##Scale"), (float*)(&mScale), 0.1f, 0.0f, std::numeric_limits<float>::max());
				} else if (dimension == 2) {
					ImGui::DragFloat2(ApplyID("##Position"), (float*)(&mPosition), 0.1f);
					ImGui::Text("Rotation");
					ImGui::SliderFloat2(ApplyID("##Rotation"), (float*)(&mRotation), -360.0f, 360.f);
					ImGui::Text("Scale");
					ImGui::DragFloat2(ApplyID("##Scale"), (float*)(&mScale), 0.1f, 0.0f, std::numeric_limits<float>::max());
				}
			}
		}
	};

	template class Transform<2>;
	template class Transform<3>;	

	using Transform2D = Transform<2>;
	using Transform3D = Transform<3>;
}

