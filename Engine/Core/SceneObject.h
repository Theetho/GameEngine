#pragma once

namespace Engine
{
	class Scene;

	class SceneObject
	{
	protected:
		friend class Scene;
		virtual void OnLeftPanel(SceneObject* caller = nullptr, std::string label = "", int number = -1);
		virtual void OnRightPanel() = 0;
		inline void RenderChild(SceneObject& child)
		{
			child.OnRightPanel();
		}
	private:
		static bool* sCurrentlySelected;
		bool mSelected = false;
	};
}