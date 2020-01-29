#pragma once

#include <vector>
#include "SFML/include/SFML/Graphics.hpp"

class HeightMap
{
public:
	HeightMap(unsigned int width, unsigned int height);
	~HeightMap();

	void Generate();

	unsigned int GetWidth() const;
	unsigned int GetHeight() const;
	const std::vector<float>& GetHeightValues() const;
	std::vector<unsigned char>& GetPixelsValue();
	std::vector<unsigned char>& GetColoredMap();
	inline int& GetSeed()
	{
		return mSeed;
	}
	inline size_t& GetOctave()
	{
		return mOctave;
	}
	inline double& GetLacunarity()
	{
		return mLacunarity;
	}
	inline double& GetPersistence()
	{
		return mPersistence;
	}
	inline double& GetScale()
	{
		return mScale;
	}

private:
	unsigned mWidth, mHeight;
	std::vector<float> mHeightValues;
	std::vector<unsigned char> mPixels;
	std::vector<unsigned char> mColors;
	double mMin = std::numeric_limits<double>::max();
	double mMax = std::numeric_limits<double>::min();
	int    mSeed;
	size_t mOctave;
	double mLacunarity;
	double mPersistence;
	double mScale;
	bool mPixelsNeedUpdate, mColorsNeedUpdate;

	sf::Color ApplyColor(float grey_scale) const;
};

