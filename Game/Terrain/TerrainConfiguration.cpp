#include "pch.h"
#include "TerrainConfiguration.h"
#include "TerrainQuadTree.h"

using namespace Engine;

TerrainConfiguration::TerrainConfiguration(const std::string& path)
	: mScaleY(0.0f)
	, mScaleXZ(0.0f)
	, mLodRange()
	, mLodMorphingArea()
{
	ConfigFile cf(path);
	mScaleY  = cf.GetValueAt<float>("ScaleY");
	mScaleXZ = cf.GetValueAt<float>("ScaleXZ");
	mTesselationSlope  = cf.GetValueAt<float>("TesselationSlope");
	mTesselationShift  = cf.GetValueAt<float>("TesselationShift");
	mTesselationFactor = cf.GetValueAt<int>("TesselationFactor");
	
	for (int i = 0; i < mLodRange.size(); i++)
	{
		mLodRange[i] = cf.GetValueAt<int>("LodRange" + std::to_string(i + 1));
		if (mLodRange[i] == 0)
		{
			mLodMorphingArea[i] = 0;
		}
		else
		{
			mLodMorphingArea[i] = mLodRange[i] - CalculateMorphingArea(i + 1);
		}
	}

	mHeightMap = Texture2D::Create(cf.GetValueAt<std::string>("HeightMap"));
	mNormalMap = Texture2D::Create(cf.GetValueAt<std::string>("NormalMap"));
}

TerrainConfiguration::~TerrainConfiguration()
{
}

float TerrainConfiguration::GetScaleXZ() const
{
	return mScaleXZ;
}

float TerrainConfiguration::GetScaleY() const
{
	return mScaleY;
}

float TerrainConfiguration::GetTesselationSlope() const
{
	return mTesselationSlope;
}

float TerrainConfiguration::GetTesselationShift() const
{
	return mTesselationShift;
}

int TerrainConfiguration::GetTesselationFactor() const
{
	return mTesselationFactor;
}

std::array<int, 8> TerrainConfiguration::GetLodRange() const
{
	return mLodRange;
}

std::array<int, 8> TerrainConfiguration::GetLodMorphingArea() const
{
	return mLodMorphingArea;
}

Engine::Ref<Engine::Texture2D> TerrainConfiguration::GetHeightMap() const
{
	return mHeightMap;
}

Engine::Ref<Engine::Texture2D> TerrainConfiguration::GetNormalMap() const
{
	return mNormalMap;
}

int TerrainConfiguration::CalculateMorphingArea(int lod) const
{
	return (int)((mScaleXZ / TerrainQuadTree::GetRootNodesCount()) / pow(2, lod));
}
