#pragma once

#include <iostream>
#include <math.h>
#include "Export.h"

template <class T>
class Vec2
{
public:
	T x;
	T y;

	// Constructors
	Vec2()
		: Vec2<T>(0)
	{
	}
	template <class T1>
	Vec2(const T1& x, const T1& y)
		: x(static_cast<T>(x))
		, y(static_cast<T>(y))
	{
	}
	template <class T1>
	Vec2(const T1& t)
		: Vec2<T>(t, t)
	{
	}
	template <class T1>
	Vec2(const Vec2<T1>& v)
		: x(static_cast<T>(v.x))
		, y(static_cast<T>(v.y))
	{
	}
	~Vec2()
	{
	}
	// Operators
	inline bool operator==(const Vec2<T>& v) const
	{
		return (this->x == v.x && this->y == v.y);
	}
	inline bool operator!=(const Vec2<T>& v) const
	{
		return !this->operator==(v);
	}
	template<class T1>
	Vec2<T> operator=(const Vec2<T1>& v)
	{
		return Vec2<T>(v);
	}
	template<class T1>
	inline auto operator+(const T1& t) const
	{
		return Vec2<decltype(this->x + t)>(this->x + t, this->y + t);
	}
	template<class T1>
	inline auto operator-(const T1& t) const
	{
		return Vec2<decltype(this->x - t)>(this->x - t, this->y - t);
	}
	template<class T1>
	inline auto operator*(const T1& t) const
	{
		return Vec2<decltype(this->x * t)>(this->x * t, this->y * t);
	}
	template<class T1>
	inline auto operator/(const T1& t) const
	{
		return Vec2<decltype(this->x / t)>(this->x / t, this->y / t);
	}
	template<class T1>
	inline void operator+=(const T1& t)
	{
		this->x += static_cast<T>(t);
		this->y += static_cast<T>(t);
	}
	template<class T1>
	inline void operator-=(const T1& t)
	{
		this->x -= static_cast<T>(t);
		this->y -= static_cast<T>(t);
	}
	template<class T1>
	inline void operator*=(const T1& t)
	{
		this->x *= static_cast<T>(t);
		this->y *= static_cast<T>(t);
	}
	template<class T1>
	inline void operator/=(const T1& t)
	{
		this->x /= static_cast<T>(t);
		this->y /= static_cast<T>(t);
	}
	template<class T1>
	inline void operator+=(const Vec2<T1>& v)
	{
		this->x += static_cast<T>(v.x);
		this->y += static_cast<T>(v.y);
	}
	template<class T1>
	inline void operator-=(const Vec2<T1>& v)
	{
		this->x -= static_cast<T>(v.x);
		this->y -= static_cast<T>(v.y);
	}
	template<class T1>
	inline void operator*=(const Vec2<T1>& v)
	{
		this->x *= static_cast<T>(v.x);
		this->y *= static_cast<T>(v.y);
	}
	template<class T1>
	inline void operator/=(const Vec2<T1>& v)
	{
		this->x /= static_cast<T>(v.x);
		this->y /= static_cast<T>(v.y);
	}
	// Functions
	inline double length() const
	{
		return sqrt(pow(this->x, 2) + pow(this->y, 2));
	}
	inline Vec2<T> normalize()
	{
		this->operator/=(this->length());
		return *this;
	}
	template<class T1>
	inline auto dot(const Vec2<T1>& v) const
	{
		return this->x * v.x + this->y * v.y;
	}
	template<class T1>
	inline auto cross(const Vec2<T1>& v) const
	{
		return Vec2<decltype(this->y * v.z)>(
				this->y * v.x - this->x * v.y,
				this->x * v.y - this->y * v.x);
	}
};
// Operators
template<class T1, class T2>
inline auto operator+(const Vec2<T1>& v1, const Vec2<T2>& v2)
{
	return Vec2<decltype(v1.x + v2.x)>(v1.x + v2.x, v1.y + v2.y);
}
template<class T1, class T2>
inline auto operator-(const Vec2<T1>& v1, const Vec2<T2>& v2)
{
	return Vec2<decltype(v1.x - v2.x)>(v1.x - v2.x, v1.y - v2.y);
}
template<class T1, class T2>
inline auto operator*(const Vec2<T1>& v1, const Vec2<T2>& v2)
{
	return Vec2<decltype(v1.x * v2.x)>(v1.x * v2.x, v1.y * v2.y);
}
template<class T1, class T2>
inline auto operator/(const Vec2<T1>& v1, const Vec2<T2>& v2)
{
	return Vec2<decltype(v1.x / v2.x)>(v1.x / v2.x, v1.y / v2.y);
}
template<class T>
std::ostream& operator<<(std::ostream& os, const Vec2<T>& v)
{
	os << "[" << v.x << " " << v.y << "]" << std::endl;

	return os;
}
// Functions
template<class T1, class T2>
inline auto lerp(const Vec2<T1>& v1, const Vec2<T2>& v2, const double& percentage)
{
	return (1 - percentage) * v1 + percentage * v2;
}

// Usefull type def
typedef Vec2<float>			Vec2f;
typedef Vec2<double>		Vec2d;
typedef Vec2<unsigned int>	Vec2u;
typedef Vec2<int>			Vec2i;