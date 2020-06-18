#include "EnginePch.h"
#include "EditableObject.h"

namespace Engine
{
	uint EditableObject::sCount = 0;

	EditableObject::EditableObject()
		: mSceneID(sCount++)
	{}
	
	void EditableObject::Render(EditableObject* editable)
	{
		editable->OnUiRender();
	}
}

