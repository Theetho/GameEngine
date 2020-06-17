#include "EnginePch.h"
#include "Light.h"
#include "Renderer/Rendering/Renderer.h"
#include "Renderer/Rendering/RendererAPI.h"
#include "API/OpenGL/Shader.h"

namespace Engine
{
	Light::Light(const Color& color)
		: mColor(color)
		, mActive(true)
	{}

	Light::~Light()
	{}

	void Light::Load(Ref<Shader> shader, unsigned int index)
	{
		switch (Renderer::GetAPI())
		{
		case API::OpenGL:
			LoadGLUniforms(std::dynamic_pointer_cast<OpenGL::Shader>(shader), index);
		default:
			break;
		}
	}

	void Light::Unload(Ref<Shader> shader, unsigned int index)
	{
		switch (Renderer::GetAPI())
		{
			case API::OpenGL:
				UnloadGLUniforms(std::dynamic_pointer_cast<OpenGL::Shader>(shader), index);
			default:
				break;
		}
	}

	const Color& Light::GetColor() const
	{
		return mColor;
	}

	void Light::SetColor(const Color& color)
	{
		mColor = color;
	}

	void Light::LoadGLUniforms(Ref<OpenGL::Shader> shader, unsigned int index)
	{
		shader->Bind();
		shader->UploadUniform("uLights[" + std::to_string(index) + "].minDiffuseFactor", mMinDiffuseFactor);
		shader->UploadUniform("uLights[" + std::to_string(index) + "].id"   , this->GetID());
		shader->UploadUniform("uLights[" + std::to_string(index) + "].color", Vec3(mColor));
	}

	void Light::UnloadGLUniforms(Ref<OpenGL::Shader> shader, unsigned int index)
	{
		shader->Bind();
		shader->UploadUniform("uLights[" + std::to_string(index) + "].id", 0);
		shader->UploadUniform("uLights[" + std::to_string(index) + "].color", 0);
	}

	void Light::OnRightPanel()
	{
		ImGui::Checkbox(ApplyID("Active"), &mActive);
		ImGui::Text("Color");
		ImGui::ColorEdit3(ApplyID("##Color"), (float*)&mColor);
		ImGui::Text("Min diffuse factor");
		ImGui::SliderFloat(ApplyID("##DiffuseFactor"), &mMinDiffuseFactor, 0.0f, 1.0f);
		ImGui::Separator();

		std::unordered_map<int, const char*> items = {
			{(int)LightID::Directional, "Directional"},
			{(int)LightID::Point, "Point" },
			{(int)LightID::Spot, "Spot" }
		};

		const char* item_current = items[this->GetID()];
		if (ImGui::BeginCombo(ApplyID(""), item_current))
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
}