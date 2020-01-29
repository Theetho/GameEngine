#include "NormalMap.h"

NormalMap::NormalMap(const HeightMap& height_map)
	: mHeightMap(height_map)
	, mWidth(height_map.GetWidth())
	, mHeight(height_map.GetHeight())
	, mStrength(2.5f)
{
}

NormalMap::~NormalMap()
{
}

void NormalMap::Generate()
{
	mPixels.clear();

	auto& hm = mHeightMap.GetHeightValues();

	for (int row = 0; row < mHeight; ++row)
	{
		for (int column = 0; column < mWidth; ++column)
		{
			/*
				* z0  z1  z2
				*
				* z3  px  z4
				*
				* z5  z6  z7
				*/

			int z0 = (row == 0 ? 0 : row == mHeight - 1 ? mHeight - 2 : row - 1) * mWidth + (column == 0 ? 0 : column == mWidth - 1 ? mWidth - 2 : column - 1);
			int z1 = z0 + 1;
			int z2 = z1 + 1;
			int z3 = z0 + mWidth;
			int z4 = z3 + 2;
			int z5 = z3 + mWidth;
			int z6 = z5 + 1;
			int z7 = z6 + 1;

			// r g b a
			float r = hm[z0] + 2 * hm[z3] + hm[z5] - hm[z2] - 2 * hm[z4] - hm[z7];
			float g = hm[z0] + 2 * hm[z1] + hm[z2] - hm[z5] - 2 * hm[z6] - hm[z7];
			float b = 1.0f / (float)mStrength;

			Normalize(r, g, b);

			mPixels.push_back(unsigned char((r + 1) * (255 / 2.0f)));
			mPixels.push_back(unsigned char((g + 1) * (255 / 2.0f)));
			mPixels.push_back(unsigned char((b + 1) * (255 / 2.0f)));
			mPixels.push_back(255);
		}
	}
}

std::vector<unsigned char>& NormalMap::GetPixelsValue()
{
	return mPixels;
}

void NormalMap::Normalize(float& r, float& g, float& b) const
{
	float sum = sqrt(r * r + g * g + b * b);
	r /= sum; b /= sum; g /= sum;
}
