#pragma once

#include "Maths.h"
#include "Event.h"

namespace Engine
{
	class GameObject;

	class Camera3D
	{
	public:
		Camera3D(
			const Vec3& position = Vec3(0.0f, 1.0f, 0.0f),
			const Vec3& target = Vec3(0.0f, 0.0f, 0.0f),
			const Vec3& up = Vec3(0.0f, 1.0f, 0.0f)
		);

		virtual ~Camera3D();

		virtual void onUpdate(
			const double& delta
		);

		virtual void onEvent(
			Event& event
		);

		inline void setPosition(
			const Vec3& position
		)
		{
			m_axis.position = position;
		}

		inline const Vec3& getPosition() const
		{
			return m_axis.position;
		}

		inline const Vec3& getTarget() const
		{
			return m_axis.target;
		}
		
		inline const Vec3& getUp() const
		{
			return m_axis.up;
		}

		inline const Mat4& getView() const
		{
			return m_view;	
		}
		
		inline const Mat4& getProjection() const
		{
			return m_projection;
		}
		
		inline const Mat4& getVP() const
		{
			return m_VP;
		}

	protected:
		Mat4 m_view;
		Mat4 m_projection;
		Mat4 m_VP;

		struct Axis
		{
			Vec3 position;
			Vec3 target;
			Vec3 up;

			Axis(
				const Vec3& position,
				const Vec3& target,
				const Vec3& up
			)
				: position(position)
				, target(target)
				, up(up)
			{
			}
		};
		Axis m_axis;

		void updateVP();
	};

	class Camera3DLocked : public Camera3D
	{
	public:
		Camera3DLocked(
			const GameObject& target,
			const Vec3& offset
		);
		~Camera3DLocked();

		void onUpdate(
			const double& delta
		) override;

		void onEvent(
			Event& event
		) override;

		inline void setOffset(
			const Vec3& offset
		)
		{
			m_offset = offset;
		}

		inline const Vec3& getOffset() const
		{
			return m_offset;
		}

	private:
		const GameObject& m_target;

		Vec3 m_offset;
	};
}

