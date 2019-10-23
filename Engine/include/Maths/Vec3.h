#pragma once

#include <iostream>
#include <math.h>
#include "Export.h"

template <class T>
class Vec3
{
public:
	T x;
	T y;
	T z;

	// Constructors
	Vec3()
		: Vec3<T>(0)
	{
	}
	template <class T1>
	Vec3(const T1& x, const T1& y, const T1& z)
		: x(static_cast<T>(x))
		, y(static_cast<T>(y))
		, z(static_cast<T>(z))
	{
	}
	template <class T1>
	Vec3(const T1& t)
		: Vec3<T>(t, t, t)
	{
	}
	template <class T1>
	Vec3(const Vec3<T1>& v)
		: x(static_cast<T>(v.x))
		, y(static_cast<T>(v.y))
		, z(static_cast<T>(v.z))
	{
	}
	~Vec3()
	{
	}
	// Operators
	inline bool operator==(const Vec3<T>& v) const
	{
		return (this->x == v.x && this->y == v.y && this->z == v.z);
	}
	inline bool operator!=(const Vec3<T>& v) const
	{
		return !this->operator==(v);
	}
	template<class T1>
	Vec3<T> operator=(const Vec3<T1>& v)
	{
		return Vec3<T>(v);
	}
	template<class T1>
	inline auto operator+(const T1& t) const
	{
		return Vec3<decltype(this->x + t)>(this->x + t, this->y + t, this->z + t);
	}
	template<class T1>
	inline auto operator-(const T1& t) const
	{
		return Vec3<decltype(this->x - t)>(this->x - t, this->y - t, this->z - t);
	}
	template<class T1>
	inline auto operator*(const T1& t) const
	{
		return Vec3<decltype(this->x * t)>(this->x * t, this->y * t, this->z * t);
	}
	template<class T1>
	inline auto operator/(const T1& t) const
	{
		return Vec3<decltype(this->x / t)>(this->x / t, this->y / t, this->z / t);
	}
	template<class T1>
	inline void operator+=(const T1& t)
	{
		this->x += static_cast<T>(t);
		this->y += static_cast<T>(t);
		this->z += static_cast<T>(t);
	}
	template<class T1>
	inline void operator-=(const T1& t)
	{
		this->x -= static_cast<T>(t);
		this->y -= static_cast<T>(t);
		this->z -= static_cast<T>(t);
	}
	template<class T1>
	inline void operator*=(const T1& t)
	{
		this->x *= static_cast<T>(t);
		this->y *= static_cast<T>(t);
		this->z *= static_cast<T>(t);
	}
	template<class T1>
	inline void operator/=(const T1& t)
	{
		this->x /= static_cast<T>(t);
		this->y /= static_cast<T>(t);
		this->z /= static_cast<T>(t);
	}
	template<class T1>
	inline void operator+=(const Vec3<T1>& v)
	{
		this->x += static_cast<T>(v.x);
		this->y += static_cast<T>(v.y);
		this->z += static_cast<T>(v.z);
	}
	template<class T1>
	inline void operator-=(const Vec3<T1>& v)
	{
		this->x -= static_cast<T>(v.x);
		this->y -= static_cast<T>(v.y);
		this->z -= static_cast<T>(v.z);
	}
	template<class T1>
	inline void operator*=(const Vec3<T1>& v)
	{
		this->x *= static_cast<T>(v.x);
		this->y *= static_cast<T>(v.y);
		this->z *= static_cast<T>(v.z);
	}
	template<class T1>
	inline void operator/=(const Vec3<T1>& v)
	{
		this->x /= static_cast<T>(v.x);
		this->y /= static_cast<T>(v.y);
		this->z /= static_cast<T>(v.z);
	}
	// Functions
	inline double length() const
	{
		return sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2));
	}
	inline Vec3<T> normalize()
	{
		this->operator/=(this->length());
		return *this;
	}
	template<class T1>
	inline auto dot(const Vec3<T1>& v) const
	{
		return this->x * v.x + this->y * v.y + this->z * v.z;
	}
	template<class T1>
	inline auto cross(const Vec3<T1>& v) const
	{
		return Vec3<decltype(this->y * v.z)>(
				this->y * v.z - this->z * v.y,
				this->z * v.x - this->x * v.z,
				this->x * v.y - this->y * v.x);
	}
};
// Operators
template<class T1, class T2>
inline auto operator+(const Vec3<T1>& v1, const Vec3<T2>& v2)
{
	return Vec3<decltype(v1.x + v2.x)>(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}
template<class T1, class T2>
inline auto operator-(const Vec3<T1>& v1, const Vec3<T2>& v2)
{
	return Vec3<decltype(v1.x - v2.x)>(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}
template<class T1, class T2>
inline auto operator*(const Vec3<T1>& v1, const Vec3<T2>& v2)
{
	return Vec3<decltype(v1.x * v2.x)>(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}
template<class T1, class T2>
inline auto operator/(const Vec3<T1>& v1, const Vec3<T2>& v2)
{
	return Vec3<decltype(v1.x / v2.x)>(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z);
}
template<class T>
std::ostream& operator<<(std::ostream& os, const Vec3<T>& v)
{
	os << "[" << v.x << " " << v.y << " " << v.z << "]" << std::endl;

	return os;
}
// Functions
template<class T1, class T2>
inline auto lerp(const Vec3<T1>& v1, const Vec3<T2>& v2, const double& percentage)
{
	return (1 - percentage) * v1 + percentage * v2;
}

// Usefull type def
typedef Vec3<float>			Vec3f;
typedef Vec3<double>		Vec3d;
typedef Vec3<unsigned int>	Vec3u;
typedef Vec3<int>			Vec3i;