#pragma once

#include "Util/Color.h"

namespace Engine
{
	class Light
	{
	public:
		Light(
			const Color& color
		);

		virtual ~Light()
		{
		}

		inline void setColor(
			const Color& color
		)
		{
			m_color = color;
		}

		inline const Color& getColor() const
		{
			return m_color;
		}

	private:
		Color m_color;
	};
}
