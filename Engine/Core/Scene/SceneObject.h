#pragma once

#include "EditableObject.h"

namespace Engine
{
	class Scene;

	class SceneObject : public EditableObject
	{
	public:
		SceneObject(bool do_register = true);
		~SceneObject();
		SceneObject(const SceneObject& other);
		SceneObject(const SceneObject&& other) noexcept;
		bool operator==(const SceneObject& other) const;
	private:
		friend class Scene;
		static bool* sCurrentlySelected;
		bool mSelected = false;
		void OnUiRender() override;
	protected:
		virtual void OnUiSelected() = 0;
	};
}