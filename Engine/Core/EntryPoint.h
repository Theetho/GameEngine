#pragma once

#ifdef ENGINE_WINDOWS

extern Engine::Application* Engine::createApplication();

namespace Engine
{
	void init()
	{
		Engine::Log::init();
		Engine::Input::Create();
		Engine::Shader::setFolder("../Engine/Assets/Shaders/");
		Engine::Texture::setFolder("../Engine/Assets/Textures/");
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