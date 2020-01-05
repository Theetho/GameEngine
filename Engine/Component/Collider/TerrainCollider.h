#pragma once

#include "Collider.h"

namespace Engine
{
	class Terrain;

	class TerrainCollider : public Collider
	{
	public:
		TerrainCollider(GameObject& game_object, const Vec3& center);
		TerrainCollider(TerrainCollider* terrain_collider);
		TerrainCollider(const TerrainCollider& terrain_collider);
		TerrainCollider(const TerrainCollider&& terrain_collider) noexcept;
		TerrainCollider& operator=(const TerrainCollider& terrain_collider);
		TerrainCollider& operator=(const TerrainCollider&& terrain_collider) noexcept;
		~TerrainCollider();

		float GetGroundLevel(const GameObject& game_object) const;
	private:
		Terrain* mTerrain;

		void UpdateCollisionSystem() override;
		void Render(Ref<RenderCommand> render_command, Ref<Shader> shader) const override;
	};
}

