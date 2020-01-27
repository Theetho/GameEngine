#include "..\..\Game\Terrain\Terrain.h"
#include "EnginePch.h"
#include "Terrain.h"
#include "Component/Collider/TerrainCollider.h"
#include "GameObject/Transform.h"
#include "Renderer/Texture/Texture2D.h"
#include "Renderer/Buffer.h"
#include "Renderer/Rendering/RenderCommand.h"
#include "Renderer/Rendering/RendererAPI.h"
#include "API/OpenGL/Shader.h"

namespace Engine
{
	const const std::map<const char*, Terrain::Biome> Terrain::sBiome{
		{ "Deep_Water", Biome(0.30f, 4.00f, Color(10 , 75 , 120))},
		{ "Water",		Biome(0.45f, 5.00f, Color(15 , 100, 190))},
		//{ "Deep_Water", Biome(0.30f, 4.00f, Color(170, 125, 50 ))},
		//{ "Water",		Biome(0.45f, 5.00f, Color(200 ,160, 80 ))},
		{ "Sand",		Biome(0.50f, 10.0f, Color(250, 245, 170))},
		{ "Grass_1",	Biome(0.65f, 12.0f, Color(100, 200, 0  ))},
		{ "Grass_2",	Biome(1.00f, 14.0f, Color(75 , 150, 0  ))},
	};

	Terrain::Terrain(const Vec2& grid_position, const char* height_map_path, const Vec2& dimension)
		: GameObject(Transform(Vec3(grid_position.x * dimension.x, 0.f, grid_position.y * dimension.y), Vec3(0.0f), Vec3(1.0f)))
		, mDimension(dimension)
		, mResolution(100.0f, 100.0f)
	{
		mHeightMap = Texture2D::Create(height_map_path);
		//mHeightMap = Texture2D::Create("Heightmaps/3279_8_2_0.5_0.758.png");

		if (mHeightMap)
			mResolution = Vec2(mHeightMap->GetWidth(), mHeightMap->GetHeight());

		//mTexture = Texture2D::Create("lawn.png");

		GenerateTerrain();

		AddComponent<TerrainCollider>(CreateRef<TerrainCollider>(*this, mTransform.GetPosition()));
	}

	Terrain::~Terrain()
	{
		for (unsigned int i = 0; i < mHeightMap->GetWidth(); ++i)
			delete mHeights[i];
		delete mHeights;
	}

	float Terrain::GetHeight(unsigned int x, unsigned int y) const
	{
		if (x < 0 || y < 0 || x > mResolution.x - 1 || y > mResolution.y - 1)
			return -1000.0f;
		return mHeights[x][y];
	}

	Ref<Texture2D> Terrain::GetHeightMap() const
	{
		return mHeightMap;
	}

	Vec2 Terrain::GetDimensions() const
	{
		return mDimension;
	}

	Vec2 Terrain::GetResolution() const
	{
		return mResolution;
	}

