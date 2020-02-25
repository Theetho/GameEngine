#pragma once

#include "Include/Maths.h"

namespace Engine
{
	enum class BufferUsage { STATIC, DYNAMIC };

	template<int dimension>
	struct Vertex
	{
		Vec<dimension> position;
		Vec2		   texture_coordinates;
		Color		   color;
		uint		   texture_id;
	};
}