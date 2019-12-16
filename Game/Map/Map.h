#pragma once

#include "Floor.h"
#include "DestructibleWall.h"
#include "ExitCell.h"

class Map
{
public:
	Map(
		const unsigned int& width,
		const unsigned int& height,
		const Engine::Vec3& blockSize
	);

	~Map();

	void onUpdate(
		const double& delta,
		bool remove
	);

	inline void addWalls(
		const Wall& wall
	)
	{
		m_walls.push_back(std::move(wall));
	}

	inline void addWalls(
		const DestructibleWall& wall
	)
	{
		m_destructibleWalls.push_back(std::move(wall));
	}

	inline void addFloor(
		const Floor& floor
	)
	{
		m_floor.push_back(std::move(floor));
	}

	inline void addFloor(
		const ExitCell& floor
	)
	{
		m_exit = floor;
	}

	inline const ExitCell& getExit() const
	{
		return m_exit;
	}

	inline const Engine::Vec3& getEntry() const
	{
		return m_entry;
	}
	
	inline void setEntry(
		const Engine::Vec3& entry
	)
	{
		m_entry = entry;
	}

	inline const std::vector<Wall>& getWalls() const
	{
		return m_walls;
	}

	inline const std::vector<DestructibleWall>& getDestructibleWalls() const
	{
		return m_destructibleWalls;
	}
	
	inline std::vector<DestructibleWall>& getDestructibleWalls()
	{
		return m_destructibleWalls;
	}

	inline const std::vector<Floor>& getFloor() const
	{
		return m_floor;
	}

private:
	std::vector<Wall> m_walls;
	std::vector<DestructibleWall> m_destructibleWalls;
	std::vector<Floor> m_floor;
	ExitCell m_exit;
	unsigned int m_width, m_height;
	Engine::Vec3 m_entry, m_blockSize;
};

