#include "stb_image.h"
#include "stb_image_write.h"
#include <iostream>
#include <sstream>
#include <array>

#include "FastNoise.h"
#include "UILib/UILib.h"

using namespace sf;

struct Data
{
	int    seed;
	size_t octave;
	double lacunarity;
	double persistence;
	double scale;
};

namespace Shared
{
	int _width    = 1024;
	int _height   = 1024;
	int _channels = 4;
	std::vector<unsigned char> _height_map;
	std::vector<unsigned char> _height_map_colored;
	Font _font;
	Vector2f _mouse_position;
	Vector2f _previous_mouse_position;
	Vector2f _mouse_movement;
	Data _data;
}

static sf::Color ApplyColor(float grey_scale)
{	
	std::map<float, sf::Color> colors{
		{ 0.3f,  sf::Color(10, 75, 120) }, // Deep water
		{ 0.4f,  sf::Color(15, 100, 190) }, // Water
		{ 0.45f, sf::Color(250, 245, 170) }, // Sand
		{ 0.55f, sf::Color(100, 200, 0) }, // Grass 1
		{ 0.6f,  sf::Color(50, 100, 0) }, // Grass 2
		{ 0.7f,  sf::Color(90, 60, 20) }, // Rock 1
		{ 0.9f,  sf::Color(60, 40, 10) }, // Rock 2
		{ 1.0f,  sf::Color(sf::Color::White) }, // Snow
	};
	auto color = colors.begin();
	while (color != colors.end())
	{
		if (grey_scale <= color->first)
		{
			return color->second;
		}
		++color;
	}
}

static void GenerateHeightMap()
{
	Shared::_height_map.clear();
	Shared::_height_map_colored.clear();

	FastNoise noise;
	noise.SetNoiseType(FastNoise::PerlinFractal);
	noise.SetSeed(Shared::_data.seed);
	noise.SetFractalOctaves(Shared::_data.octave);
	noise.SetFractalLacunarity(Shared::_data.lacunarity);
	noise.SetFractalGain(Shared::_data.persistence);

	double max = -6000.0, min = 6000.0;

	for (int row = 0; row < Shared::_height; ++row)
	{
		for (int column = 0; column < Shared::_width; ++column)
		{
			double noise_value = noise.GetNoise((double)row / Shared::_data.scale, (double)column / Shared::_data.scale);
			max = max < noise_value ? noise_value : max;
			min = min > noise_value ? noise_value : min;
		}
	}
	for (int row = 0; row < Shared::_height; ++row)
	{
		for (int column = 0; column < Shared::_width; ++column)
		{
			double noise_value = noise.GetNoise((double)row / Shared::_data.scale, (double)column / Shared::_data.scale);
			unsigned char color = ((noise_value - min) / (max - min)) * 255;
			Shared::_height_map.push_back(color);
			Shared::_height_map.push_back(color);
			Shared::_height_map.push_back(color);
			Shared::_height_map.push_back(255);

			auto colored = ApplyColor((noise_value - min) / (max - min));
			Shared::_height_map_colored.push_back(colored.r);
			Shared::_height_map_colored.push_back(colored.g);
			Shared::_height_map_colored.push_back(colored.b);
			Shared::_height_map_colored.push_back(255);
		}
	}
}

static void HandleInput(const Event& event, bool& running)
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

int main()
{
	srand(time(0));

	Shared::_data.seed = rand();
	Shared::_data.octave = 8;
	Shared::_data.lacunarity = 2;
	Shared::_data.persistence = 0.5;
	Shared::_data.scale = 0.758;

	GenerateHeightMap();

	UILib::Window window(1280, 720, "HeightMap");
	bool running = true;
	bool colored = false;

	// Height map
	Texture texture;
	texture.create(Shared::_width, Shared::_height);
	Sprite map(texture);
	map.setScale(512.f / (float)Shared::_width, 512.f / (float)Shared::_height);
	//map.setScale(2, 2);
	map.setPosition(window.GetWidth() / 2 - map.getGlobalBounds().width / 2, window.GetHeight() / 2 - map.getGlobalBounds().height / 2);

	int& seed = Shared::_data.seed;

	auto save_image = []()
	{
		std::ostringstream name;
		name << Shared::_data.seed << "_" <<
			    Shared::_data.octave << "_" <<
			    Shared::_data.lacunarity << "_" <<
			    Shared::_data.persistence << "_" <<
			    Shared::_data.scale << ".png";

		stbi_write_png(("../Game/Assets/Textures/Heightmaps/" + name.str()).c_str(), Shared::_width, Shared::_height, Shared::_channels, Shared::_height_map.data(), Shared::_width * Shared::_channels);
		std::cout << "Image saved " << std::endl;
	};

	window.AddUIElement(new UILib::Button(Vector2f(380, 30), [&seed](){ seed = rand(); GenerateHeightMap(); }, "Generate"));
	window.AddUIElement(new UILib::Slider<double> (Shared::_data.scale, 0.0, 1.0, 0.01, Vector2f(150, 70), &GenerateHeightMap, "Scale"));
	window.AddUIElement(new UILib::Slider<double> (Shared::_data.lacunarity, 1.0, 10.0, 0.1, Vector2f(150, 110), &GenerateHeightMap, "Lacunarity"));
	window.AddUIElement(new UILib::Slider<double> (Shared::_data.persistence, 0.0, 1.0, 0.01, Vector2f(150, 150), &GenerateHeightMap, "Persistence"));
	window.AddUIElement(new UILib::Slider<size_t> (Shared::_data.octave, 1, 8, 1, Vector2f(150, 190), &GenerateHeightMap, "Octave"));
	window.AddUIElement(new UILib::Button(Vector2f(120, 600),save_image, "Save"));
	window.AddUIElement(new UILib::Button(Vector2f(120, 560), [&colored](){colored = !colored;}, "Color scale"));
	window.AddUIElement(new UILib::Input<int>(seed, Vector2f(150, 30), &GenerateHeightMap, "Seed"));

	while (running)
	{
		window.Clear(Color(200, 200, 200));

		Event event;
		while (window.PollEvent(event))
		{
			HandleInput(event, running);
		}

		window.UpdateUI();

		Uint8* pixels;
		if (colored)
			pixels = Shared::_height_map_colored.data();
		else
			pixels = Shared::_height_map.data();
		texture.update(pixels);
		
		window.RenderUI();
		window.Draw(map);
		window.Display();
	}

	for (auto it : window.GetUIElements()) delete it;

	return 0;
}