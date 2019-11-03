#pragma once

class Cube : public Engine::GameObject
{
public:
	explicit Cube(
		const float& size = 1.0,
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

