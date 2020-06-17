#include "EnginePch.h"
#include "Scene.h"
#include "SceneObject.h"
#include "Include/GUI.h"
#include "Include/Lighting.h"
#include "Core/Application.h"
#include "Renderer/Shader.h"

namespace Engine
{
	uint Scene::sInstancesCount = 0;

	Scene::Scene()
		: mObjects()
		, mId(sInstancesCount)
	{
		sInstancesCount += 1;
	}

	Scene::~Scene()
	{}

	void Scene::Render()
	{
		auto left_panel = Application::Get().GetEngineGUI().GetPanel("Left");
		auto tab = left_panel.GetOpenedTab();
		if (tab == Tab::Scene)
		{
			left_panel.Begin();
			if (ImGui::TreeNode("Scene"))
			{
				int i = 0;
				for (; i < mObjects.size(); ++i)
				{
					mObjects[i]->OnLeftPanel();
				}
				if (ImGui::TreeNode("Lights"))
				{
					for (int j = 0; j < mLights.size(); ++j)
					{
						mLights[j]->OnLeftPanel();
					}
					ImGui::TreePop();
				}
				ImGui::TreePop();
			}
			left_panel.End();
		}
	}

	void Scene::UpdateLights(std::initializer_list<Ref<Shader>> shaders)
	{
		for (int i = 0; i < mLights.size(); ++i)
		{
			auto light = mLights[i];

			// Switch the current light's type
			if (light->ShouldChangeType())
			{
				switch (light->GetRequestedType())
				{
					case (int)Light::LightID::Directional:
						mLights[i] = CreateRef<DirectionalLight>(Vec3(1.0, -1.0, 0.0));
						break;
					case (int)Light::LightID::Point:
						mLights[i] = CreateRef<PointLight>(Vec3(-1.0, 1.0, 0.0));
						break;
					case (int)Light::LightID::Spot:
						mLights[i] = CreateRef<SpotLight>(Vec3(0.0, 1.0, 0.0), Vec3(0.0, -1.0, 0.0));
						break;
					default: break;
				}
				light = mLights[i];
				// Reselect the modified light in the inspector
				((SceneObject*) & *light)->mSelected = true;
			}

			// Load the light in the shaders
			for (auto& shader : shaders)
			{
				light->IsActive() ? light->Load(shader, i) : light->Unload(shader, i);
			}
		}
	}
}
