#pragma once

#include "Floor.h"
#include "Wall.h"

class Map
{
public:
	Map(
		const unsigned int& width,
		const unsigned int& height,
		const Engine::Vec3& blockSize
	);

	~Map();

	inline void addWalls(
		const Wall& wall
	)
	{
		m_walls.push_back(std::move(wall));
	}

	inline void addFloor(
		const Floor& floor
	)
	{
		m_floor.push_back(std::move(floor));
	}

	inline const Engine::Vec3& getEntry() const
	{
		return m_entry;
	}
	
	inline const Engine::Vec3& getExit() const
	{
		return m_exit;
	}

	inline void setEntry(
		const Engine::Vec3& entry
	)
	{
		m_entry = entry;
	}

	inline void setExit(
		const Engine::Vec3& exit
	)
	{
		m_exit = exit;
	}

	inline std::vector<Wall>& getWalls()
	{
		return m_walls;
	}

	inline std::vector<Floor>& getFloor()
	{
		return m_floor;
	}

private:
	std::vector<Wall> m_walls;
	std::vector<Floor> m_floor;
	unsigned int m_width, m_height;
	Engine::Vec3 m_entry, m_exit, m_blockSize;
};

