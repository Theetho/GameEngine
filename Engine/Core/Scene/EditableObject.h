#pragma once

#define ApplyID(label) (label + std::string("##") + std::to_string(mSceneID)).c_str()

namespace Engine
{
	class EditableObject
	{
	public:
		static void Render(Ref<EditableObject> editable);
		inline void SetShowOnEditor(bool set) {
			mShowOnEditor = set;
		}
		EditableObject(const EditableObject& other);
		EditableObject(const EditableObject&& other) noexcept;
	private:
		static uint sCount;
	protected:
		EditableObject();
		uint mSceneID;
		bool mShowOnEditor;
		virtual void OnUiRender() = 0;
	};
}

