#pragma once

#ifdef ENGINE_WINDOWS

extern Engine::Application* Engine::CreateApplication();

namespace Engine
{
	void Initialize()
	{
		Engine::Log::Initialize();
		Engine::Input::Create();
	}
}

int main(int argc, char** argv)
{
	Engine::Initialize();

	Engine::Application *app = Engine::CreateApplication();
	app->Run();
	delete app;
	return 0;
}

#endif // ENGINE_WINDOWS