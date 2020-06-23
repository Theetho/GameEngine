#pragma once

#include "Model/Mesh.h"
#include "Renderer/Shader.h"
#include "Renderer/Texture/Texture2D.h"

namespace Engine
{
	class Scene;

	template<typename T>
	class Library
	{
	public:
		inline virtual ~Library()
		{}

		inline void Add(const Ref<T>& t)
		{
			if (!Exists(t->GetName()))
				mReferences[t->GetName()] = t;
		}
		inline Ref<T> Load(const std::string& file_path, std::string name = "", bool use_folder_path = true)
		{
			if (name == "")
				name = ExtractName(file_path);

			if (!Exists(name))
			{
				mReferences[name] = T::Create(use_folder_path ? sFolderPath + file_path : file_path);
			}

			return mReferences[name];
		}
		inline Ref<T> Get(const std::string& name)
		{
			if (Exists(name))
			{
				return mReferences[name];
			}
		}
		inline bool   Exists(const std::string& name)
		{
			return mReferences.find(name) != mReferences.end();
		}

		static void SetFolder(const std::string& path);
	private:
		friend class Scene;
		static std::string sFolderPath;
		inline std::unordered_map<std::string, Ref<T>>& GetList()
		{
			return mReferences;
		}

		std::unordered_map<std::string, Ref<T>> mReferences;

		inline std::string ExtractName(const std::string& file_path)
		{
			// Getting the name from the file path
			size_t lastSlash = file_path.find_last_of("/\\");
			lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
			size_t lastDot = file_path.rfind('.');
			int count = lastDot == std::string::npos ? file_path.size() - lastSlash : lastDot - lastSlash;

			return file_path.substr(lastSlash, count);
		}
	};

	template<class T>
	std::string Library<T>::sFolderPath = "";

	template<class T>
	void Library<T>::SetFolder(const std::string& path)
	{
		sFolderPath = path;
	}

	typedef Library<Shader> ShaderLibrary;
	typedef Library<Texture2D> Texture2DLibrary;
	typedef Library<Mesh> MeshLibrary;
}

