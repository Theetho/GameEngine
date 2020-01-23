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
	
	for (unsigned int i = 0; i < mLodRange.size(); i++)
	{
		mLodRange[i]		= cf.GetValueAt<unsigned int>("LodRange" + std::to_string(i));
		mLodMorphingArea[i] = mLodRange[i] - CalculateMorphingArea(mLodRange[i] + 1);
	}
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

unsigned int TerrainConfiguration::CalculateMorphingArea(unsigned int lod) const
{
	return (mScaleXZ / TerrainQuadTree::GetRootNodesCount()) / pow(2, lod);
}
