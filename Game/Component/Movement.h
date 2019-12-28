#pragma once

class Movement : public Engine::Component
{
public:
	Movement(Engine::GameObject& gameObject);
	~Movement();

	void OnUpdate(const double& delta) override;

	void SetForwardAxis(const Engine::Vec3& axis);
private:
	Engine::Transform& mTransform;
	const float mSpeed = 5.0f;
	float mRotation;
	std::unordered_map<const char*, Engine::Vec3> mAxis = {
		{ "Forward", Engine::Vec3(0.0f, 0.0f, 1.0f)},
		{ "Up",		 Engine::Vec3(0.0f, 1.0f, 0.0f)},
		{ "Side",	 Engine::Vec3(1.0f, 0.0f, 0.0f)}
	};
};

