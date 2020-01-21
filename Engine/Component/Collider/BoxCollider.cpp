#include "EnginePch.h"
#include "BoxCollider.h"
#include "Include/GameObject.h"
#include "System/CollisionSystem.h"
#include "Core/AssetManager.h"
#include "API/OpenGL/OpenGLShader.h"
#include "Renderer/Rendering/RenderCommand.h"
#include "Renderer/Rendering/RendererAPI.h"
#include "Include/Model.h"

namespace Engine
{
	BoxCollider::BoxCollider(GameObject& game_object, const Vec3& center, const Vec3& bounds)
		: Collider(game_object, center)
		, mWidth(bounds.x / 2.0f)
		, mHeight(bounds.y / 2.0f)
		, mDepth(bounds.z / 2.0f)
		, mMaxExtent(center + Vec3(mWidth, mHeight, mDepth))
		, mMinExtent(center - Vec3(mWidth, mHeight, mDepth))
	{
		CollisionSystem::AddCollider<BoxCollider>(this);
	}

	BoxCollider::BoxCollider(const BoxCollider& box_collider)
		: Collider(box_collider.mGameObject, box_collider.mCenter)
		, mMaxExtent(box_collider.mMaxExtent)
		, mMinExtent(box_collider.mMinExtent)
		, mWidth(box_collider.mWidth)
		, mHeight(box_collider.mHeight)
		, mDepth(box_collider.mDepth)
	{
		CollisionSystem::AddCollider<BoxCollider>(this);
	}

	BoxCollider::BoxCollider(const BoxCollider&& box_collider) noexcept
		: Collider(box_collider.mGameObject, box_collider.mCenter)
		, mMaxExtent(box_collider.mMaxExtent)
		, mMinExtent(box_collider.mMinExtent)
		, mWidth(box_collider.mWidth)
		, mHeight(box_collider.mHeight)
		, mDepth(box_collider.mDepth)
	{
		CollisionSystem::AddCollider<BoxCollider>(this);
	}

	BoxCollider& BoxCollider::operator=(const BoxCollider& box_collider)
	{
		*this = BoxCollider(box_collider);

		CollisionSystem::AddCollider<BoxCollider>(this);

		return *this;
	}

	BoxCollider& BoxCollider::operator=(const BoxCollider&& box_collider) noexcept
	{
		*this = BoxCollider(box_collider);

		CollisionSystem::AddCollider<BoxCollider>(this);

		return *this;
	}

	BoxCollider::~BoxCollider()
	{
		CollisionSystem::RemoveCollider(this);
	}
	
	void BoxCollider::OnUpdate(const double& delta)
	{
		Collider::OnUpdate(delta);

		mMaxExtent = mCenter + Vec3(mWidth, mHeight, mDepth);
		mMinExtent = mCenter - Vec3(mWidth, mHeight, mDepth);
	}

	const Vec3& BoxCollider::GetMax() const
	{
		return mMaxExtent;
	}

	const Vec3& BoxCollider::GetMin() const
	{
		return mMinExtent;
	}

	void BoxCollider::SetScale(const Vec3& scale)
	{
		mWidth  *= scale.x;
		mHeight *= scale.y;
		mDepth  *= scale.z;
	}

	void BoxCollider::SetScale(float scale)
	{
		SetScale(Vec3(scale));
	}

	void BoxCollider::UpdateCollisionSystem()
	{
		CollisionSystem::RemoveCollider(this);
		CollisionSystem::AddCollider<BoxCollider>(this);
	}

	void BoxCollider::Render(Ref<RenderCommand> render_command, Ref<Shader> shader) const
	{
		Transform transform;
		transform.SetPosition(mCenter);
		transform.SetScale(mMaxExtent - mMinExtent);

		if (render_command->GetAPI() == API::OpenGL)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

			auto& open_gl_shader = std::dynamic_pointer_cast<Engine::OpenGLShader>(shader);

			open_gl_shader->UploadUniform("uModel", transform.GetModel());
		}

		for (auto& mesh : AssetManager::GetModelLibrary().Get("wall")->GetMeshes())
		{
			Renderable::Render(&mesh, render_command, shader);
		}

		if (render_command->GetAPI() == API::OpenGL)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
	}
}
