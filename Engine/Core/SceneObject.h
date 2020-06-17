#pragma once

#define ApplyID(label) (label + std::string("##") + std::to_string(mSceneID)).c_str()

namespace Engine
{
	class Scene;

	class SceneObject
	{
	protected:
		SceneObject();
		friend class Scene;
		virtual void OnLeftPanel(SceneObject* caller = nullptr, std::string label = "");
		virtual void OnRightPanel() = 0;
		inline void RenderChild(SceneObject& child)
		{
			child.OnRightPanel();
		}
	private:
		static uint sCount;
		static bool* sCurrentlySelected;
		bool mSelected = false;
	protected:
		uint mSceneID;
	};
}