#pragma once

namespace Engine
{
	class SceneObject;
	class Light;
	class Shader;

	class Scene
	{
	public:
		Scene();
		~Scene();

		void Render();
		void UpdateLights(std::initializer_list<Ref<Shader>> shaders);
		inline void Push(SceneObject* object)
		{
			mObjects.push_back(object);
		}
		inline void Clear()
		{
			mObjects.clear();
		}
		inline std::vector<Ref<Light>>& GetLights()
		{
			return mLights;
		}
	private:
		static uint sInstancesCount;
		uint mId;
		std::vector<SceneObject*> mObjects;
		std::vector<Ref<Light>> mLights;
	};
}

