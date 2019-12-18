#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/Network.hpp"
#include "SFML/System.hpp"

using namespace sf;

#define SPEED 10.0f
#define SQUARE_SIZE Vector2f(32.0f, 32.0f)

void HandleInput(
	const Event& event,
	bool& running
);

void MoveRectangle(
	Vector2f& rectangle_position
);

int main(int argc, char** argv)
{
	bool running = true;
	RenderWindow window;
	Event event;
	CircleShape circle;
	Vector2f circle_position = Vector2f(400.0f, 100.0f);
	RectangleShape rectangle;
	Vector2f rectangle_position = Vector2f(150.0f, 150.0f);
	RectangleShape floor;

	// Window
	window.create(VideoMode(1280, 720), "Physics Test");
	window.setFramerateLimit(60);

	// Circle
	circle.setPosition(circle_position);
	circle.setRadius(50.0f);
	circle.setOutlineThickness(3);
	circle.setOutlineColor(Color::Red);
	circle.setFillColor(Color::Transparent);

	// Cube
	rectangle.setPosition(rectangle_position);
	rectangle.setSize(SQUARE_SIZE);
	rectangle.setOutlineThickness(2);
	rectangle.setOutlineColor(Color::Green);
	rectangle.setFillColor(Color::Transparent);

	// Floor
	floor.setPosition(-10.0, window.getSize().y * 0.95);
	floor.setSize(Vector2f(window.getSize().x * 1.05f, window.getSize().y * 0.10f));
	floor.setOutlineColor(Color::White);
	floor.setOutlineThickness(2);
	floor.setFillColor(Color::Transparent);

	while (running)
	{
		window.clear(Color::Black);

		window.pollEvent(event);

		HandleInput(event, running);
		MoveRectangle(rectangle_position);

		rectangle.setPosition(rectangle_position);

		window.draw(floor);
		window.draw(circle);
		window.draw(rectangle);

		window.display();
	}

	return 0;
}

void HandleInput(
	const Event& event,
	bool& running
)
{
	if (event.type == Event::Closed)
	{
		running = false;
	}
	else if (event.type == Event::KeyPressed)
	{
		if (event.key.code == Keyboard::Escape)
		{
			running = false;
		}
	}
}

void MoveRectangle(
	Vector2f& rectangle_position
)
{
	if (Keyboard::isKeyPressed(Keyboard::Z))
	{
		rectangle_position.y -= SPEED;
	}
	if (Keyboard::isKeyPressed(Keyboard::S))
	{
		rectangle_position.y += SPEED;
	}
	if (Keyboard::isKeyPressed(Keyboard::Q))
	{
		rectangle_position.x -= SPEED;
	}
	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		rectangle_position.x += SPEED;
	}
}