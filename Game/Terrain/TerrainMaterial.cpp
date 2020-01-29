#include "pch.h"
#include "TerrainMaterial.h"

using namespace Engine;

TerrainMaterial::TerrainMaterial(const std::string& diffuse_path, const std::string& normal_path, const std::string& displacement_path, float scale_x, float scale_y)
	: mScale(scale_x, scale_y)
{
	mDiffuse =		Texture2D::Create(diffuse_path);
	mNormal  =		Texture2D::Create(normal_path);
	mDisplacement = Texture2D::Create(displacement_path);
}

void TerrainMaterial::Load(Engine::Ref<Engine::Shader> shader, int index, int& texture_unit) const
{
	switch (Engine::Renderer::GetAPI())
	{
		case Engine::API::OpenGL:
			LoadGLUniforms(std::dynamic_pointer_cast<Engine::OpenGL::Shader>(shader), index, texture_unit);
		default:
			break;
	}
}

void TerrainMaterial::LoadGLUniforms(Engine::Ref<Engine::OpenGL::Shader> shader, int index, int& texture_unit) const
{
	shader->Bind();
	shader->UploadUniform("uMaterials[" + std::to_string(index) + "].diffuse", texture_unit);
	mDiffuse->Bind(texture_unit++);
	shader->UploadUniform("uMaterials[" + std::to_string(index) + "].normal", texture_unit);
	mNormal->Bind(texture_unit++);
	shader->UploadUniform("uMaterials[" + std::to_string(index) + "].displacement", texture_unit);
	mDisplacement->Bind(texture_unit++);
	shader->UploadUniform("uMaterials[" + std::to_string(index) + "].scale", mScale);
}
