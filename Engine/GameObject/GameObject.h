#pragma once

#include "EnginePch.h"
#include "Include/Component.h"
#include "Transform.h"
#include "Core/SceneObject.h"

namespace Engine
{
	struct Collision;
	class Event;

	template<int dimension>
	class GameObject : public SceneObject
	{
	public:
		GameObject()
			: mTransform(Transform<dimension>())
			, mComponents()
		{}
		GameObject(const Transform<dimension>& transform)
			: mTransform(transform)
			, mComponents()
		{}
		GameObject(const GameObject<dimension>& gameObject)
			: mTransform(gameObject.mTransform)
			, mComponents(gameObject.mComponents)
		{}
		GameObject(const GameObject<dimension>&& gameObject) noexcept
			: mTransform(gameObject.mTransform)
			, mComponents(gameObject.mComponents)
		{}
		GameObject& operator=(const GameObject<dimension>& gameObject)
		{
			mTransform = gameObject.mTransform;
			mComponents = gameObject.mComponents;

			return *this;
		}
		GameObject& operator=(const GameObject<dimension>&& gameObject) noexcept
		{
			mTransform = gameObject.mTransform;
			mComponents = gameObject.mComponents;

			return *this;
		}
		~GameObject() {}

		Transform<dimension>& GetTransform()
		{
			return mTransform;
		}
		const Transform<dimension>& GetTransform() const
		{
			return mTransform;
		}

		template<typename T>
		void AddComponent(Ref<Component<dimension>> component)
		{
			static_assert(std::is_base_of<Component<dimension>, T>::value, "T is not a component");

			auto* type = &typeid(T);

			if (mComponents.find(*type) == mComponents.end())
			{
				mComponents[*type] = component;
			}
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
		Transform<dimension> mTransform;
		std::unordered_map<std::type_index, Ref<Component<dimension>>> mComponents;

		void UpdateComponents(const double& delta)
		{
			for (auto kv : mComponents)
			{
				kv.second->OnUpdate(delta);
			}
		}

		virtual void OnLeftPanel(SceneObject* caller = nullptr, std::string label = "", int number = -1) override
		{
			SceneObject::OnLeftPanel(this, "GameObject", number);
		}

		inline void OnRightPanel() override
		{
			SceneObject::RenderChild(mTransform);
			for (auto& kv : mComponents)
			{
				ImGui::Separator();
				SceneObject::RenderChild(*kv.second);
			}
		}
	};

	class GameObject2D : public GameObject<2>
	{
	public:
		virtual void OnUpdate(const double& delta)
		{
			UpdateComponents(delta);
		}
		virtual void OnEvent(Event& event)
		{};
	protected:
	};
	class GameObject3D : public GameObject<3>
	{
	public:
		virtual void OnUpdate(const double& delta)
		{
			UpdateComponents(delta);
		}
		virtual void OnEvent(Event& event)
		{};
	protected:
	};

}

