#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>
#include "assimp/matrix4x4.h"
#include "assimp/quaternion.h"

namespace Engine
{
	template<int L>
	using Vec = glm::vec<L, float, glm::packed_highp>;
	typedef glm::vec2 Vec2;
	typedef glm::vec3 Vec3;
	typedef glm::vec4 Vec4;
	typedef glm::mat3 Mat3;
	typedef glm::mat4 Mat4;
	typedef glm::quat Quaternion;

	static aiQuaternion Interpolate(const aiQuaternion& q1, const aiQuaternion& q2, double factor)
	{
		aiQuaternion result;
		aiQuaternion::Interpolate(result, q1, q2, factor);
		result = result.Normalize();

		return result;
	}
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
static std::ostream& operator<<(std::ostream& os, const Engine::Quaternion& q)
{
	os << "[ " << q.x << " " << q.y << " " << q.z << " " << q.w << " ]";

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

static std::ostream& operator<<(std::ostream& os, const aiMatrix4x4& m)
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
static Engine::Mat4 AssimpToGlm(const aiMatrix4x4& matrix)
{
	return glm::transpose(glm::make_mat4(&matrix.a1));
}

static Engine::Quaternion AssimpToGlm(const aiQuaternion& quaternion)
{
	return Engine::Quaternion(quaternion.x, quaternion.y, quaternion.z, quaternion.w);
}

static Engine::Vec3 AssimpToGlm(const aiVector3D& vector)
{
	return Engine::Vec3(vector.x, vector.y, vector.z);
}

