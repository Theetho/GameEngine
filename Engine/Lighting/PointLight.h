#pragma once

#include "Light.h"

namespace Engine
{
	class PointLight : public Light
	{
	public:
		/**
		  * Distance Constant Linear	Quadratic
		  *  7		  1.0	   0.7		 1.8
		  *  13		  1.0	   0.35		 0.44
		  *  20		  1.0	   0.22		 0.20
		  *  32		  1.0	   0.14		 0.07
		  *  50		  1.0	   0.09		 0.032
		  *  65		  1.0	   0.07		 0.017
		  *  100	  1.0	   0.045	 0.0075
		  *  160	  1.0	   0.027	 0.0028
		  *  200	  1.0	   0.022	 0.0019
		  *  325	  1.0	   0.014	 0.0007
		  *  600	  1.0	   0.007	 0.0002
		  *  3250	  1.0	   0.0014	 0.000007	  
		  */
		struct Attenuation
		{
			float quadratic;
			float linear;
			float constant;

			Attenuation(
				float quadratic = 0.000007f,
				float linear    = 0.0014f,
				float constant  = 1.0f
			)
				: quadratic(quadratic)
				, linear(linear)
				, constant(constant)
			{}
		};

		PointLight(const Vec3& position, const Attenuation& attenuation = Attenuation(), const Color& color = Color::White);
		virtual ~PointLight();

		virtual int				   GetID() const override;
		virtual Attenuation&	   GetAttenuation();
		virtual const Vec3&		   GetPosition() const;
		virtual const Attenuation& GetAttenuation() const;

		void SetPosition(const Vec3& position);
	private:
		Vec3		mPosition;
		Attenuation mAttenuation;
	protected:
		void LoadGLUniforms(Ref<OpenGL::Shader> shader, unsigned int index) override;
		virtual void OnLeftPanel(SceneObject* caller = nullptr, std::string label = "", int number = -1) override;
		virtual void OnRightPanel() override;
	};
}
