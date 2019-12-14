#pragma once

class Bomb : public Engine::GameObject
{
public:
	Bomb(
		Engine::Ref<Engine::Model> model,
		const Engine::Transform& transform = Engine::Transform()
	);
	~Bomb();

	void onUpdate(
		const double& delta
	) override;

	inline const Engine::Model& getModel() const
	{
		return m_model;
	}

	void setModel(
		Engine::Ref<Engine::Model> model
	);

	// TEMPORARY
	bool hasExploded = false;

private:
	std::array<Engine::Ref<Engine::RawMaterial>, 2> m_materials;
	Engine::Model m_model;
	bool m_material;

	struct Lifetime
	{
		const double timeUntilExplosion = 500.0;
		const float scaleFactor = 2.0f;
		// { Step, Time, MaxTime }
		std::array<double, 3> timesExplosion = { 100.0, 500.0, 1300.0};
		std::array<double, 3> timesActualExplosion = { 50.0, 1300.0, 1500.0};
		double lifetime = 0.0;
	};
	Lifetime m_lifetime;

	void explode();
};

