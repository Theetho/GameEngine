#include "EnginePch.h"
#include "Matrix.h"

namespace Engine
{
	Mat4 Matrix::Model(const Vec3& translation, const Vec3& rotation, const Vec3& scale)
	{
		Mat4 result(1.f);
		result = glm::translate(result, translation);
		result = glm::rotate(result, glm::radians(rotation.x), { 1, 0, 0 });
		result = glm::rotate(result, glm::radians(rotation.y), { 0, 1, 0 });
		result = glm::rotate(result, glm::radians(rotation.z), { 0, 0, 1 });
		result = glm::scale(result, scale);

		return result;
	}
	Mat4 Matrix::View(const Camera3D& camera)
	{
		Mat4 matrix(1.f);
		matrix = glm::rotate(matrix, glm::radians(camera.GetPitch()), { 1, 0, 0 });
		matrix = glm::rotate(matrix, glm::radians(camera.GetYaw()),   { 0, 1, 0 });
		matrix = glm::rotate(matrix, glm::radians(camera.GetRoll()),  { 0, 0, 1 });
		matrix = glm::translate(matrix, - camera.GetPosition());
		
		return matrix;
	}
	Mat4 Matrix::Projection(double field_of_view, double aspect_ratio, double _near, double _far)
	{
		return glm::perspective(glm::radians(field_of_view), aspect_ratio, _near, _far);
	}
}