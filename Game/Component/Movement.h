#pragma once

class Movement : public Engine::Component
{
public:
	Movement(
		Engine::GameObject& owner
	);

	~Movement() {}

	virtual void onUpdate(
		const double& delta
	) override;

private:
	const float m_speed = 5.0f;
	Engine::Transform& m_transform;
	Engine::Vec3 m_velocity;
};

