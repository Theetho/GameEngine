#pragma once

#include "EditableObject.h"


namespace Engine
{
	class Scene;

	class SceneObject : public EditableObject
	{
	public:
		SceneObject();
		~SceneObject();
	private:
		friend class Scene;
		static bool* sCurrentlySelected;
		bool mSelected = false;
		void OnUiRender() override;
	protected:
		virtual void OnUiSelected() = 0;
	};
}