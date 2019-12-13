#pragma once

#include "Mesh.h"
#include "Include/Maths.h"
#include "assimp/scene.h"

namespace Engine
{
	class Model
	{
	public:
		Model(
			const std::string& filePath,
			const std::string& name,
			const bool& useFolderPath
		);

		virtual ~Model()
		{
		}

		static Ref<Model> Create(
			const std::string& filePath,
			const std::string& name,
			const bool& useFolderPath
		);

		static inline void setFolder(
			const std::string& folderPath
		)
		{
			s_folderPath = folderPath;
		}

		inline virtual void setName(
			const std::string& name
		)
		{
			m_name = name;
		}

		inline virtual std::string getName() const
		{
			return m_name;
		}

		inline const std::vector<Mesh>& getMeshes() const
		{
			return m_meshes;
		}

		inline std::vector<Mesh>::iterator begin()
		{
			return m_meshes.begin();
		}
		inline const std::vector<Mesh>::const_iterator begin() const
		{
			return m_meshes.cbegin();
		}
		inline std::vector<Mesh>::iterator end()
		{
			return m_meshes.end();
		}
		inline const std::vector<Mesh>::const_iterator end() const
		{
			return m_meshes.cend();
		}

		struct Dimension
		{
			Vec3 max = Vec3(0.0f);
			Vec3 min = Vec3(0.0f);
		};

		inline const Vec3& getSize() const
		{
			return m_size;
		}

		inline void setMaterial(
			Ref<Material> material
		)
		{
			for (auto& mesh : m_meshes)
			{
				mesh.setMaterial(material);
			}
		}

	private:
		static std::string s_folderPath;
		
		std::string m_path;
		std::string m_name;
		std::vector<Mesh> m_meshes;
		Vec3 m_size;
		Dimension m_dimensions;
		
		void loadModel(
			const std::string& filePath,
			const bool& useFolderPath
		);
		void processNode(
			aiNode* node,
			const aiScene* scene
		);
		Mesh processMesh(
			aiMesh* mesh,
			const aiScene* scene
		);

		std::vector<Ref<Texture2D>> loadMaterial(
			aiMaterial* mat,
			const aiTextureType& type,
			const std::string& name
		);

		void getDimensions(
			const std::string& filePath,
			const bool& useFolderPath
		);

		void updateDimensions(
			const Vec3& vector
		);
	};
}

