#include "EnginePch.h"
#include "Sprite.h"
#include "GameObject/GameObject.h"
#include "Core/AssetManager.h"
#include "Vendor/portable-file-dialogs/portable-file-dialogs.h"
#include "imgui_internal.h"

namespace Engine
{
	Sprite::Sprite(GameObject2D& game_object, Ref<Texture2D> texture)
		: Component2D::Component(game_object)
		, mTexture(texture)
		, mColor(Color::White)
	{
	}

	Sprite::Sprite(GameObject2D& game_object, const Color& color)
		: Component2D::Component(game_object)
		, mTexture(nullptr)
		, mColor(color)
	{
	}

	Sprite::~Sprite()
	{
	}
	void Sprite::OnUpdate(const double& delta)
	{
	}
	void Sprite::OnUiRender()
	{
		if (ImGui::CollapsingHeader(ApplyID("Sprite"), ImGuiTreeNodeFlags_DefaultOpen))
		{
			ImGui::Text("Color");
			ImGui::ColorEdit3(ApplyID("##Color"), (float*)&mColor);
			ImGui::Text("Texture");
			
			static std::shared_ptr<pfd::open_file> open_file;
			ImGui::PushItemFlag(ImGuiItemFlags_Disabled, (bool)open_file); 
			if (ImGui::Button(ApplyID(mTexture->GetPath().c_str())))
				open_file = std::make_shared<pfd::open_file>("Choose file", "C:\\");
			if (open_file && open_file->ready())
			{
				auto result = open_file->result();
				if (result.size()) {
					std::string current_path = mTexture->GetPath();
					mTexture = AssetManager::GetTexture2DLibrary().Load(result[0], false);
				}
				open_file = nullptr;
			}
			ImGui::PopItemFlag();
		}
	}
}
