#pragma once

#include "Floor.h"

class ExitCell : public Floor
{
public:
	ExitCell(
		const Engine::Transform& transform = Engine::Transform()
	);
	~ExitCell();

	const Engine::Ref<Engine::Model> getModel() const override
	{
		return s_model;
	}
private:
	static Engine::Ref<Engine::Model> s_model;
	static bool s_isInitialized;
};

