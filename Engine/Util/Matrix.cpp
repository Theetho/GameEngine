#include "EnginePch.h"
#include "Matrix.h"

namespace Engine
{
	Mat4 Matrix::model( 
		const Vec3& translation, 
		const Vec3& rotation, 
		const Vec3& scale
	)
	{
		Mat4 result(1.f);
		result = glm::translate(result, translation);
		/* IF THERE IS A PROBLEM, REMOVE RADIANS CONVERSION */
		result = glm::rotate(result, glm::radians(rotation.x), { 1, 0, 0 });
		result = glm::rotate(result, glm::radians(rotation.y), { 0, 1, 0 });
		result = glm::rotate(result, glm::radians(rotation.z), { 0, 0, 1 });
		result = glm::scale(result, scale);

		return result;
	}
	Mat4 Matrix::view(
		const Camera3D& camera
	)
	{
		Mat4 matrix(1.f);
		matrix = glm::rotate(matrix, glm::radians(camera.getPitch()), { 1, 0, 0 });
		matrix = glm::rotate(matrix, glm::radians(camera.getYaw()), { 0, 1, 0 });
		matrix = glm::rotate(matrix, glm::radians(camera.getRoll()), { 0, 0, 1 });
		matrix = glm::translate(matrix, - camera.getPosition());
		
		return matrix;
	}
}