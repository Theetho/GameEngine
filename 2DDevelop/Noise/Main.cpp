#include "stb_image.h"
#include "stb_image_write.h"
#include <iostream>
#include <sstream>
#include <array>
#include <iostream>

#include "FastNoise.h"
#include "UILib/UILib.h"
#include "HeightMap.h"
#include "NormalMap.h"

using namespace sf;

enum _Image { HEIGHTMAP, NORMALMAP, COLORED };

namespace Shared
{
	int _width    = 1024;
	int _height   = 1024;
	int _channels = 4;
	Font _font;
	Vector2f _mouse_position;
	Vector2f _previous_mouse_position;
	Vector2f _mouse_movement;
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

	HeightMap height_map(Shared::_width, Shared::_height);
	height_map.Generate();
	NormalMap normal_map(height_map);
	normal_map.Generate();

	UILib::Window window(1280, 720, "HeightMap");
	bool running = true;
	_Image image = HEIGHTMAP;

	// Height map
	Texture texture;
	texture.create(Shared::_width, Shared::_height);
	Sprite map(texture);
	map.setScale(512.f / (float)Shared::_width, 512.f / (float)Shared::_height);
	map.setPosition(window.GetWidth() / 2 - map.getGlobalBounds().width / 2, window.GetHeight() / 2 - map.getGlobalBounds().height / 2);

	int& seed = height_map.GetSeed();
	auto generate_height_map = std::bind(&HeightMap::Generate, &height_map);
	auto generate_normal_map = std::bind(&NormalMap::Generate, &normal_map);

	auto save_image = [&image, &height_map, &normal_map]()
	{
			std::ostringstream name;
			name << "Heightmap_" <<
					height_map.GetSeed() << "_" <<
				    height_map.GetOctave() << "_" <<
				    height_map.GetLacunarity() << "_" <<
				    height_map.GetPersistence() << "_" <<
				    height_map.GetScale() << ".png";

			stbi_write_png(("../Game/Assets/Textures/Terrain/" + name.str()).c_str(), Shared::_width, Shared::_height, Shared::_channels, height_map.GetPixelsValue().data(), Shared::_width * Shared::_channels);
			std::cout << "Heightmap saved " << std::endl;

			name.str("");

			name << "Normalmap_" <<
				height_map.GetSeed() << "_" <<
				height_map.GetOctave() << "_" <<
				height_map.GetLacunarity() << "_" <<
				height_map.GetPersistence() << "_" <<
				height_map.GetScale() << ".png";

			stbi_write_png(("../Game/Assets/Textures/Terrain/" + name.str()).c_str(), Shared::_width, Shared::_height, Shared::_channels, normal_map.GetPixelsValue().data(), Shared::_width * Shared::_channels);
			std::cout << "Normalmap saved " << std::endl;
	};

	Uint8* pixels = height_map.GetPixelsValue().data();
	texture.update(pixels);

	auto switch_image = [&image, &normal_map]()
	{
		if (image == COLORED)
		{
			image = HEIGHTMAP;
		}
		else if (image == HEIGHTMAP)
		{
			image = NORMALMAP;
			normal_map.Generate();
		}
		else if (image == NORMALMAP)
		{
			image = COLORED;
		}
	};

	window.AddUIElement(new UILib::Button(Vector2f(380, 30), [&seed, &generate_height_map](){ seed = rand(); generate_height_map(); }, "Generate"));
	window.AddUIElement(new UILib::Slider<double>(height_map.GetScale(), 0.0, 10.0, 0.01, Vector2f(150, 70), generate_height_map, "Scale"));
	window.AddUIElement(new UILib::Slider<double>(height_map.GetLacunarity(), 1.0, 10.0, 0.1, Vector2f(150, 110), generate_height_map, "Lacunarity"));
	window.AddUIElement(new UILib::Slider<double>(height_map.GetPersistence(), 0.0, 1.0, 0.01, Vector2f(150, 150), generate_height_map, "Persistence"));
	window.AddUIElement(new UILib::Slider<size_t>(height_map.GetOctave(), 1, 8, 1, Vector2f(150, 190), generate_height_map, "Octave"));
	window.AddUIElement(new UILib::Slider<float> (normal_map.GetStrength(), 0.001f, 10.000f, 0.1f, Vector2f(150, 230), generate_normal_map, "Strength"));
	window.GetUIElements().back()->SetCallbackType(UILib::CallbackType::CLICK);
	window.AddUIElement(new UILib::Button(Vector2f(120, 600), save_image, "Save"));
	window.AddUIElement(new UILib::Button(Vector2f(120, 560), switch_image, "Switch texture"));
	window.AddUIElement(new UILib::Input<int>(seed, Vector2f(150, 30), generate_height_map, "Seed"));

	while (running)
	{
		window.Clear(Color(200, 200, 200));

		Event event;
		while (window.PollEvent(event))
		{
			HandleInput(event, running);
		}
		
		if (image == HEIGHTMAP)
			pixels = height_map.GetPixelsValue().data();
		else if (image == NORMALMAP)
			pixels = normal_map.GetPixelsValue().data();
		else if (image == COLORED)
			pixels = height_map.GetColoredMap().data();

		texture.update(pixels);

		window.UpdateUI();
		
		window.RenderUI();
		window.Draw(map);
		window.Display();
	}

	for (auto it : window.GetUIElements()) delete it;

	return 0;
}