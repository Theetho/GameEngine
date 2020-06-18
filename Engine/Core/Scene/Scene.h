#pragma once

namespace Engine
{
	class SceneObject;
	class Light;

	class Scene
	{
	public:
		Scene();
		~Scene();

		void OnUiRender();
		void UpdateLights();

		inline void Clear()
		{
			mSceneObjects.clear();
		}
		inline void Push(SceneObject* object)
		{
			mSceneObjects.push_back(object);
		}
		inline void Remove(SceneObject* object)
		{
			mSceneObjects.remove(object);
		}
		inline void AddLight(Ref<Light> light)
		{
			Remove((SceneObject*)light.get());
			mLights.push_back(light);
		}
		inline void RemoveLight(Ref<Light> light)
		{
			mLights.remove(light);
		}
	private:
		std::list<SceneObject*> mSceneObjects;
		std::list<Ref<Light>> mLights;
	};
}

