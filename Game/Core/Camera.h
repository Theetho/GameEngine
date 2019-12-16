#pragma once

class Camera : public Engine::Camera3DLocked
{
public:
	Camera(
		const Engine::GameObject& target,
		float distance
	);
	~Camera();

	void onUpdate(
		const double& delta
	) override;

	void calculateAngleAroundPlayer() override;

private:
	void updateTargetAxis();
};

