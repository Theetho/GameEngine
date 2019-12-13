#pragma once

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
		Engine::Ref<Engine::GameObject> wall
	)
	{
		m_walls.push_back(wall);
		addCollider(wall);
	}

	inline void addFloor(
		Engine::Ref<Engine::GameObject> floor
	)
	{
		m_floor.push_back(floor);
		addCollider(floor);
	}

	//inline Engine::Ref<Engine::GameObject> operator[](const unsigned int& index)
	//{
	//	if (index < m_walls.size())
	//		return m_walls[index];
	//}

	//inline const Engine::Ref<Engine::GameObject> operator[](const unsigned int& index) const
	//{
	//	if (index < m_walls.size())
	//		return m_walls[index];
	//}

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

	inline std::vector<Engine::Ref<Engine::GameObject>>& getWalls()
	{
		return m_walls;
	}

	inline std::vector<Engine::Ref<Engine::GameObject>>& getFloor()
	{
		return m_floor;
	}

private:
	std::vector<Engine::Ref<Engine::GameObject>> m_walls;
	std::vector<Engine::Ref<Engine::GameObject>> m_floor;
	unsigned int m_width, m_height;
	Engine::Vec3 m_entry, m_exit, m_blockSize;

	void addCollider(
		Engine::Ref<Engine::GameObject> object
	);
};

