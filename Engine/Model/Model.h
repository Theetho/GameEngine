#pragma once

#include "Renderer/Rendering/Renderable.h"
#include "assimp/scene.h"

namespace Engine
{
	class Mesh;
	class Material;
	
	class Texture2D;

	class Model : public Renderable
	{
	public:
		Model(const std::string& file_path, const std::string& name, bool use_folder_path);
		virtual ~Model();

		static Ref<Model> Create(const std::string& file_path, const std::string& name, bool use_folder_path);
		static void SetFolder(const std::string& folder_path);

		virtual void SetName(const std::string& name);

		virtual const std::string& GetName() const;
		virtual const std::vector<Mesh>& GetMeshes() const;
		virtual const Vec3& GetSize() const;

		void SetMaterial(Ref<Material> material);

		std::vector<Mesh>::iterator begin();
		const std::vector<Mesh>::const_iterator begin() const;
		std::vector<Mesh>::iterator end();
		const std::vector<Mesh>::const_iterator end() const;
	private:
		static std::string sFolderPath;
		std::string mPath;
		std::string mName;
		std::vector<Mesh> mMeshes;
		Vec3 mSize;
		struct Dimension
		{
			Vec3 max = Vec3(0.0f);
			Vec3 min = Vec3(0.0f);
		};
		Dimension mDimensions;
		
		void LoadModel(const std::string& file_path, bool use_folder_path);
		void ProcessNode(aiNode* node, const aiScene* scene);
		Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
		std::vector<Ref<Texture2D>> LoadMaterial(aiMaterial* mat, const aiTextureType& type, const std::string& name);
		void UpdateDimensions(const Vec3& vector);

		void Render(Ref<RenderCommand> render_command, Ref<Shader> shader) const override;
	};
}

