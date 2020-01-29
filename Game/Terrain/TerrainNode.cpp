#include "pch.h"
#include "TerrainNode.h"
#include "TerrainQuadTree.h"

using namespace Engine;

TerrainNode::TerrainNode(const PatchVertexArray& vertex_array, const TerrainConfiguration& configuration,
	const Engine::Vec2& location, unsigned int lod, const Engine::Vec2& index)
	: Node()
	, mVertexArray(vertex_array)
	, mIsLeaf(true)
	, mIndex(index)
	, mLod(lod)
	, mLocation(location)
	, mTerrainConfiguration(configuration)
	, mGap(1.f / (TerrainQuadTree::GetRootNodesCount() * pow(2, lod)))
{
	mLocalTransform.SetPosition(Engine::Vec3(location.x, 0, location.y));
	mLocalTransform.SetScale(Engine::Vec3(mGap, 0, mGap));
	
	mGlobalTransform.SetScale(Vec3(configuration.GetScaleXZ(), configuration.GetScaleY(), configuration.GetScaleXZ()));
	mGlobalTransform.SetPosition(Vec3(-configuration.GetScaleXZ(), 0, -configuration.GetScaleXZ()) / 2.f);

	ComputePosition();
}

TerrainNode::~TerrainNode()
{}

void TerrainNode::OnUpdate(const double& delta, Engine::Camera3D & camera)
{
	if (camera.GetPosition().y > mTerrainConfiguration.GetScaleY())
		mPosition.y = mTerrainConfiguration.GetScaleY();
	else
		mPosition.y = camera.GetPosition().y;

	UpdateChildren(camera);

	for (auto child : mChildren)
		static_cast<TerrainNode*>(child)->OnUpdate(delta, camera);
}

void TerrainNode::UpdateChildren(Engine::Camera3D& camera)
{
	float distance = glm::distance(camera.GetPosition(), mPosition);

	if (distance < mTerrainConfiguration.GetLodRange()[mLod])
	{
		this->SplitNode(mLod + 1);
	}
	else
	{
		this->MergeNode();
	}
}

void TerrainNode::SplitNode(unsigned int lod)
{
	if (mIsLeaf)
		mIsLeaf = false;

	if (mChildren.size() == 0)
	{
		for (unsigned int i = 0; i < 2; ++i)
		{
			for (unsigned int j = 0; j < 2; ++j)
			{
				AddChild(new TerrainNode(mVertexArray, mTerrainConfiguration, mLocation + Vec2(i, j) * (mGap / 2.0f), lod, Vec2(i, j)));
			}
		}
	}
}

void TerrainNode::MergeNode()
{
	if (!mIsLeaf)
		mIsLeaf = true;

	for (auto child : mChildren)
		delete child;

	mChildren.clear();
}

void TerrainNode::ComputePosition()
{
	Vec2 location = mLocation + (mGap / 2.f);
	location *= mTerrainConfiguration.GetScaleXZ();
	location -= mTerrainConfiguration.GetScaleXZ() / 2.0f;

	mPosition = Vec3(location.x, 0, location.y);
}

void TerrainNode::Render(Ref<RenderCommand> render_command, Ref<Shader> shader) const
{
	if (mIsLeaf)
	{
		if (render_command->GetAPI() == Engine::API::OpenGL)
		{
			auto ogl_shader = std::dynamic_pointer_cast<Engine::OpenGL::Shader>(shader);
			ogl_shader->UploadUniform("uGlobal"   , mGlobalTransform.GetModel());
			ogl_shader->UploadUniform("uLocal"    , mLocalTransform.GetModel());
			ogl_shader->UploadUniform("uScaleY"   , mTerrainConfiguration.GetScaleY());
			ogl_shader->UploadUniform("uLod"      , (int)mLod);
			ogl_shader->UploadUniform("uIndex"    , mIndex);
			ogl_shader->UploadUniform("uLocation" , mLocation);
			ogl_shader->UploadUniform("uGap"      , mGap);
			ogl_shader->UploadUniform("uTesselationSlope" , mTerrainConfiguration.GetTesselationSlope());
			ogl_shader->UploadUniform("uTesselationShift" , mTerrainConfiguration.GetTesselationShift());
			ogl_shader->UploadUniform("uTesselationFactor", mTerrainConfiguration.GetTesselationFactor());
			mTerrainConfiguration.GetHeightMap()->Bind();
			ogl_shader->UploadUniform("uHeightMap", 0);
			mTerrainConfiguration.GetNormalMap()->Bind(1);
			ogl_shader->UploadUniform("uNormalMap", 1);
			ogl_shader->UploadUniform("uTBNRange", mTerrainConfiguration.GetTBNRange());
			
			auto& materials = mTerrainConfiguration.GetMaterials();
			int texture_unit = 2;
			for (int i = 0; i < materials.size(); ++i)
			{
				materials[i].Load(shader, i, texture_unit);
			}
		}
		Renderable::Render(&mVertexArray, render_command, shader);
	}
	
	for (auto child : mChildren)
	{
		Renderable::Render(child, render_command, shader);
	}
}
