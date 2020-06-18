#pragma once

#define ApplyID(label) (label + std::string("##") + std::to_string(mSceneID)).c_str()

namespace Engine
{
	class EditableObject
	{
	public:
		static void Render(EditableObject* editable);
	private:
		static uint sCount;
	protected:
		EditableObject();
		uint mSceneID;
		virtual void OnUiRender() = 0;
	};
}

