#pragma once

#include "Map/Map.h"

class Bomb : public Engine::GameObject
{
public:
	Bomb(Engine::Ref<Engine::Model> model, const Engine::Transform& transform = Engine::Transform(), float power = 1.5f);
	~Bomb();

	void OnUpdate(const double& delta) override;
	void IncreasePower();

	const Engine::Model& GetModel() const;
	void GetSurroundingWalls(Map& world_map);

	void SetModel(Engine::Ref<Engine::Model> model);

	// TEMPORARY
	bool hasExploded = false;
private:
	std::array<Engine::Ref<Engine::RawMaterial>, 2> mMaterials;
	std::vector<DestructibleWall*> mSurroundingWalls;
	Engine::Model mModel;
	bool mMaterial;
	float mPower;

	struct Lifetime
	{
		const double time_until_explosion = 1.0;
		const float scale_factor = 1.5f;
		// { Step, Time, MaxTime }
		std::array<double, 3> time_explosion = { 0.15, 1.0, 2.0};
		std::array<double, 3> time_actual_explosion = { 0.04, 2.0, 2.16};
		double lifetime = 0.0;
	};
	Lifetime mLifetime;

	bool AreAlignOnAxis(float min_bomb_point, float max_bomb_point, float min_wall_point, float max_wall_point);
	bool AreCloseEnough(float bomb_radius, float wall_size, float distance);
	void Animate();
	void Explode();
};

