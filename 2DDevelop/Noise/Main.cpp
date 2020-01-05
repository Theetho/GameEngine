#include "stb_image.h"
#include "stb_image_write.h"
#include <iostream>
#include <sstream>
#include <array>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "FastNoise.h"

#define ApplyFontSize(x, y) x.setCharacterSize(y);\
					    x.setStyle(Text::Regular);\
					    x.setFillColor(Color::White)
#define ApplyFont(x) ApplyFontSize(x, 30)

using namespace sf;

namespace Shared
{
	int _width    = 256;
	int _height   = 256;
	int _channels = 4;
	std::vector<unsigned char> _height_map;
	Font _font;
	Vector2f _mouse_position;
	Vector2f _previous_mouse_position;
	Vector2f _mouse_movement;
}

struct Data
{
	int    seed;
	size_t octave;
	double lacunarity;
	double persistence;
	double scale;
};

class Button : public Drawable
{
public:
	Button(const char* label, const Vector2f& position)
		: mLabel(label, Shared::_font)
	{
		mLabel.setPosition(position);
		ApplyFont(mLabel);
	}
	~Button(){}
	void OnUpdate()
	{
		mLabel.setFillColor(Color::White);

		float left   = mLabel.getGlobalBounds().left;
		float top    = mLabel.getGlobalBounds().top;
		float right  = left + mLabel.getGlobalBounds().width;
		float bottom = top  + mLabel.getGlobalBounds().height;

		if (Shared::_mouse_position.x >= left && Shared::_mouse_position.x <= right && Shared::_mouse_position.y >= top && Shared::_mouse_position.y <= bottom)
		{
			mLabel.setFillColor(Color(128,0,0));
			if (Mouse::isButtonPressed(Mouse::Button::Left))
			{
				mClick = true;
			}
			else if (mClick)
			{
				const char* path = "../Game/Assets/Textures/Heightmaps/generated_height_map.png";
				stbi_write_png(path, Shared::_width, Shared::_height, Shared::_channels, Shared::_height_map.data(), Shared::_width * Shared::_channels);
				std::cout << "Image saved at " << path << std::endl;
				mClick = false;
			}
		}
	}

private:
	Text mLabel;
	bool	 mClick = false;

	virtual void draw(RenderTarget& target, RenderStates states) const override
	{
		target.draw(mLabel);
	}
};

class Slider : public Drawable
{
public:
	Slider(double min, double max, Vector2f position, double* value)
		: mMax(max)
		, mMin(min)
		, mValue((max - min) / (double)2)
		, mShape({ 100, 100 })
		, mLabel("", Shared::_font)
		, mReference(value)
	{
		mShape.setPosition(position);
		mShape.setFillColor(Color::Transparent);

		mLine.setSize(Vector2f(50, 4));
		mLine.setPosition(position + Vector2f(25, 23));
		mLine.setFillColor(Color(128, 128, 128));
		mLine.setOutlineColor(Color(40, 40, 40));
		mLine.setOutlineThickness(1);

		mCursor.setRadius(4);
		mCursor.setPosition(position + Vector2f(46, 21));
		mCursor.setFillColor(Color(128, 128, 128));
		mCursor.setOutlineColor(Color(40, 40, 40));
		mCursor.setOutlineThickness(1);
		
		std::stringstream ss;
		ss << mValue;
		mLabel.setString(ss.str());
		mLabel.setPosition(position + Vector2f(82, 21 - mLabel.getGlobalBounds().height / 2.0f));
		ApplyFontSize(mLabel, 20);
	}
	void OnUpdate()
	{
		if (Mouse::isButtonPressed(Mouse::Button::Left))
			mCursor.setPosition(mCursor.getPosition() + Vector2f(Shared::_mouse_movement.x, 0.0f));
	
		float min_x = mLine.getPosition().x - mCursor.getRadius();
		float max_x = min_x + mLine.getGlobalBounds().width;
		float cursor_x = mCursor.getPosition().x;
		
		mValue = (double)((cursor_x - min_x) / (max_x - min_x));

		std::stringstream ss;
		ss << mValue;
		mLabel.setString(ss.str());
		mLabel.setPosition(mShape.getPosition() + Vector2f(82, 21 - mLabel.getGlobalBounds().height / 2.0f));

		mCursor.setPosition(sf::Vector2f(std::max(std::min(max_x, cursor_x), min_x), mCursor.getPosition().y));
	
		*mReference = mValue;
	}
	double GetValue() const
	{
		return mValue;
	}
private:
	double mMin;
	double mMax;
	double mValue;
	double* mReference;
	double mStep = 0.01;
	Text		   mLabel;
	RectangleShape mLine;
	//RectangleShape mCursor;
	CircleShape    mCursor;
	RectangleShape mShape;

	virtual void draw(RenderTarget& target, RenderStates states) const override
	{
		target.draw(mShape);
		target.draw(mLine);
		target.draw(mCursor);
		target.draw(mLabel);
	}
};

