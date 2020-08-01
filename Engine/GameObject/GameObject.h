#pragma once

#include "Component/Transform.h"
#include "Core/Scene/SceneObject.h"

namespace Engine
{
	class Event;

	template<int dimension>
	class GameObject : public SceneObject
	{
		CREATOR(GameObject<dimension>);
	protected:
		GameObject()
			: SceneObject()
			, mComponents()
		{
			AddComponent<Transform<dimension>>();
		}
	public:
		virtual ~GameObject() {}
		GameObject(const GameObject<dimension>& gameObject)
			: SceneObject()
			, mComponents(gameObject.mComponents)
		{}
		GameObject(const GameObject<dimension>&& gameObject) noexcept
			: SceneObject()
			, mComponents(gameObject.mComponents)
		{}
		GameObject& operator=(const GameObject<dimension>& gameObject)
		{
			mComponents = gameObject.mComponents;

			return *this;
		}
		GameObject& operator=(const GameObject<dimension>&& gameObject) noexcept
		{
			mComponents = gameObject.mComponents;

			return *this;
		}
		virtual void OnUpdate(const double& delta)
		{
			UpdateComponents(delta);
		}
		virtual void OnEvent(Event& event)
		{};

		template<typename T>
		void AddComponent(Ref<T> component) {
			static_assert(std::is_base_of<Component<dimension>, T>::value, "T is not a component");

			auto* type = &typeid(T);

			if (mComponents.find(*type) == mComponents.end())
			{
				mComponents[*type] = component;
			}
		}

		template<typename T, typename ... Args>
		Ref<T> AddComponent(Args&& ... args)
		{
			static_assert(std::is_base_of<Component<dimension>, T>::value, "T is not a component");

			auto* type = &typeid(T);

			Ref<Component<dimension>> component = std::make_shared<T>(*this, std::forward<Args>(args)...);

			if (mComponents.find(*type) == mComponents.end())
			{
				mComponents[*type] = component;
			}

			return std::dynamic_pointer_cast<T>(component);
		}

		template<typename T>
		void RemoveComponent()
		{
			static_assert(std::is_base_of<Component<dimension>, T>::value, "T is not a component");

			if (mComponents.find(typeid(T)) != mComponents.end())
				mComponents.erase(typeid(T));
		}

		template<typename T>
		Ref<T> GetComponent()
		{
			static_assert(std::is_base_of<Component<dimension>, T>::value, "T is not a component");

			for (auto kv : mComponents)
			{
				if (kv.first == typeid(T))
				{
					return std::dynamic_pointer_cast<T>(kv.second);
				}
			}

			return std::shared_ptr<T>();
		}

		template<typename T>
		const Ref<T> GetComponent() const
		{
			static_assert(std::is_base_of<Component<dimension>, T>::value, "T is not a component");

			for (auto kv : mComponents)
			{
				if (kv.first == typeid(T))
				{
					return std::dynamic_pointer_cast<T>(kv.second);
				}
			}
	
			return std::shared_ptr<T>();
		}
	protected:
		std::unordered_map<std::type_index, Ref<Component<dimension>>> mComponents;

		void UpdateComponents(const double& delta)
		{
			for (auto kv : mComponents)
			{
				kv.second->OnUpdate(delta);
			}
		}

		inline void OnUiSelected()
		{
			for (auto& kv : mComponents)
			{
				ImGui::Separator();
				EditableObject::Render(kv.second);
			}
		}
	};

	template class GameObject<2>;
	template class GameObject<3>;

	using GameObject2D = GameObject<2>;
	using GameObject3D = GameObject<3>;
}

