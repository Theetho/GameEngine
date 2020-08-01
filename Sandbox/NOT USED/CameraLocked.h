#pragma once

class CameraLocked : public Engine::Camera3D
{
public:
	CameraLocked(const Engine::GameObject& target, float distance);
	~CameraLocked();

	void OnUpdate(const double& delta) override;
	void OnEvent(Engine::Event& event) override;
private:
	const Engine::GameObject& mTarget;
	float mAngleAroundTarget;
	float mDistance;

	void  UpdatePosition();
	void  UpdateAngleAroundPlayer();
	void  ClampZoom();
	float GetHorizontalDistance();
	float GetVerticalDistance();
};

