#include "HeightMap.h"
#include "FastNoise.h"

HeightMap::HeightMap(unsigned int width, unsigned int height)
	: mWidth(width)
	, mHeight(height)
	, mSeed(rand())
	, mOctave(8)
	, mLacunarity(2.0)
	, mPersistence(0.5)
	, mScale(5.0)
	, mPixelsNeedUpdate(true)
	, mColorsNeedUpdate(true)
{
}

HeightMap::~HeightMap()
{
}

void HeightMap::Generate()
{
	mHeightValues.clear();

	FastNoise noise;
	noise.SetNoiseType(FastNoise::PerlinFractal);
	noise.SetSeed(mSeed);
	noise.SetFractalOctaves(mOctave);
	noise.SetFractalLacunarity(mLacunarity);
	noise.SetFractalGain(mPersistence);

	for (int row = 0; row < mHeight; ++row)
	{
		for (int column = 0; column < mWidth; ++column)
		{
			double noise_value = noise.GetNoise((double)row / mScale, (double)column / mScale);
			if (mMax < noise_value)
				mMax = noise_value;
			if (mMin > noise_value)
				mMin = noise_value;

			mHeightValues.push_back(noise_value);
		}
	}

	mPixelsNeedUpdate = true;
	mColorsNeedUpdate = true;
}

unsigned int HeightMap::GetWidth() const
{
	return mWidth;
}

unsigned int HeightMap::GetHeight() const
{
	return mHeight;
}

const std::vector<float>& HeightMap::GetHeightValues() const
{
	return mHeightValues;
}

std::vector<unsigned char>& HeightMap::GetPixelsValue()
{
	if (mPixelsNeedUpdate)
	{
		mPixels.clear();

		for (auto& pixel : mHeightValues)
		{
			float height = (pixel -mMin) / (mMax - mMin);
			unsigned char color = height * 255;

			mPixels.push_back(color);
			mPixels.push_back(color);
			mPixels.push_back(color);
			mPixels.push_back(255);
		}

		mPixelsNeedUpdate = false;
	}

	return mPixels;
}

std::vector<unsigned char>& HeightMap::GetColoredMap()
{
	if (mColorsNeedUpdate)
	{
		mColors.clear();

		for (auto& pixel : mHeightValues)
		{
			float height = (pixel - mMin) / (mMax - mMin);

			auto colored = ApplyColor(height);

			mColors.push_back(colored.r);
			mColors.push_back(colored.g);
			mColors.push_back(colored.b);
			mColors.push_back(255);
		}

		mColorsNeedUpdate = false;
	}

	return mColors;
}

sf::Color HeightMap::ApplyColor(float grey_scale) const
{
	std::map<float, sf::Color> colors{
		{ 0.3f,  sf::Color(10 , 75 , 120) },    // Deep water
		{ 0.4f,  sf::Color(15 , 100, 190) },    // Water
		{ 0.45f, sf::Color(250, 245, 170) },    // Sand
		{ 0.55f, sf::Color(100, 200, 0  ) },    // Grass 1
		{ 0.6f,  sf::Color(50 , 100, 0  ) },    // Grass 2
		{ 0.7f,  sf::Color(90 , 60 , 20 ) },    // Rock 1
		{ 0.9f,  sf::Color(60 , 40 , 10 ) },    // Rock 2
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

