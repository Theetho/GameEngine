#pragma once

class Camera : public Engine::Camera3DLocked
{
public:
	Camera(const Engine::GameObject& target, float distance);
	~Camera();

	void OnUpdate( const double& delta) override;
	void CalculateAngleAroundPlayer() override;
private:
	void UpdateTargetAxis();
};

