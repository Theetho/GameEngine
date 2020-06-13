#include "EnginePch.h"
#include "SceneObject.h"
#include "Include/GUI.h"
#include "Core/Application.h"

namespace Engine
{
	bool* SceneObject::sCurrentlySelected = nullptr;

	void SceneObject::OnLeftPanel(SceneObject* caller, std::string label, int number)
	{
		if (!caller && number == -1) return;

		auto right_panel = Application::Get().GetEngineGUI().GetPanel("Right");

		if (number >= 0) label += "##" + std::to_string(number);

		ImGui::Selectable(label.c_str(), &mSelected);
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