	void Terrain::GenerateTerrain()
	{
		std::vector<float> vertices;
		std::vector<unsigned int> indices;

		mHeights = new float* [mResolution.y];
		for (unsigned int i = 0; i < mResolution.y; ++i)
			mHeights[i] = new float[mResolution.x];


		// Generate the vertices
		for (unsigned int i = 0; i < mResolution.y; ++i)
		{
			for (unsigned int j = 0; j < mResolution.x; ++j)
			{
				// Vertex
				vertices.push_back((float)j / ((float)mResolution.x - 1) * mDimension.x);
				mHeights[(unsigned int)j][(unsigned int)i] = GenerateHeight(j, i);
				vertices.push_back(mHeights[(unsigned int)j][(unsigned int)i]);
				vertices.push_back((float)i / ((float)mResolution.y - 1) * mDimension.y);
				// Texture coordinates
				vertices.push_back((float)j / ((float)mResolution.x - 1));
				vertices.push_back((float)i / ((float)mResolution.y - 1));
				// Normal
				Vec3 normal = GenerateNormal(j, i);
				vertices.push_back(normal.x);
				vertices.push_back(normal.y);
				vertices.push_back(normal.z);
				Color color = GenerateColor(j, i);
				vertices.push_back(color.r);
				vertices.push_back(color.g);
				vertices.push_back(color.b);
			}
		}
		// Generate the indices
		for (int i = 0; i < mResolution.x - 1; ++i)
		{
			for (int j = 0; j < mResolution.y - 1; ++j)
			{
				int top_left = (i * mResolution.x) + j;
				int top_right = top_left + 1;
				int bottom_left = ((i + 1) * mResolution.x) + j;
				int bottom_right = bottom_left + 1;
				indices.push_back(top_left);
				indices.push_back(bottom_left);
				indices.push_back(top_right);
				indices.push_back(top_right);
				indices.push_back(bottom_left);
				indices.push_back(bottom_right);
			}
		}

		mVertexArray = VertexArray::Create();

		auto vertex_buffer = VertexBuffer::Create(vertices.data(), vertices.size());

		vertex_buffer->SetLayout({
			BufferElement(ShaderDataType::Float3, "inPosition"),
			BufferElement(ShaderDataType::Float2, "inTextureCoords"),
			BufferElement(ShaderDataType::Float3, "inNormal"),
			BufferElement(ShaderDataType::Float3, "inColor")
		});

		mVertexArray->AddVertexBuffer(vertex_buffer);

		auto index_buffer = IndexBuffer::Create(indices.data(), indices.size());

		mVertexArray->AddIndexBuffer(index_buffer);
	}

	float Terrain::GenerateHeight(unsigned int x, unsigned int y) const
	{
		if (x < 0 || x >= mResolution.x || y < 0 || y >= mResolution.y)
			return 0.f;
		float pixel = mHeightMap->GetPixel(x, y).r;
		float multiplier = GetMultiplier(pixel);

		// Clamp the value in [-Multiplier /2, Multiplier /2]
		float height = pixel /*(pixel - 0.5f)*/ * multiplier;

		return height;
	}

	Vec3 Terrain::GenerateNormal(unsigned int x, unsigned int y) const
	{
		float height_left  = GenerateHeight(x - 1, y);
		float height_right = GenerateHeight(x + 1, y);
		float height_up    = GenerateHeight(x, y + 1);
		float height_down  = GenerateHeight(x, y - 1);

		return glm::normalize(Vec3(height_left - height_right, 2.f, height_down - height_up));
	}

	Color Terrain::GenerateColor(unsigned int x, unsigned int y) const
	{
		if (x < 0 || x >= mResolution.x || y < 0 || y >= mResolution.y)
			return Color(10, 75, 120);
		float height = mHeightMap->GetPixel(x, y).r;

		auto it = sBiome.begin();
		while (it != sBiome.end())
		{
			Biome biome = it->second;
			if (height <= biome.height)
			{
				return biome.color;
			}
			++it;
		}
	}

	float Terrain::GetMultiplier(float& height) const
	{
		float multiplier = 1.0f;

		auto it = sBiome.begin();
		Biome biome = it->second;
		float previous_height     = biome.height;
		float previous_multiplier = biome.multiplier;
		while (it != sBiome.end())
		{
			Biome biome = it->second;
			if (height <= biome.height)
			{
				if (biome.multiplier != previous_multiplier)
				{
					multiplier = MathsFunctions::Lerp(previous_multiplier, biome.multiplier, (height - previous_height) / (biome.height - previous_height));
				}
				else
				{
					multiplier = biome.multiplier;
				}
				break;
			}
			previous_height = biome.height;
			previous_multiplier = biome.multiplier; 
			++it;
		}

		return multiplier;
	}

	void Terrain::Render(Ref<RenderCommand> render_command, Ref<Shader> shader) const
	{
		GameObject::Render(render_command, shader);
		Renderable::Render(mVertexArray, render_command, shader);
	}

	Terrain::Biome::Biome(float height, float multiplier, Color color)
		: height(height), multiplier(multiplier), color(color)
	{
	}
}