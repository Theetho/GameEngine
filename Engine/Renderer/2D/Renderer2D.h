#pragma once

#define MAX_SPRITE_PER_BATCH 10000
#define MAX_VERTICES_PER_BATCH MAX_SPRITE_PER_BATCH * 4
#define MAX_INDICES_PER_BATCH  MAX_SPRITE_PER_BATCH * 6
// x y z u v r g b a texture
#define ELEMENT_PER_VERTEX 9
#define SIZE_OF_VERTEX ELEMENT_PER_VERTEX * sizeof(float)
#define MAX_TEXTURE_COUNT 32

namespace Engine
{
	template <int dimension>
	class GameObject;
	template <int dimension>
	class Transform;
	class Camera2D;
	class VertexArray;
	class VertexBuffer;
	class IndexBuffer;
	class Texture2D;
	class Shader;
	class Sprite;

	class Renderer2D
	{
	public:
		Renderer2D();
		~Renderer2D();
		void Submit(GameObject<2>* game_object);
		void Submit(Ref<GameObject<2>> game_object);
		void Begin(const Camera2D& camera);
		void End();
	private:
		std::vector<GameObject<2>*> mBatch;
		Ref<Shader> mShader;
		
		struct Buffers {
			Ref<VertexBuffer> vbo;
			Ref<IndexBuffer>  ibo;
			Ref<VertexArray>  vao;
		};
		Buffers mBuffers;
		
		std::vector<float> mVertices;
		std::array<Ref<Texture2D>, MAX_TEXTURE_COUNT> mTextures;
		uint mTextureIndex = 0, mIndiceCount = 0, mVertexIndex = 0;
		void _SetVertices(Ref<Sprite> sprite, Ref<Transform<2>> transform);
		void _PushVertex(const Vec2& position, const Vec2& uv, const Color& color, uint texture_id);
	};
}

