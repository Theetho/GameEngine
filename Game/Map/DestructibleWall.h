#pragma once

#include "Wall.h"

class DestructibleWall : public Wall
{
public:
	DestructibleWall(
		const Engine::Transform& transform
	);
	~DestructibleWall();

	inline const Engine::Ref<Engine::Model> getModel() const override
	{
		return s_model;
	} 

	inline bool isEnabled() const
	{
		return m_enable;
	}

	void explode();

	bool hasExploded = false;
private:
	static Engine::Ref<Engine::Model> s_model;
	static bool s_isInitialized;
	bool m_enable = true;

	void disable();
	
};

