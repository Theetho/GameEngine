#pragma once

#include "HeightMap.h"

class NormalMap
{
public:
	NormalMap(const HeightMap& height_map);
	~NormalMap();

	void Generate();
	std::vector<unsigned char>& GetPixelsValue();
	inline float& GetStrength()
	{
		return mStrength;
	}
private:
	unsigned int mWidth, mHeight;
	float mStrength;
	std::vector<unsigned char> mPixels;
	const HeightMap& mHeightMap;

	void Normalize(float& r, float& g, float& b) const;
};

