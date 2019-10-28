#pragma once

#ifdef ENGINE_WINDOWS

extern Engine::Application* Engine::createApplication();

namespace Engine
{
	void init()
	{
		Engine::Log::init();
		Engine::Input::create();
		Engine::Shader::setFolder("../Engine/res/shaders/");
	}
}

int main(int argc, char** argv)
{
	Engine::init();

	Engine::Application *app = Engine::createApplication();
	app->run();
	delete app;
	return 0;
}

#endif // ENGINE_WINDOWS