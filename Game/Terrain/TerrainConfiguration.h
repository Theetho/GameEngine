#pragma once

class TerrainConfiguration
{
public:
	TerrainConfiguration(const std::string& path);
	~TerrainConfiguration();

	float GetScaleXZ() const;
	float GetScaleY() const;
private:
	float mScaleY;
	float mScaleXZ;
	std::array<unsigned int, 8> mLodRange;
	std::array<unsigned int, 8> mLodMorphingArea;
	
	unsigned int CalculateMorphingArea(unsigned int lod) const;
};

