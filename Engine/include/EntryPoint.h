#pragma once

#ifdef ENGINE_WINDOWS

extern Engine::Application* Engine::createApplication();

int main(int argc, char** argv)
{
	std::cout << "Welcome on the game Engine\n";
	Engine::Log::init();
	ENGINE_LOG_ERROR("Critical error");
	Engine::Window window;
	Engine::Application *app = Engine::createApplication();
	app->run();
	std::cin.get();
	window.close();
	delete app;
	return 0;
}

#endif // ENGINE_WINDOWS