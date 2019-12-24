#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/Network.hpp"
#include "SFML/System.hpp"
#include "CWindow.h"
#include "CRectangle.h"
#include "CCircle.h"
#include "CPhysicsEngine.h"

using namespace sf;

#define SQUARE_SIZE Vector2f(32.0f, 32.0f)
#define FPS_CAP 60.0f

void HandleInput(
	const Event& event,
	bool& running
);

int main(int argc, char** argv)
{
	bool running = true;
	// Window
	CWindow window;
	window.Initialize(VideoMode(1280, 720), "Physics Test");
	window.mWindow.setFramerateLimit(FPS_CAP);

	Event event;
	CCircle circle(50.0f, Vector2f(400.0f, 100.0f));
	CRectangle rectangle(SQUARE_SIZE * 2.0f, Vector2f(500.0f, 300.0f));
	CRectangle player(SQUARE_SIZE, Vector2f(150.0f, 100.0f));
	player.AttachRigidBody(new CRigidBody(player));
	//CRectangle floor(Vector2f(window.mWindow.getSize().x * 0.8f, window.mWindow.getSize().y * 0.1f), Vector2f(window.mWindow.getSize().x * 0.5f, window.mWindow.getSize().y * 0.9f));

	// Circle
	circle.setOutlineThickness(3);
	circle.setOutlineColor(Color::White);
	circle.setFillColor(Color::Transparent);

	// Rectangle
	rectangle.setOutlineThickness(2);
	rectangle.setOutlineColor(Color::White);
	rectangle.setFillColor(Color::Transparent);

	// Player
	player.setOutlineThickness(2);
	player.setOutlineColor(Color::Green);
	player.setFillColor(Color::Transparent);

	// Floor
	//floor.setOutlineColor(Color::White);
	//floor.setOutlineThickness(2);
	//floor.setFillColor(Color::Transparent);

	while (running)
	{
		window.mWindow.clear(Color::Black);

		window.mWindow.pollEvent(event);

		HandleInput(event, running);
		CPhysicsEngine::GetInstance()->OnUpdate(1.0f / FPS_CAP);
		//floor.OnUpdate(1.0f / FPS_CAP);
		circle.OnUpdate(1.0f / FPS_CAP);
		rectangle.OnUpdate(1.0f / FPS_CAP);
		player.OnUpdate(1.0f / FPS_CAP);

		if (player.mIsColliding)
		{
			player.setOutlineColor(Color::Red);
		}
		else
			player.setOutlineColor(Color::Green);

		//window.mWindow.draw(floor);
		window.mWindow.draw(circle);
		window.mWindow.draw(rectangle);
		window.mWindow.draw(player);
		window.mWindow.display();
	}

	return 0;
}

void HandleInput(
	const Event& event,
	bool& running
)
{
	/*if (event.type == Event::Closed)
	{
		running = false;
	}
	else */if (event.type == Event::KeyPressed)
	{
		if (event.key.code == Keyboard::Escape)
		{
			running = false;
		}
	}
}
