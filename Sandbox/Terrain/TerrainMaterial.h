#pragma once

class TerrainMaterial
{
public:
	TerrainMaterial(const std::string& diffuse_path, const std::string& normal_path, const std::string& displacement_path, float scale_x, float scale_y);

	void Load(Engine::Ref<Engine::Shader> shader, int index, int& texture_unit) const;
private:
	Engine::Ref<Engine::Texture2D> mDiffuse;
	Engine::Ref<Engine::Texture2D> mNormal;
	Engine::Ref<Engine::Texture2D> mDisplacement;
	Engine::Vec2 mScale;

	void LoadGLUniforms(Engine::Ref<Engine::OpenGL::Shader> shader, int index, int& texture_unit) const;
};

