#pragma once

#include "Core/Scene/SceneObject.h"

namespace Engine
{
	class Color;
	class Shader;
	namespace OpenGL
	{
		class Shader;
	}

	class Light : public SceneObject
	{
	public:
		explicit Light(const Color& color = Color::White);
		virtual ~Light();

		virtual void Load(Ref<Shader> shader, unsigned int index);
		virtual void Unload(Ref<Shader> shader, unsigned int index);

		virtual int GetID() const = 0;
		const Color& GetColor() const;
		inline float GetMinDiffuseFactor() const
		{
			return mMinDiffuseFactor;
		}

		void SetColor(const Color& color);
		inline void SetMinDiffuseFactor(float factor)
		{
			mMinDiffuseFactor = factor;
		}
		inline bool ShouldChangeType() const
		{
			return (mRequestedType != (int)LightID::None && GetID() != mRequestedType);
		}
		inline int GetRequestedType() const
		{
			return mRequestedType;
		}
		inline bool& IsActive()
		{
			return mActive;
		}
		enum class LightID
		{
			None,
			Directional,
			Point,
			Spot
		};

	private:
		Color mColor;
		bool mActive;
		float mMinDiffuseFactor = 0.3f;
	protected:
		virtual void LoadGLUniforms(Ref<OpenGL::Shader> shader, unsigned int index);
		virtual void UnloadGLUniforms(Ref<OpenGL::Shader> shader, unsigned int index);
		inline void OnUiSelected() override
		{
			ImGui::Checkbox(ApplyID("Active"), &mActive);
			ImGui::Text("Color");
			ImGui::ColorEdit3(ApplyID("##Color"), (float*)&mColor);
			ImGui::Text("Diffuse factor");
			ImGui::SliderFloat(ApplyID("##DiffuseFactor"), &mMinDiffuseFactor, 0.0f, 1.0f);
			ImGui::Separator();

			std::unordered_map<int, const char*> items = {
				{(int)LightID::Directional, "Directional"},
				{(int)LightID::Point, "Point" },
				{(int)LightID::Spot, "Spot" }
			};

			const char* item_current = items[this->GetID()];
			ImGui::Text("Type");
			if (ImGui::BeginCombo(ApplyID("##Type"), item_current))
			{
				for (auto& item : items)
				{
					bool is_selected = (item_current == item.second);
					if (ImGui::Selectable(item.second, is_selected))
					{
						item_current = item.second;
						mRequestedType = item.first;
					}
					if (is_selected)
						ImGui::SetItemDefaultFocus();
				}
				ImGui::EndCombo();
			}
		}
	private:
		int mRequestedType = (int)LightID::None;
	};
}
