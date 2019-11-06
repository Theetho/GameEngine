#pragma once

#include "GameObject/Cube.h"

class Maze
{
public:
	Maze(
		const unsigned int& width,
		const unsigned int& height
	);
	~Maze();

	inline void addWalls(
		Cube* cube
	)
	{
		m_walls.push_back(cube);
	}

	inline void addGround(
		Cube* cube
	)
	{
		m_ground.push_back(cube);
	}

	inline Cube* operator[](const unsigned int& index)
	{
		if (index < m_walls.size())
			return m_walls[index];
	}

	inline const Cube* operator[](const unsigned int& index) const
	{
		if (index < m_walls.size())
			return m_walls[index];
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

	inline std::vector<Cube*>& getWalls()
	{
		return m_walls;
	}

	inline std::vector<Cube*>& getGround()
	{
		return m_ground;
	}

private:
	std::vector<Cube*> m_walls;
	std::vector<Cube*> m_ground;
	unsigned int m_width, m_height;
	Engine::Vec3 m_entry, m_exit;
};

