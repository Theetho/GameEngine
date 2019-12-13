#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>

namespace Engine
{
	typedef glm::vec2 Vec2;
	typedef glm::vec3 Vec3;
	typedef glm::vec4 Vec4;
	typedef glm::mat3 Mat3;
	typedef glm::mat4 Mat4;
}
#include <iostream>

static std::ostream& operator<<(std::ostream& os, const Engine::Vec2& v)
{
	os << "[ " << v.x << " " << v.y << " ]";

	return os;
}
static std::ostream& operator<<(std::ostream& os, const Engine::Vec3& v)
{
	os << "[ " << v.x << " " << v.y << " " << v.z << " ]";

	return os;
}
static std::ostream& operator<<(std::ostream& os, const Engine::Vec4& v)
{
	os << "[ " << v.x << " " << v.y << " " << v.z << " " << v.w << " ]";

	return os;
}
static std::ostream& operator<<(std::ostream& os, const Engine::Mat3& m)
{
	for (unsigned int i = 0; i < 3; ++i)
	{
		os << "[ ";
		for (unsigned int j = 0; j < 3; ++j)
		{
			os << m[i][j] << " ";
		}
		os << " ]" << std::endl;
	}

	return os;
}
static std::ostream& operator<<(std::ostream& os, const Engine::Mat4& m)
{
	for (unsigned int i = 0; i < 4; ++i)
	{
		os << "[ ";
		for (unsigned int j = 0; j < 4; ++j)
		{
			os << m[i][j] << " ";
		}
		os << " ]" << std::endl;
	}

	return os;
}
