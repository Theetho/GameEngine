#pragma once

class TerrainConfiguration
{
public:
	TerrainConfiguration(const std::string& path);
	~TerrainConfiguration();

	float GetScaleXZ() const;
	float GetScaleY() const;
	float GetTesselationSlope() const;
	float GetTesselationShift() const;
	int   GetTesselationFactor() const;
	std::array<int, 8> GetLodRange() const;
	std::array<int, 8> GetLodMorphingArea() const;
	Engine::Ref<Engine::Texture2D> GetHeightMap() const;
	Engine::Ref<Engine::Texture2D> GetNormalMap() const;
private:
	float mScaleY, mScaleXZ;
	float mTesselationSlope, mTesselationShift;
	int   mTesselationFactor;
	std::array<int, 8> mLodRange;
	std::array<int, 8> mLodMorphingArea;
	Engine::Ref<Engine::Texture2D> mHeightMap, mNormalMap;
	
	int CalculateMorphingArea(int lod) const;
};

