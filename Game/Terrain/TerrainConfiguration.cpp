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
	mTBNRange		   = cf.GetValueAt<int>("TBNRange");

	for (int i = 1; i < cf.GetValueAt<int>("Materials") + 1; ++i)
	{
		mMaterials.push_back(TerrainMaterial(
			cf.GetValueAt<std::string>("Material" + std::to_string(i) + "DIF"),
			cf.GetValueAt<std::string>("Material" + std::to_string(i) + "NRM"),
			cf.GetValueAt<std::string>("Material" + std::to_string(i) + "DSP"),
			cf.GetValueAt<float>	  ("Material" + std::to_string(i) + "HorizontalScaling"),
			cf.GetValueAt<float>	  ("Material" + std::to_string(i) + "VerticalScaling")
		));
	}

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
	
	int N = mHeightMap->GetWidth();

	// Normal Map
	unsigned int id;
	glGenTextures(1, &id);
	mNormalMap = CreateRef<OpenGL::Texture2D>(N, N, id);
	mNormalMap->Bind();
	mNormalMap->BilinearFilter();
	glTexStorage2D(GL_TEXTURE_2D, (int)(log(N) / log(2)), GL_RGBA32F, N, N);
	auto compute_shader = AssetManager::GetShaderLibrary().Load("ComputeNormalMap.glsl");
	compute_shader->Bind();
	compute_shader->UploadUniform("uHeightMap", 1);
	mHeightMap->Bind(1);
	compute_shader->UploadUniform("uStrength", 60.0f);
	compute_shader->UploadUniform("uResolution", N);
	glBindImageTexture(0, id, 0, false, 0, GL_WRITE_ONLY, GL_RGBA32F);
	glDispatchCompute(N / 16, N / 16, 1);
	glFinish();
	mNormalMap->Bind();
	mNormalMap->BilinearFilter();

	// Splat Map
	glGenTextures(1, &id);
	mSplatMap = CreateRef<OpenGL::Texture2D>(N, N, id);
	mSplatMap->Bind();
	mSplatMap->BilinearFilter();
	glTexStorage2D(GL_TEXTURE_2D, (int)(log(N) / log(2)), GL_RGBA16F, N, N);
	compute_shader.reset();
	compute_shader = AssetManager::GetShaderLibrary().Load("ComputeSplatMap.glsl");
	compute_shader->Bind();
	compute_shader->UploadUniform("uNormalMap", 1);
	mNormalMap->Bind(1);
	compute_shader->UploadUniform("uResolution", N);
	glBindImageTexture(0, id, 0, false, 0, GL_WRITE_ONLY, GL_RGBA16F);
	glDispatchCompute(N / 16, N / 16, 1);
	glFinish();
	mSplatMap->Bind();
	mSplatMap->BilinearFilter();
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

int TerrainConfiguration::GetTBNRange() const
{
	return mTBNRange;
}

const std::array<int, 8>& TerrainConfiguration::GetLodRange() const
{
	return mLodRange;
}

const std::array<int, 8>& TerrainConfiguration::GetLodMorphingArea() const
{
	return mLodMorphingArea;
}

const std::vector<TerrainMaterial>& TerrainConfiguration::GetMaterials() const
{
	return mMaterials;
}

Engine::Ref<Engine::Texture2D> TerrainConfiguration::GetHeightMap() const
{
	return mHeightMap;
}

Engine::Ref<Engine::Texture2D> TerrainConfiguration::GetNormalMap() const
{
	return mNormalMap;
}

Engine::Ref<Engine::Texture2D> TerrainConfiguration::GetSplatMap() const
{
	return mSplatMap;
}

int TerrainConfiguration::CalculateMorphingArea(int lod) const
{
	return (int)((mScaleXZ / TerrainQuadTree::GetRootNodesCount()) / pow(2, lod));
}
