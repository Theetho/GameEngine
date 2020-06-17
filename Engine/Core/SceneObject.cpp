#include "EnginePch.h"
#include "SceneObject.h"
#include "Include/GUI.h"
#include "Core/Application.h"

namespace Engine
{
	bool* SceneObject::sCurrentlySelected = nullptr;
	uint SceneObject::sCount = 0;

	SceneObject::SceneObject()
		: mSceneID(sCount++)
	{}

	void SceneObject::OnLeftPanel(SceneObject* caller, std::string label)
	{
		if (!caller) return;

		auto right_panel = Application::Get().GetEngineGUI().GetPanel("Right");

		ImGui::Selectable(ApplyID(label), &mSelected);
		if (mSelected)
		{
			if (sCurrentlySelected && sCurrentlySelected != &mSelected) *sCurrentlySelected = false;
			sCurrentlySelected = &mSelected;

			right_panel.Begin();
			caller->OnRightPanel();
			right_panel.End();
		}
	}
}