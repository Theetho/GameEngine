#pragma once

class Player : public Engine::GameObject
{
public:
	Player(
		const Engine::Transform& transform = Engine::Transform()
	);
	~Player();

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

	// TEMPORARY
	inline const Engine::Ref<Engine::VertexArray>& getVao()
	{
		return m_vao;
	}

private:
	// TEMPORARY
	Engine::Ref<Engine::VertexArray> m_vao;
};


