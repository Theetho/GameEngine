#pragma once

#include "Renderer/Rendering/Renderable.h"
#include "Include/Component.h"
#include "Transform.h"

namespace Engine
{
	struct Collision;
	class Event;

	class GameObject : public Renderable
	{
	public:
		GameObject();
		GameObject(const Transform& transform);
		GameObject(const GameObject& other);
		GameObject(const GameObject&& other) noexcept;
		GameObject& operator=(const GameObject& other);
		GameObject& operator=(const GameObject&& other) noexcept;

		virtual ~GameObject();

		virtual void OnUpdate(const double& delta);
		virtual void OnEvent(Event& event);
		virtual void OnCollision(const Collision& collision);

		virtual bool IsJumping() const;
		virtual bool IsMoving() const;
		virtual bool IsMoveable() const;
		virtual bool IsColliding() const;
		virtual void SetIsColliding(bool colliding);
	
		virtual const Transform& GetTransform() const;
		virtual const Vec3&		 GetFront() const;
		
		virtual Transform& GetTransform();
		
		virtual void SetPosition(const Vec3& position);
		virtual void SetRotation(const Vec3& rotation);
		virtual void SetScale(float scale);
		virtual void SetScale(const Vec3& scale);

		template<typename T>
		void AddComponent(Ref<Component> component)
		{
			static_assert(std::is_base_of<Component, T>::value, "T is not a component");

			auto* type = &typeid(T);

			if (mComponents.find(*type) == mComponents.end())
			{
				mComponents[*type] = component;
			}
		}
		template<typename T>
		void RemoveComponent()
		{
			static_assert(std::is_base_of<Component, T>::value, "T is not a component");

			if (mComponents.find(typeid(T)) != mComponents.end())
				mComponents.erase(typeid(T));
		}
		template<typename T>
		Ref<T> GetComponent()
		{
			static_assert(std::is_base_of<Component, T>::value, "T is not a component");

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
			static_assert(std::is_base_of<Component, T>::value, "T is not a component");

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
		Transform mTransform;
		bool      mIsColliding;
		
		std::unordered_map<std::type_index, Ref<Component>> mComponents;

		virtual void Render(Ref<RenderCommand> render_command, Ref<Shader> shader) const override;
	};
}

