#pragma once

class Player : public Engine::GameObject
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
		m_cameraController.getTransform().setPosition(position);
	}

	// TEMPORARY
	inline const Engine::Ref<Engine::VertexArray>& getVao()
	{
		return m_vao;
	}

	inline Engine::CameraController& getCameraController()
	{
		return m_cameraController;
	}

	inline const Engine::CameraController& getCameraController() const
	{
		return m_cameraController;
	}
private:
	// TEMPORARY
	Engine::Ref<Engine::VertexArray> m_vao;
	Engine::CameraController         m_cameraController;
};


