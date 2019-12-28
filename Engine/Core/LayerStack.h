#pragma once

#include "Layer.h"

namespace Engine
{
	class LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void Push(Layer* layer);
		void Pop();

		bool IsEmpty() const;

		std::vector<Layer*>::iterator begin() 
		{ 
			return mStack.begin();
		}
		std::vector<Layer*>::iterator end()
		{
			return mStack.end(); 
		}

	private:
		std::vector<Layer*>	mStack;
		unsigned int		mInsert = 0;
	};
}