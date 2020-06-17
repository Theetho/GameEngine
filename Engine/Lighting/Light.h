#pragma once

#include "Core/SceneObject.h"

namespace Engine
{
	class Color;
	class Shader;
	namespace OpenGL
	{
		class Shader;
	}

	class Light : public SceneObject
	{
	public:
		explicit Light(const Color& color = Color::White);
		virtual ~Light();

		virtual void Load(Ref<Shader> shader, unsigned int index);
		virtual void Unload(Ref<Shader> shader, unsigned int index);

		virtual int GetID() const = 0;
		const Color& GetColor() const;
		inline float GetMinDiffuseFactor() const
		{
			return mMinDiffuseFactor;
		}

		void SetColor(const Color& color);
		inline void SetMinDiffuseFactor(float factor)
		{
			mMinDiffuseFactor = factor;
		}
		inline bool ShouldChangeType() const
		{
			return (mRequestedType != (int)LightID::None && GetID() != mRequestedType);
		}
		inline int GetRequestedType() const
		{
			return mRequestedType;
		}
		inline bool& IsActive()
		{
			return mActive;
		}
		enum class LightID
		{
			None,
			Directional,
			Point,
			Spot
		};

	private:
		Color mColor;
		bool mActive;
		float mMinDiffuseFactor = 0.1f;
	protected:
		virtual void LoadGLUniforms(Ref<OpenGL::Shader> shader, unsigned int index);
		virtual void UnloadGLUniforms(Ref<OpenGL::Shader> shader, unsigned int index);
		void OnRightPanel() override;
	private:
		int mRequestedType = (int)LightID::None;
	};
}
