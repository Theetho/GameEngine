#pragma once

namespace Engine
{
	enum class Tab
	{
		None,
		Scene,
		Inspector,
		Project,
		Hierachy
	};

	class Panel
	{
	public:
		Panel(const std::string& label = "\0", bool* open = nullptr, int flags = 0);
		Panel(const Panel& other);
		Panel(const Panel&& other) noexcept;
		Panel& operator=(const Panel& other);
		Panel& operator=(const Panel&& other) noexcept;
		~Panel();
		bool Begin(bool first = false) const;
		void End() const;
		void AddTab(const std::string& label, Tab value);
		void Render(bool first = false);

		inline const ImVec2& GetPosition() const
		{
			return mPosition;
		}
		inline const ImVec2& GetSize() const
		{
			return mSize;
		}
		inline void SetSize(const ImVec2& size)
		{
			mSize = size;
		}
		inline void SetPosition(const ImVec2& position)
		{
			mPosition = position;
		}
		inline Tab GetOpenedTab() const
		{
			return mOpenedTab;
		}
	private:
		std::string mLabel;
		bool* mOpen;
		int mFlags;
		Tab mOpenedTab;
		ImVec2 mSize;
		ImVec2 mPosition;
		std::unordered_map<std::string, Tab> mTabs;
	};
}

