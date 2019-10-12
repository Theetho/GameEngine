#pragma once

#include <iostream>
#include <math.h>
#include "Export.h"

template <class T> 
class Vec4
{
public:
	T x;
	T y;
	T z;
	T w;

	// Constructors
	Vec4()
		: Vec4<T>(0)
	{
	}
	template <class T1>
	Vec4(const T1& x, const T1& y, const T1& z, const T1& w)
		: x(static_cast<T>(x))
		, y(static_cast<T>(y))
		, z(static_cast<T>(z))
		, w(static_cast<T>(w))
	{
	}
	template <class T1>
	Vec4(const T1& t)
		: Vec4<T>(t, t, t, t)
	{
	}
	template <class T1>
	Vec4(const Vec4<T1>& v)
		: x(static_cast<T>(v.x))
		, y(static_cast<T>(v.y))
		, z(static_cast<T>(v.z))
		, w(static_cast<T>(v.w))
	{
	}
	~Vec4()
	{
	}
	// Operators
	inline bool operator==(const Vec4<T>& v) const
	{
		return (this->x == v.x && this->y == v.y && this->z == v.z && this->w == w);
	}
	inline bool operator!=(const Vec4<T>& v) const
	{
		return !this->operator==(v);
	}
	template<class T1>
	inline Vec4<T> operator=(const Vec4<T1>& v)
	{
		return Vec4<T>(v);
	}
	template<class T1>
	inline auto operator+(const T1& t) const
	{
		return Vec4<decltype(this->x + t)>(this->x + t, this->y + t, this->z + t, this->w + t);
	}
	template<class T1>
	inline auto operator-(const T1& t) const
	{
		return Vec4<decltype(this->x - t)>(this->x - t, this->y - t, this->z - t, this->w - t);
	}
	template<class T1>
	inline auto operator*(const T1& t) const
	{
		return Vec4<decltype(this->x * t)>(this->x * t, this->y * t, this->z * t, this->w - t);
	}
	template<class T1>
	inline auto operator/(const T1& t) const
	{
		return Vec4<decltype(this->x / t)>(this->x / t, this->y / t, this->z / t, this->w / t);
	}
	template<class T1>
	inline void operator+=(const T1& t)
	{
		this->x += static_cast<T>(t);
		this->y += static_cast<T>(t);
		this->z += static_cast<T>(t);
		this->w += static_cast<T>(t);
	}
	template<class T1>
	inline void operator-=(const T1& t)
	{
		this->x -= static_cast<T>(t);
		this->y -= static_cast<T>(t);
		this->z -= static_cast<T>(t);
		this->w -= static_cast<T>(t);
	}
	template<class T1>
	inline void operator*=(const T1& t)
	{
		this->x *= static_cast<T>(t);
		this->y *= static_cast<T>(t);
		this->z *= static_cast<T>(t);
		this->w *= static_cast<T>(t);
	}
	template<class T1>
	inline void operator/=(const T1& t)
	{
		this->x /= static_cast<T>(t);
		this->y /= static_cast<T>(t);
		this->z /= static_cast<T>(t);
		this->w /= static_cast<T>(t);
	}
	template<class T1>
	inline void operator+=(const Vec4<T1>& v)
	{
		this->x += static_cast<T>(v.x);
		this->y += static_cast<T>(v.y);
		this->z += static_cast<T>(v.z);
		this->w += static_cast<T>(v.w);
	}
	template<class T1>
	inline void operator-=(const Vec4<T1>& v)
	{
		this->x -= static_cast<T>(v.x);
		this->y -= static_cast<T>(v.y);
		this->z -= static_cast<T>(v.z);
		this->w -= static_cast<T>(v.w);
	}
	template<class T1>
	inline void operator*=(const Vec4<T1>& v)
	{
		this->x *= static_cast<T>(v.x);
		this->y *= static_cast<T>(v.y);
		this->z *= static_cast<T>(v.z);
		this->w *= static_cast<T>(v.w);
	}
	template<class T1>
	inline void operator/=(const Vec4<T1>& v)
	{
		this->x /= static_cast<T>(v.x);
		this->y /= static_cast<T>(v.y);
		this->z /= static_cast<T>(v.z);
		this->w /= static_cast<T>(v.w);
	}
	// Functions
	inline double length() const
	{
		return sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2) + pow(this->w, 2));
	}
	inline Vec4<T> normalize()
	{
		this->operator/=(this->length());
		return *this;
	}
	template<class T1>
	inline auto dot(const Vec4<T1>& v) const
	{
		return this->x * v.x + this->y * v.y + this->z * v.z + this->w * v.w;
	}
	template<class T1>
	inline auto cross(const Vec4<T1>& v) const
	{
		return Vec4<decltype(this->y * v.z)>(
				this->y * v.z - this->z * v.y,
				this->z * v.w - this->w * v.z,
				this->w * v.x - this->x * v.w,
				this->x * v.y - this->y * v.x);
	}
};
// Operators
template<class T1, class T2>
inline auto operator+(const Vec4<T1>& v1, const Vec4<T2>& v2)
{
	return Vec4<decltype(v1.x + v2.x)>(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w);
}
template<class T1, class T2>
inline auto operator-(const Vec4<T1>& v1, const Vec4<T2>& v2)
{
	return Vec4<decltype(v1.x - v2.x)>(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w);
}
template<class T1, class T2>
inline auto operator*(const Vec4<T1>& v1, const Vec4<T2>& v2)
{
	return Vec4<decltype(v1.x * v2.x)>(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v1.w * v2.w);
}
template<class T1, class T2>
inline auto operator/(const Vec4<T1>& v1, const Vec4<T2>& v2)
{
	return Vec4<decltype(v1.x / v2.x)>(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z, v1.w / v2.w);
}
template<class T>
std::ostream& operator<<(std::ostream& os, const Vec4<T>& v)
{
	os << "[" << v.x << " " << v.y << " " << v.z << " " << v.w << "]" << std::endl;
	
	return os;
}
// Functions
template<class T1, class T2>
inline auto lerp(const Vec4<T1>& v1, const Vec4<T2>& v2, const double& percentage)
{
	return (1 - percentage) * v1 + percentage * v2;
}

// Usefull type def
typedef Vec4<float>			Vec4f;
typedef Vec4<double>		Vec4d;
typedef Vec4<unsigned int>	Vec4u;
typedef Vec4<int>			Vec4i;