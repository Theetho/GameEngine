#pragma once

class Wall : public Engine::GameObject
{
public:
	Wall(
		const Engine::Transform& transform
	);
	virtual ~Wall();

	virtual inline const Engine::Ref<Engine::Model> getModel() const
	{
		return Wall::s_model;
	}

private:
	static Engine::Ref<Engine::Model> s_model;
	static bool s_isInitialized;
};

