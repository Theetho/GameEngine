#include "EnginePch.h"
#include "TerrainCollider.h"
#include "Terrain/Terrain.h"
#include "System/CollisionSystem.h"
#include "Include/GameObject.h"

namespace Engine
{
	Engine::TerrainCollider::TerrainCollider(GameObject& game_object, const Vec3& center)
		: Collider(game_object, center)
	{
		mTerrain = dynamic_cast<Terrain*>(&game_object);
		CollisionSystem::AddTerrain(this);
	}

	TerrainCollider::TerrainCollider(TerrainCollider* terrain_collider)
		: Collider(terrain_collider->mGameObject, terrain_collider->mCenter)
		, mTerrain(terrain_collider->mTerrain)
	{}

	TerrainCollider::TerrainCollider(const TerrainCollider& terrain_collider)
		: Collider(terrain_collider.mGameObject, terrain_collider.mCenter)
		, mTerrain(terrain_collider.mTerrain)
	{}

	TerrainCollider::TerrainCollider(const TerrainCollider&& terrain_collider) noexcept
		: Collider(terrain_collider.mGameObject, terrain_collider.mCenter)
		, mTerrain(terrain_collider.mTerrain)
	{}

	TerrainCollider& TerrainCollider::operator=(const TerrainCollider& terrain_collider)
	{
		*this = TerrainCollider(terrain_collider);

		return *this;
	}

	TerrainCollider& TerrainCollider::operator=(const TerrainCollider&& terrain_collider) noexcept
	{
		*this = TerrainCollider(terrain_collider);

		return *this;
	}

	Engine::TerrainCollider::~TerrainCollider()
	{
		CollisionSystem::RemoveCollider(this);
	}

	// Adaptation of the code in the video of ThinMatrix about terrain collision detection
	float TerrainCollider::GetGroundLevel(const Vec3& position) const
	{
		Vec2 terrain_position = Vec2(mTerrain->GetTransform().GetPosition().x, mTerrain->GetTransform().GetPosition().z);
		Vec2 object_position  = Vec2(position.x, position.z);
		Vec2 object_position_on_terrain = object_position - terrain_position;
		
		Vec2 terrain_grid_size = mTerrain->GetDimensions() / (mTerrain->GetResolution() - 1.0f);
		Vec2 object_grid_on_terrain = glm::floor(object_position_on_terrain / terrain_grid_size);
		
		// Value in [0, 1]
		float object_position_on_grid_x = fmodf(object_position_on_terrain.x, terrain_grid_size.x) / terrain_grid_size.x;
		float object_position_on_grid_z = fmodf(object_position_on_terrain.y, terrain_grid_size.y) / terrain_grid_size.y;
		float which_triangle_of_the_grid = object_position_on_grid_x + object_position_on_grid_z;
		
		if (which_triangle_of_the_grid <= 1.0f)
		{
			// Then we are on the left triangle 
			return MathsFunctions::BarryCentric(
				Vec3(0.f, mTerrain->GetHeight(object_grid_on_terrain.x, object_grid_on_terrain.y), 0.f),
				Vec3(1.f, mTerrain->GetHeight(object_grid_on_terrain.x + 1, object_grid_on_terrain.y), 0.f),
				Vec3(0.f, mTerrain->GetHeight(object_grid_on_terrain.x, object_grid_on_terrain.y + 1), 1.f),
				Vec2(object_position_on_grid_x, object_position_on_grid_z)
			);
		}
		else
		{
			// Else we are on the right triangle
			return MathsFunctions::BarryCentric(
				Vec3(1.f, mTerrain->GetHeight(object_grid_on_terrain.x + 1, object_grid_on_terrain.y), 0.f),
				Vec3(1.f, mTerrain->GetHeight(object_grid_on_terrain.x + 1, object_grid_on_terrain.y + 1), 1.f),
				Vec3(0.f, mTerrain->GetHeight(object_grid_on_terrain.x, object_grid_on_terrain.y + 1), 1.f),
				Vec2(object_position_on_grid_x, object_position_on_grid_z)
			);
		}
	}

	bool TerrainCollider::Contains(const Vec3& position) const
	{
		float top    = mTerrain->GetTransform().GetPosition().y;
		float left   = mTerrain->GetTransform().GetPosition().x;
		float bottom = top + mTerrain->GetDimensions().y;
		float right  = left + mTerrain->GetDimensions().x;


		return position.x >= left && position.y >= top && position.x <= right && position.y <= bottom;
	}

	void TerrainCollider::UpdateCollisionSystem()
	{
	}

	void TerrainCollider::Render(Ref<RenderCommand> render_command, Ref<Shader> shader) const
	{
	}
}
