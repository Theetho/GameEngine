#pragma once

class Cube : public Engine::Entity
{
public:
	explicit Cube(
		const float& size = 1.0,
		const Engine::Transform& transform = Engine::Transform(),
		Engine::Material* material = nullptr,
		Engine::Texture* texture = nullptr
	);
	~Cube();

	void onUpdate() override;
	
	inline const Engine::Ref<Engine::VertexArray>& getVao() const
	{
		return m_vao;
	}

private:
	Engine::Ref<Engine::VertexArray> m_vao;
	float m_size;
};

