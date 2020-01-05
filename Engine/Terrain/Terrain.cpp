#include "EnginePch.h"
#include "Terrain.h"
#include "Component/Collider/TerrainCollider.h"

namespace Engine
{
	const float Terrain::sMaxHeight	= 10.0f;

	Terrain::Terrain(const Vec2& grid_position, const char* height_map_path, const Vec2& dimension)
		: GameObject(Transform(Vec3(grid_position.x * dimension.x, 0.f, grid_position.y * dimension.y)))
		, mDimension(dimension)
		, mResolution(100.0f, 100.0f)
	{
		mHeightMap = Texture2D::Create(height_map_path);

		if (mHeightMap)
			mResolution = Vec2(mHeightMap->GetWidth(), mHeightMap->GetHeight());

		mTexture = Texture2D::Create("lawn.png");

		GenerateTerrain();

		AddComponent<TerrainCollider>(std::make_shared<TerrainCollider>(*this, mTransform.GetPosition()));
	}

	Terrain::~Terrain()
	{
		for (unsigned int i = 0; i < mHeightMap->GetWidth(); ++i)
			delete mHeights[i];
		delete mHeights;
	}

	float Terrain::GetHeight(unsigned int x, unsigned int y) const
	{
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

		mHeights = new float* [mResolution.x];
		for (unsigned int i = 0; i < mResolution.x; ++i)
			mHeights[i] = new float[mResolution.y];

		// Generate the vertices
		for (unsigned int i = 0; i < mResolution.x; ++i)
		{
			for (unsigned int j = 0; j < mResolution.y; ++j)
			{
				// Vertex
				vertices.push_back((float)j / ((float)mResolution.y - 1) * mDimension.y);
				mHeights[(unsigned int)j][(unsigned int)i] = GenerateHeight(j, i);
				vertices.push_back(mHeights[(unsigned int)j][(unsigned int)i]);
				vertices.push_back((float)i / ((float)mResolution.x - 1) * mDimension.x);
				// Texture coordinates
				vertices.push_back((float)j / ((float)mResolution.y - 1));
				vertices.push_back((float)i / ((float)mResolution.x - 1));
				// Normal
				Vec3 normal = GenerateNormal(i, j);
				vertices.push_back(normal.x);
				vertices.push_back(normal.y);
				vertices.push_back(normal.z);
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

		Ref<Material> material = std::make_shared<RawMaterial>(
			Color(0.0f, 0.2f, 0.0), Color(0.0f, 0.25f, 0.0), Color(0.0f, 0.3f, 0.0), 2
		);

		auto mesh = std::make_shared<Mesh>(vertices, indices, material);
		mVertexArray = mesh->GetVao();
	}

	float Terrain::GenerateHeight(unsigned int x, unsigned int y) const
	{
		if (x < 0 || x >= mResolution.x || y < 0 || y >= mResolution.y)
			return 0.f;
		Color pixel = mHeightMap->GetPixel(x, y);
		// Clamp the value in [-sMaxHeight/2, sMaxHeight/2]
		float height = (pixel.r - 0.5f) * sMaxHeight;

		return height;
	}

	Vec3 Terrain::GenerateNormal(unsigned int x, unsigned int y)
	{
		float height_left  = GenerateHeight(x - 1, y);
		float height_right = GenerateHeight(x + 1, y);
		float height_up    = GenerateHeight(x, y + 1);
		float height_down  = GenerateHeight(x, y - 1);

		return glm::normalize(Vec3(height_left - height_right, 2.f, height_down - height_up));
	}

	void Terrain::Render(Ref<RenderCommand> render_command, Ref<Shader> shader) const
	{
		GameObject::Render(render_command, shader);
		mTexture->Bind();
		if (render_command->GetAPI() == API::OpenGL)
		{
			std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniform("u_terrain", 0);
		}
		Renderable::Render(mVertexArray, render_command, shader);
	}
}