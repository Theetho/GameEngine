#include "EnginePch.h"
#include "EditableObject.h"

namespace Engine
{
	uint EditableObject::sCount = 0;

	EditableObject::EditableObject()
		: mSceneID(sCount++)
		, mShowOnEditor(true)
	{}

	void EditableObject::Render(Ref<EditableObject> editable)
	{
		if (editable->mShowOnEditor)
			editable->OnUiRender();
	}
	
	EditableObject::EditableObject(const EditableObject& other)
		: mSceneID(sCount++)
		, mShowOnEditor(other.mShowOnEditor)
	{
	}
	
	EditableObject::EditableObject(const EditableObject&& other) noexcept
		: mSceneID(other.mSceneID)
		, mShowOnEditor(other.mShowOnEditor)
	{
	}
}

