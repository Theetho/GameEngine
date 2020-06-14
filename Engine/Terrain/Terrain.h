#pragma once

#include "GameObject/GameObject.h"
#include "Renderer/Rendering/Renderable.h"

namespace Engine
{
	class VertexArray;
	class Texture2D;

	class Terrain : public GameObject3D, public Renderable
	{
	public:
		///////////////////////////
		/// Constructor of the class.
		/// @param position: position of the terrain in the "terrain's grid".
		/// @param height_map_path: path to the height map for the terrain's generation.
		/// @param dimension: width and depth of the terrain.
		///////////////////////////
		Terrain(const Vec2& grid_position, const char* height_map_path = nullptr, const Vec2& dimension = Vec2(1000));
		~Terrain();
		///////////////////////////
		/// Return the height of the vertex with coordinates (x, y).
		/// @params x, y: coordinates of the vertex on the terrain,
		/// which also correspond to a pixel on the heightmap.
		///////////////////////////
		float GetHeight(unsigned int x, unsigned int y) const;

		Ref<Texture2D> GetHeightMap() const;
		Vec2		   GetDimensions() const;
		Vec2		   GetResolution() const;
	private:
		///////////////////////////
		/// Generate the vertices, texture coordinates, normals and
		/// indices of the terrain.
		///////////////////////////
		void  GenerateTerrain();
		float GenerateHeight(unsigned int x, unsigned int y) const;
		///////////////////////////
		/// Generate a normal vector for a given vertex.
		/// @params x, y: coordinates of the vertex on the terrain.
		///////////////////////////
		Vec3  GenerateNormal(unsigned int x, unsigned int y) const;
		Color GenerateColor(unsigned int x, unsigned int y) const;
		float GetMultiplier(float& height) const;
		void  Render(Ref<RenderCommand> render_command, Ref<Shader> shader) const override;
	private:
		struct Biome
		{
			float height;
			float multiplier;
			Color color;
			Biome(float height, float multiplier, Color color);
		};
		static const std::map<const char*, Biome>sBiome;
		Vec2			   mDimension;
		Vec2			   mResolution; // Number of subdivision
		float**			   mHeights;
		Ref<VertexArray>   mVertexArray;
		Ref<Texture2D>	   mHeightMap;

		virtual void OnLeftPanel(SceneObject* caller = nullptr, std::string label = "", int number = -1) override
		{
			SceneObject::OnLeftPanel(this, "Terrain", number);
		}
	};
}

