#pragma once

#include <memory.h>

namespace Engine
{
	template<class T>
	class Singleton
	{
	public:
		static T* Get();
	protected:
		static T* sInstance;
		Singleton() = default;
		~Singleton() = default;
	};

	template<class T>
	T* Singleton<T>::sInstance = new T();

	template<class T>
	inline T* Singleton<T>::Get()
	{
		return sInstance;
	}

}
