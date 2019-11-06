#pragma once

class Cube : public Engine::GameObject
{
public:
	Cube(
		const float& size,
		const Engine::Transform& transform = Engine::Transform()
	);

	~Cube();

	void onUpdate(
		const double& delta
	) override;
	
	inline const Engine::Ref<Engine::VertexArray>& getVao() const
	{
		return m_vao;
	}

private:
	Engine::Ref<Engine::VertexArray> m_vao;
	float m_size;
};

