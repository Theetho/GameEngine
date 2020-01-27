#include "EnginePch.h"
#include "GameObject.h"
#include "Include/Component.h"
#include "API/OpenGL/Shader.h"
#include "Renderer/Rendering/RendererAPI.h"
#include "Renderer/Rendering/RenderCommand.h"

namespace Engine
{
	GameObject::GameObject()
		: mTransform(Transform())
		, mIsColliding(false)
	{
	}

	GameObject::GameObject(const Transform& transform)
		: mTransform(transform)
		, mIsColliding(false)
	{}

	GameObject::GameObject(const GameObject& gameObject)
		: mTransform(gameObject.mTransform)
		, mIsColliding(gameObject.mIsColliding)
		, mComponents(gameObject.mComponents)
	{}

	GameObject::GameObject(const GameObject&& gameObject) noexcept
		: mTransform(gameObject.mTransform)
		, mIsColliding(gameObject.mIsColliding)
		, mComponents(gameObject.mComponents)
	{}

	GameObject& GameObject::operator=(const GameObject& gameObject)
	{
		mTransform = gameObject.mTransform;
		mIsColliding = gameObject.mIsColliding;
		mComponents = gameObject.mComponents;

		return *this;
	}

	GameObject& GameObject::operator=(const GameObject&& gameObject) noexcept
	{
		mTransform = gameObject.mTransform;
		mIsColliding = gameObject.mIsColliding;
		mComponents = gameObject.mComponents;

		return *this;
	}

	GameObject::~GameObject()
	{}

	void GameObject::OnUpdate(const double& delta)
	{
		for (auto kv : mComponents)
		{
			kv.second->OnUpdate(delta);
		}
	}

	// Meant to be overrided
	void GameObject::OnEvent(Event& event)
	{}

	// Meant to be overrided
	void GameObject::OnCollision(const Collision& collision)
	{}
	
	bool GameObject::IsJumping() const
	{
		return false;
	}

	bool GameObject::IsMoving() const
	{
		return false;
	}

	bool GameObject::IsMoveable() const
	{
		return false;
	}

	bool GameObject::IsColliding() const
	{
		return mIsColliding;
	}

	void GameObject::SetIsColliding(bool colliding)
	{
		mIsColliding = colliding;
	}
	
	Transform& GameObject::GetTransform()
	{
		return mTransform;
	}
	
	const Transform& GameObject::GetTransform() const
	{
		return mTransform;
	}

	const Vec3& GameObject::GetFront() const
	{
		float rotation = glm::radians(mTransform.GetRotation().y);

		return Vec3(sin(rotation), 0.0f, cos(rotation));
	}

	void GameObject::SetPosition(const Vec3& position)
	{
		mTransform.SetPosition(position);
	}

	void GameObject::SetRotation(const Vec3& rotation)
	{
		mTransform.SetRotation(rotation);
	}

	void GameObject::SetScale(float scale)
	{
		SetScale(Vec3(scale));
	}

	void GameObject::SetScale(const Vec3& scale)
	{
		mTransform.SetScale(scale);

		auto box    = GetComponent<BoxCollider>();
		auto sphere = GetComponent<SphereCollider>();
		
		if (box)
			box->SetScale(scale);
		if (sphere)
			sphere->SetScale(scale.x);
	}
	void GameObject::Render(Ref<RenderCommand> render_command, Ref<Shader> shader) const
	{
		if (render_command->GetAPI() == API::OpenGL)
		{
			auto& open_gl_shader = std::dynamic_pointer_cast<Engine::OpenGL::Shader>(shader);

			open_gl_shader->UploadUniform("uModel", mTransform.GetModel());
		}
	}
}