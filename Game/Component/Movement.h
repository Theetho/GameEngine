#pragma once

class Movement : public Engine::Component
{
public:
	Movement(Engine::GameObject& game_object, bool is_reversed = false);
	~Movement();

	void OnUpdate(const double& delta) override;

	//void SetForwardAxis(const Engine::Vec3& axis);
private:
	Engine::Ref<Engine::RigidBody> mRigidBody;
	struct Speed
	{
		float current;
		float angular = 50.0f;
		const float max = 100.0f;
		const float min = 25.0f;
	};
	Speed mSpeed;
	// For camera for example;
	const bool mIsReversed;
	//float mRotation;
	//std::unordered_map<const char*, Engine::Vec3> mAxis = {
	//	{ "Forward", Engine::Vec3(0.0f, 0.0f, 1.0f)},
	//	{ "Up",		 Engine::Vec3(0.0f, 1.0f, 0.0f)},
	//	{ "Side",	 Engine::Vec3(1.0f, 0.0f, 0.0f)}
	//};
};

