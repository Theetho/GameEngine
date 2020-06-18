#include "EnginePch.h"
#include "SceneObject.h"
#include "Scene.h"
#include "Core/Application.h"
#include "GUI/EngineGui.h"
#include <typeinfo>

namespace Engine
{
	bool* SceneObject::sCurrentlySelected = nullptr;

	SceneObject::SceneObject()
		: EditableObject()
	{
		if (Application::Get())
			Application::Get()->GetScene().Push(this);
	}

	SceneObject::~SceneObject()
	{}

	void SceneObject::OnUiRender()
	{
		std::string name(typeid(*this).name());
		std::string label = "undefined";
		// If name contains ':'
		size_t actual_start = name.find_last_of(':');
		if (actual_start != std::string::npos)
		{
			// It means it is in the form "class ${namespace}::${className}",
			// so we have to extract the actual class name, which is after the
			// last ':'.
			label = name.erase(0, actual_start + 1);
		}
		
		ImGui::Selectable(ApplyID(label), &mSelected);
		if (mSelected)
		{
			if (sCurrentlySelected && sCurrentlySelected != &mSelected) *sCurrentlySelected = false;
			sCurrentlySelected = &mSelected;

			auto& right_panel = Application::Get()->GetEngineGUI().GetPanel("Right");
			
			right_panel.Begin();
			OnUiSelected();
			right_panel.End();
		}
	}
}