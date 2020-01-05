#include "core/NoisePerlin.h"
#include "stb_image.h"
#include "stb_image_write.h"
#include <iostream>
#include <sstream>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

namespace Shared
{
	int _width    = 256;
	int _height   = 256;
	int _channels = 4;
	std::vector<unsigned char> _height_map;
	sf::Font _font;
	sf::Vector2f _mouse_position;
}

struct Data
{
	int    seed;
	int    quality;
	size_t octave;
	double frequency;
	double lacunarity;
	double persistence;
	double nscale;
};

class Button : public sf::Drawable
{
public:
	Button(const char* label, const sf::Vector2f& position)
		: mLabel(label, Shared::_font)
	{
		mLabel.setPosition(position);
		mLabel.setCharacterSize(30);
		mLabel.setStyle(sf::Text::Regular);
		mLabel.setFillColor(sf::Color::White);

		mShape = mLabel.getGlobalBounds();
	}
	~Button(){}
	void OnUpdate()
	{
		mLabel.setFillColor(sf::Color::White);

		float left   = mLabel.getGlobalBounds().left;
		float top    = mLabel.getGlobalBounds().top;
		float right  = left + mLabel.getGlobalBounds().width;
		float bottom = top  + mLabel.getGlobalBounds().height;

		if (Shared::_mouse_position.x >= left && Shared::_mouse_position.x <= right && Shared::_mouse_position.y >= top && Shared::_mouse_position.y <= bottom)
		{
			mLabel.setFillColor(sf::Color(128,0,0));
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
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
	sf::FloatRect mShape;
	sf::Text	  mLabel;
	bool		  mClick = false;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		target.draw(mLabel);
	}
};

static void GenerateHeightMap(const Data& data, int width, int height, std::vector<unsigned char>& height_map)
{
	height_map.clear();

	noisepp::PerlinElement2D p2D(data.octave, data.frequency, data.lacunarity, data.persistence, data.seed, data.quality, data.nscale);
	noisepp::Cache cache;

	for (int row = 0; row < height; ++row)
	{
		for (int column = 0; column < width; ++column)
		{
			unsigned char value = 255 - p2D.getValue((double)row / (double)height, (double)column / (double)width, &cache) * 255;

			height_map.push_back(value);
			height_map.push_back(value);
			height_map.push_back(value);
			height_map.push_back(255);
		}
	}
}

static void HandleInput(const sf::Event& event, bool& running, Data& data)
{
	if (event.type == sf::Event::Closed)
	{
		running = false;
	}
	else if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Escape)
		{
			running = false;
		}
		if (event.key.code == sf::Keyboard::M)
		{
			data.seed = rand();
			GenerateHeightMap(data, Shared::_width, Shared::_height, Shared::_height_map);
		}
		if (event.key.code == sf::Keyboard::Q)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
			{
				data.quality = (data.quality + noisepp::NOISE_QUALITY_FAST_HIGH) % (noisepp::NOISE_QUALITY_FAST_HIGH + 1);
			}
			else
			{
				data.quality = (data.quality + 1) % (noisepp::NOISE_QUALITY_FAST_HIGH + 1);
			}
			GenerateHeightMap(data, Shared::_width, Shared::_height, Shared::_height_map);
		}
		if (event.key.code == sf::Keyboard::O)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
			{
				data.octave = (data.octave - 1) % 8;;
			}
			else
			{
				data.octave = (data.octave + 1) % 8;
			}
			GenerateHeightMap(data, Shared::_width, Shared::_height, Shared::_height_map);
		}
		if (event.key.code == sf::Keyboard::F)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
			{
				data.frequency -= 0.2;
			}
			else
			{
				data.frequency += 0.2;
			}
			data.frequency = max(0.2, data.frequency);
			GenerateHeightMap(data, Shared::_width, Shared::_height, Shared::_height_map);
		}
		if (event.key.code == sf::Keyboard::L)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
			{
				data.lacunarity /= 2;
			}
			else
			{
				data.lacunarity *= 2;
			}
			data.lacunarity = max(0.0625, data.lacunarity);
			GenerateHeightMap(data, Shared::_width, Shared::_height, Shared::_height_map);
		}
		if (event.key.code == sf::Keyboard::D)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
			{
				data.persistence /= 2;
			}
			else
			{
				data.persistence *= 2;
			}
			data.persistence = max(0.0625, data.persistence);
			GenerateHeightMap(data, Shared::_width, Shared::_height, Shared::_height_map);
		}
		if (event.key.code == sf::Keyboard::S)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
			{
				data.nscale -= 0.1;
			}
			else
			{
				data.nscale += 0.1;
			}
			data.nscale = max(0.1, data.nscale);
			GenerateHeightMap(data, Shared::_width, Shared::_height, Shared::_height_map);
		}
	}
}

int main()
{
	srand(time(0));

	Data data;

	data.seed = 2049301;
	data.quality = noisepp::NOISE_QUALITY_HIGH;
	data.octave = 8;
	data.frequency = 10;
	data.lacunarity = 2;
	data.persistence = 1;
	data.nscale = 0.3;

	GenerateHeightMap(data, Shared::_width, Shared::_height, Shared::_height_map);

	sf::RenderWindow window;
	sf::VideoMode window_size(1280, 720);
	window.create(window_size, "HeightMap");
	bool running = true;

	// Height map
	sf::Texture texture;
	texture.create(Shared::_width, Shared::_height);
	sf::Sprite map(texture);
	map.setScale(2, 2);
	map.setPosition(window_size.width / 2 - map.getGlobalBounds().width / 2, window_size.height / 2 - map.getGlobalBounds().height / 2);

	// Instructions
	Shared::_font.loadFromFile("Noise/Font/consola.ttf");
	sf::Text instructions("init", Shared::_font);
	instructions.setCharacterSize(30);
	instructions.setStyle(sf::Text::Regular);
	instructions.setFillColor(sf::Color::White);

	Button save("Save", sf::Vector2f(window_size.width * 0.05f, window_size.height * 0.8f));

	while (running)
	{
		window.clear(sf::Color::Black);
		Shared::_mouse_position = window.mapPixelToCoords(sf::Mouse::getPosition(window));

		sf::Event event;
		window.pollEvent(event);

		HandleInput(event, running, data);

		save.OnUpdate();

		sf::Uint8* pixels = Shared::_height_map.data();
		texture.update(pixels);
		
		std::stringstream ss;
		ss <<
		"(m)seed       : " << data.seed <<
		"\n(s)scale      : " << data.nscale <<
		"\n(o)octave	 : " << data.octave <<
		"\n(q)quality    : " << data.quality <<
		"\n(f)frequency  : " << data.frequency <<
		"\n(l)lacunarity : " << data.lacunarity <<
		"\n(d)persistence: " << data.persistence;
		instructions.setString(ss.str().c_str());
		
		window.draw(map);
		window.draw(instructions);
		window.draw(save);
		window.display();
	}

	return 0;
}