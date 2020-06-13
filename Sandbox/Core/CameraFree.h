#pragma once

class CameraFree : public Engine::Camera3D
{
public:
	CameraFree(const Engine::Vec3& position = Engine::Vec3(0.0f, 1.0f, 0.0f));
	~CameraFree();

	void OnUpdate(const double& delta) override;
	//void OnCollision(const Engine::Collision& collision) override;
};

