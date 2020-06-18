#include "EnginePch.h"
#include "EngineGUI.h"
#include "Core/Application.h"
#include "Core/Window.h"
#include "GUI/Panel.h"

namespace Engine
{
	EngineGUI::EngineGUI()
		: mPanels()
	{}

	EngineGUI::~EngineGUI()
	{}

	void EngineGUI::Initialize()
	{
		auto panel_flags =
			ImGuiWindowFlags_NoCollapse |
			ImGuiWindowFlags_NoMove |
			ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_NoTitleBar |
			ImGuiWindowFlags_NoBringToFrontOnFocus;
		Window& window = Application::Get()->GetWindow();

		float main_menu_height = 0.f;
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Edit"))
			{
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Example"))
			{
				ImGui::EndMenu();
			}
			main_menu_height = ImGui::GetWindowHeight();
			ImGui::EndMainMenuBar();
		}

		float panel_height = (float)window.GetHeight() * 0.90f - main_menu_height;
		
		// Left panel
		std::string label = "Engine-Left-Panel";
		mPanels.emplace(label, Panel(label, nullptr, panel_flags));
		mPanels.at(label).SetPosition(ImVec2(0.f, main_menu_height));
		mPanels.at(label).SetSize(ImVec2(window.GetWidth() * 0.15f, panel_height));
		mPanels.at(label).AddTab("Scene", Tab::Scene);
		mPanels.at(label).AddTab("Hierarchy", Tab::Hierachy);

		// Playing panel
		label = "Engine-Playing-Panel";
		mPanels.emplace(label, Panel(label, nullptr, panel_flags));
		mPanels.at(label).SetPosition(ImVec2(window.GetWidth() * 0.15f, main_menu_height));
		mPanels.at(label).SetSize(ImVec2(window.GetWidth() * 0.70f, panel_height));

		// Right panel
		label = "Engine-Right-Panel";
		mPanels.emplace(label, Panel(label, nullptr, panel_flags));
		mPanels.at(label).SetPosition(ImVec2(window.GetWidth() * 0.85f, main_menu_height));
		mPanels.at(label).SetSize(ImVec2(window.GetWidth() * 0.15f, panel_height));
		mPanels.at(label).AddTab("Inspector", Tab::Inspector);

		// Bottom panel
		label = "Engine-Bottom-Panel";
		mPanels.emplace(label, Panel(label, nullptr, panel_flags));
		mPanels.at(label).SetPosition(ImVec2(0.f, main_menu_height + panel_height));
		mPanels.at(label).SetSize(ImVec2((float)window.GetWidth(), window.GetHeight() - (main_menu_height + panel_height)));
		mPanels.at(label).AddTab("Project", Tab::Project);
	}

	void EngineGUI::Render()
	{
		ImGuiStyle& style = ImGui::GetStyle();
		style.WindowRounding = 0;

		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Edit"))
			{
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Example"))
			{
				ImGui::EndMenu();
			}
			ImGui::EndMainMenuBar();
		}

		int i = 0;
		for (auto& panel : mPanels)
		{
			panel.second.Render(true);
		}
		
		style.WindowRounding = 7;
	}
}