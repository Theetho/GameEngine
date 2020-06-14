#pragma once

#include "Material.h"

namespace Engine
{
	class RawMaterial : public Material
	{
	public:
		RawMaterial(
			const Color& ambient = Color::White,
			const Color& diffuse = Color::White,
			const Color& specular = Color::White,
			float shininess = 128.f
		);

		~RawMaterial();

		static RawMaterial Emerald;	 
		static RawMaterial Jade;	 
		static RawMaterial Obsidian;
		static RawMaterial Pearl;	
		static RawMaterial Ruby;	 
		static RawMaterial Turquoise;
		static RawMaterial Brass;	
		static RawMaterial Bronze;	
		static RawMaterial Chrome;	
		static RawMaterial Copper;	
		static RawMaterial Gold;	 
		static RawMaterial Silver; 
		static RawMaterial BlackPlastic;
		static RawMaterial CyanPlastic;  
		static RawMaterial GreenPlastic;
		static RawMaterial RedPlastic;   
		static RawMaterial WhitePlastic; 
		static RawMaterial YellowPlastic;
		static RawMaterial BlackRubber;	 
		static RawMaterial CyanRubber;	 
		static RawMaterial GreenRubber;	 
		static RawMaterial RedRubber;	 
		static RawMaterial WhiteRubber;	 
		static RawMaterial YellowRubber; 

	private:
		Color mAmbient;
		Color mDiffuse;
		Color mSpecular;
		float mShininess;

		int GetID() const override;

		void LoadGLUniforms(Ref<OpenGL::Shader> shader) override;
		inline void OnRightPanel() override
		{
			if (ImGui::CollapsingHeader("Material", ImGuiTreeNodeFlags_DefaultOpen))
			{
				ImGui::SliderFloat("Shininess", &mShininess, 1.0f, 1024.f);
				ImGui::Separator();
				ImGui::ColorEdit3("Ambient", (float*)&mAmbient);
				ImGui::ColorEdit3("Diffuse", (float*)&mDiffuse);
				ImGui::ColorEdit3("Specular", (float*)&mSpecular);
			}
		}
	};
}