#pragma once

#include <memory.h>

template<class T>
class Singleton
{
public:
	static std::shared_ptr<T> Get();
protected:
	static std::shared_ptr<T> sInstance;
	Singleton()  = default;
	~Singleton() = default;
};

template<class T>
std::shared_ptr<T> Singleton<T>::sInstance = std::make_shared<T>();

template<class T>
inline std::shared_ptr<T> Singleton<T>::Get()
{
	return sInstance;
}

