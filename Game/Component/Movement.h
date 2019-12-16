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

	inline void setForwardAxis(
		const Engine::Vec3& axis
	)
	{
		m_axis["Forward"] = glm::normalize(axis);
		m_axis["Side"]  = glm::cross(m_axis["Forward"], m_axis["Up"]);

		// the dot product between the forward axis and the z axis is
		// in [-1, 0, 1], which gives [180, 90, 0] with acos.
		m_rotation = glm::degrees(std::acos(glm::dot(m_axis["Forward"], Engine::Vec3(0.0f, 0.0f, 1.0f ))));
		
		// as 0 gives only 90 (where it could be 270)
		if (m_rotation == 90.0f)
		{
			// we add the dot product between the forward axis and the x axis,
			// which is either 0 or 180, which gives 90 or 270.
			m_rotation += glm::degrees(std::acos(glm::dot(m_axis["Forward"], { 1.0f, 0.0f, 0.0f })));
		}
	}

private:
	const float m_speed = 5.0f;
	Engine::Transform& m_transform;
	float m_rotation;
	// [Side, Up, Forward] velocity
	Engine::Vec3 m_velocity;
	std::unordered_map<const char*, Engine::Vec3> m_axis = {
		{ "Forward", Engine::Vec3(0.0f, 0.0f, 1.0f)},
		{ "Up",		 Engine::Vec3(0.0f, 1.0f, 0.0f)},
		{ "Side",	 Engine::Vec3(1.0f, 0.0f, 0.0f)}
	};
};