static void GenerateHeightMap(const Data& data, int width, int height, std::vector<unsigned char>& height_map)
{
	height_map.clear();

	FastNoise noise;
	noise.SetNoiseType(FastNoise::PerlinFractal);
	noise.SetSeed(data.seed);
	noise.SetFractalOctaves(data.octave);
	noise.SetFractalLacunarity(data.lacunarity);
	noise.SetFractalGain(data.persistence);

	double max = -6000.0, min = 6000.0;

	for (int row = 0; row < height; ++row)
	{
		for (int column = 0; column < width; ++column)
		{
			double noise_value = noise.GetNoise((double)row / data.scale, (double)column / data.scale);
			max = max < noise_value ? noise_value : max;
			min = min > noise_value ? noise_value : min;
		}
	}
	for (int row = 0; row < height; ++row)
	{
		for (int column = 0; column < width; ++column)
		{
			double noise_value = noise.GetNoise((double)row / data.scale, (double)column / data.scale);
			unsigned char color = ((noise_value - min) / (max - min)) * 255;
			height_map.push_back(color);
			height_map.push_back(color);
			height_map.push_back(color);
			height_map.push_back(255);
		}
	}
}

static void HandleInput(const Event& event, bool& running, Data& data)
{
	if (event.type == Event::Closed)
	{
		running = false;
	}
	else if (event.type == Event::MouseMoved)
	{
		Shared::_previous_mouse_position = Shared::_mouse_position;
		Shared::_mouse_position = Vector2f(event.mouseMove.x, event.mouseMove.y);
		Shared::_mouse_movement = Shared::_mouse_position - Shared::_previous_mouse_position;
	}
	else if (event.type == Event::KeyPressed)
	{
		if (event.key.code == Keyboard::Escape)
		{
			running = false;
		}
		if (event.key.code == Keyboard::M)
		{
			data.seed = rand();
			GenerateHeightMap(data, Shared::_width, Shared::_height, Shared::_height_map);
		}
		if (event.key.code == Keyboard::O)
		{
			if (Keyboard::isKeyPressed(Keyboard::LShift))
			{
				data.octave = (data.octave - 1) % 8;;
			}
			else
			{
				data.octave = (data.octave + 1) % 8;
			}
			GenerateHeightMap(data, Shared::_width, Shared::_height, Shared::_height_map);
		}
		if (event.key.code == Keyboard::L)
		{
			if (Keyboard::isKeyPressed(Keyboard::LShift))
			{
				data.lacunarity /= 2;
			}
			else
			{
				data.lacunarity *= 2;
			}
			data.lacunarity = std::max(0.0625, data.lacunarity);
			GenerateHeightMap(data, Shared::_width, Shared::_height, Shared::_height_map);
		}
		if (event.key.code == Keyboard::D)
		{
			if (Keyboard::isKeyPressed(Keyboard::LShift))
			{
				data.persistence /= 2;
			}
			else
			{
				data.persistence *= 2;
			}
			data.persistence = std::max(pow(2, -32), data.persistence);
			GenerateHeightMap(data, Shared::_width, Shared::_height, Shared::_height_map);
		}
		if (event.key.code == Keyboard::S)
		{
			if (Keyboard::isKeyPressed(Keyboard::LShift))
			{
				data.scale -= 0.01;
			}
			else
			{
				data.scale += 0.01;
			}
			data.scale = std::max(0.0, data.scale);
			data.scale = std::min(1.0, data.scale);
			GenerateHeightMap(data, Shared::_width, Shared::_height, Shared::_height_map);
		}
	}
}

int main()
{
	srand(time(0));

	Data data;

	data.seed = rand();
	data.octave = 8;
	data.lacunarity = 2;
	data.persistence = 0.5;
	data.scale = 0.276;

	GenerateHeightMap(data, Shared::_width, Shared::_height, Shared::_height_map);

	RenderWindow window;
	VideoMode window_size(1280, 720);
	window.create(window_size, "HeightMap");
	bool running = true;

	// Height map
	Texture texture;
	texture.create(Shared::_width, Shared::_height);
	Sprite map(texture);
	map.setScale(2, 2);
	map.setPosition(window_size.width / 2 - map.getGlobalBounds().width / 2, window_size.height / 2 - map.getGlobalBounds().height / 2);

	// Instructions
	Shared::_font.loadFromFile("Noise/Font/consola.ttf");
	Text instructions("init", Shared::_font);
	ApplyFont(instructions);

	Button save("Save", Vector2f(window_size.width * 0.05f, window_size.height * 0.8f));
	std::array<Slider, 3> sliders{
		Slider(0, 1, { 50, 540 }, &data.scale),
		Slider(0, 1, { 50, 600 }, &data.lacunarity),
		Slider(0, 1, { 50, 660 }, &data.persistence)
	};

	while (running)
	{
		window.clear(Color::Black);

		Event event;
		window.pollEvent(event);

		HandleInput(event, running, data);

		save.OnUpdate();
		for (auto slider : sliders)
			slider.OnUpdate();

		Uint8* pixels = Shared::_height_map.data();
		texture.update(pixels);
		
		std::stringstream ss;
		ss <<
		"(m)seed       : " << data.seed <<
		"\n(s)scale      : " << data.scale <<
		"\n(o)octave	 : " << data.octave <<
		"\n(l)lacunarity : " << data.lacunarity <<
		"\n(d)persistence: " << data.persistence;
		instructions.setString(ss.str().c_str());
		
		window.draw(map);
		window.draw(instructions);
		window.draw(save);
		for (auto slider : sliders)
			window.draw(slider);
		window.display();
	}

	return 0;
}