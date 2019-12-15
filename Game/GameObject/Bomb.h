#pragma once

#include "Map/Map.h"

class Bomb : public Engine::GameObject
{
public:
	Bomb(
		Engine::Ref<Engine::Model> model,
		const Engine::Transform& transform = Engine::Transform(),
		float power = 1.5f
	);
	~Bomb();

	void onUpdate(
		const double& delta
	) override;

	inline void increasePower()
	{
		m_power += 1.0f;
	}

	inline const Engine::Model& getModel() const
	{
		return m_model;
	}

	void setModel(
		Engine::Ref<Engine::Model> model
	);

	void getSurroundingWalls(
		Map& worldMap
	);

	// TEMPORARY
	bool hasExploded = false;

private:
	std::array<Engine::Ref<Engine::RawMaterial>, 2> m_materials;
	std::vector<DestructibleWall*> m_surroundingWalls;
	Engine::Model m_model;
	bool m_material;
	float m_power;

	struct Lifetime
	{
		const double timeUntilExplosion = 1.0;
		const float scaleFactor = 1.5f;
		// { Step, Time, MaxTime }
		std::array<double, 3> timesExplosion = { 0.15, 1.0, 2.0};
		std::array<double, 3> timesActualExplosion = { 0.04, 2.0, 2.16};
		double lifetime = 0.0;
	};
	Lifetime m_lifetime;

	bool areAlignOnAxis(
		float minBombPoint,
		float maxBombPoint,
		float minWallPoint,
		float maxWallPoint
	);

	bool areCloseEnough(
		float bombRadius,
		float wallSize,
		float distance
	);

	void animate();
	void explode();
};

