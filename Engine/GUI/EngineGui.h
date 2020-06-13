#pragma once

#include "GUI/Panel.h"

namespace Engine
{
	class EngineGUI
	{
	public:
		EngineGUI();
		~EngineGUI();

		void Initialize();
		void Render();
		inline const Panel& GetPanel(const std::string& label) const
		{
			std::string actual_label = "Engine-" + label + "-Panel";

			if (mPanels.count(actual_label))
				return mPanels.at(actual_label);
		}
	private:
		std::unordered_map<std::string, Panel> mPanels;
	};
}

