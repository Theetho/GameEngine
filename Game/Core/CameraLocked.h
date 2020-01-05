#pragma once

class CameraLocked : public Engine::Camera3DLocked
{
public:
	CameraLocked(const Engine::GameObject& target, float distance);
	~CameraLocked();

	void OnUpdate( const double& delta) override;
	void CalculateAngleAroundPlayer() override;
private:
	void UpdateTargetAxis();
};

