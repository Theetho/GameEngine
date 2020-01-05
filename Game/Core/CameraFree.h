#pragma once

#include "Component/Movement.h"

class CameraFree : public Engine::Camera3D
{
public:
	CameraFree(const Engine::Vec3& position = Engine::Vec3(0.0f, 1.0f, 0.0f));
	~CameraFree();

	void OnUpdate(const double& delta) override;
	void OnEvent(Engine::Event& event) override;
private:
	const float  mSpeed = 20.0f;
	Engine::Vec3 mVelocity;
};

