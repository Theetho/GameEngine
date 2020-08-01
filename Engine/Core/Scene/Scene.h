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
		{}

		inline void AddObject(Ref<SceneObject> scene_object) {
			mSceneObjects.insert(scene_object);
		}

		template<class T, class ... Args>
		inline std::shared_ptr<T> AddObject(Args&& ... args) {
			static_assert(std::is_base_of<SceneObject, T>::value, "T is not a SceneObject");

			auto scene_object = T::Create(std::forward<Args>(args)...);

			mSceneObjects.insert(scene_object);
			return scene_object;
		}

		inline void RemoveObject(Ref<SceneObject> scene_object) {
			if (!mSceneObjects.count(scene_object)) return;

			mSceneObjects.erase(scene_object);
		}

		template<class T, class ... Args>
		inline void AddLight(Args&& ... args) {
			static_assert(std::is_base_of<Light, T>::value, "T is not a Light");

			mLights.push_back(T::Create(std::forward<Args>(args)...));
		}

		inline void RemoveLight(Ref<Light> light) {
			mLights.remove(light);
		}
	private:
		std::set<Ref<SceneObject>> mSceneObjects;
		std::list<Ref<Light>> mLights;
	};
}

