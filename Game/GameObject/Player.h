#pragma once

class Player : public Engine::DynamicObject
{
public:
	Player();
	~Player();

	void onUpdate(
		const double& delta
	) override;

	void onEvent(
		Engine::Event& event
	) override;

	// TEMPORARY
	inline void setVao(
		const Engine::Ref<Engine::VertexArray>& vao
	)
	{
		m_vao = vao;
	}

	inline void setPosition(
		const Engine::Vec3& position
	)
	{
		m_transform.setPosition(position);
	}

	// TEMPORARY
	inline const Engine::Ref<Engine::VertexArray>& getVao()
	{
		return m_vao;
	}

private:
	// TEMPORARY
	Engine::Ref<Engine::VertexArray> m_vao;
};


