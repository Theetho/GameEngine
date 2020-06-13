#include "EnginePch.h"
#include "Panel.h"

namespace Engine
{
	Panel::Panel(const std::string& label, bool* open, int flags)
		: mLabel(label)
		, mOpen(open)
		, mFlags(flags)
		, mOpenedTab(Tab::None)
		, mTabs()
	{}

	Panel::Panel(const Panel& other)
		: mLabel(other.mLabel)
		, mOpen(other.mOpen)
		, mFlags(other.mFlags)
		, mOpenedTab(other.mOpenedTab)
		, mTabs(other.mTabs)
	{}

	Panel::Panel(const Panel && other) noexcept
		: mLabel(other.mLabel)
		, mOpen(other.mOpen)
		, mFlags(other.mFlags)
		, mOpenedTab(other.mOpenedTab)
		, mTabs(other.mTabs)
	{}

	Panel& Panel::operator=(const Panel & other)
	{
		mLabel = other.mLabel;
		mOpen = other.mOpen;
		mFlags = other.mFlags;
		mTabs = other.mTabs;
		mOpenedTab = other.mOpenedTab;

		return *this;
	}

	Panel& Panel::operator=(const Panel&& other) noexcept
	{
		mLabel = other.mLabel;
		mOpen = other.mOpen;
		mFlags = other.mFlags;
		mTabs = other.mTabs;
		mOpenedTab = other.mOpenedTab;

		return *this;
	}

	Panel::~Panel()
	{}

	bool Panel::Begin(bool first) const
	{
		bool result = false;

		if (first)
		{
			result = ImGui::Begin(mLabel.c_str(), mOpen, mFlags);
			ImGui::SetWindowPos(mPosition);
			ImGui::SetWindowSize(mSize);
		}
		else
			result = ImGui::Begin(mLabel.c_str());

	

		return result;
	}

	void Panel::End() const
	{
		ImGui::End();
	}

	void Panel::AddTab(const std::string& label, Tab value)
	{
		mTabs.emplace(label, value);
	}

	void Panel::Render(bool first)
	{
		Begin(first);
		if (mTabs.size())
		{
			if (ImGui::BeginTabBar((mLabel + "-Tabs").c_str()))
			{
				for (auto button : mTabs)
				{
					if (ImGui::BeginTabItem(button.first.c_str()))
					{
						mOpenedTab = button.second;
						ImGui::EndTabItem();
					}
				}
				ImGui::EndTabBar();
			}
		}
		End();
	}
}