#pragma once

#ifdef ENGINE_WINDOWS

extern Engine::Application* Engine::createApplication();


int main(int argc, char** argv)
{
	Engine::Log::init();
	Engine::Input::create();

	Engine::Application *app = Engine::createApplication();
	app->run();
	delete app;
	return 0;
}

#endif // ENGINE_WINDOWS