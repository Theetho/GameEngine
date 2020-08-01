#include "EnginePch.h"
#include "Scene.h"
#include "Core/Application.h"
#include "Core/AssetManager.h"
#include "Include/Lighting.h"
#include "GUI/EngineGui.h"
#include "SceneObject.h"
#include "EditableObject.h"

namespace Engine
{
	Scene::Scene()
	{}

	Scene::~Scene()
	{
	}

	void Scene::OnUiRender()
	{
		auto& left_panel = Application::Get()->GetEngineGUI().GetPanel("Left");
		auto tab = left_panel.GetOpenedTab();
		if (tab == Tab::Scene)
		{
			left_panel.Begin();
			if (ImGui::TreeNode("Scene"))
			{
				for (auto& object : mSceneObjects)
				{
					EditableObject::Render(object);
				}
				if (ImGui::TreeNode("Lights"))
				{
					for (auto& light : mLights)
					{
						EditableObject::Render(light);
					}
					ImGui::TreePop();
				}
				ImGui::TreePop();
			}
			left_panel.End();
		}
		
	}

	void Scene::UpdateLights()
	{
		if (mLights.size() == 0) return;

		int i = 0;
		for (Ref<Light>& light : mLights)
		{
			// Switch the current light's type
			if (light->ShouldChangeType())
			{
				switch (light->GetRequestedType())
				{
					case (int)Light::LightID::Directional:
						light = DirectionalLight::Create(Vec3(1.0, -1.0, 0.0));// .reset(new DirectionalLight(Vec3(1.0, -1.0, 0.0)));
						break;
					case (int)Light::LightID::Point:
						light = PointLight::Create(Vec3(-1.0, 1.0, 0.0));
						break;
					case (int)Light::LightID::Spot:
						light = SpotLight::Create(Vec3(0.0, 1.0, 0.0), Vec3(0.0, -1.0, 0.0)); // .reset(new SpotLight(Vec3(0.0, 1.0, 0.0), Vec3(0.0, -1.0, 0.0)));
						break;
					default: break;
				}
				// Reselect the modified light in the inspector
				light->mSelected = true;
			}

			// Load the light in the shaders
			for (auto& shader : AssetManager::GetShaderLibrary().GetList())
			{
				light->IsActive() ? light->Load(shader.second, i) : light->Unload(shader.second, i);
			}

			++i;
		}
	}
}
