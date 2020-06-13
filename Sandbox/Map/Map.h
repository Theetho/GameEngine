#pragma once

#include "Floor.h"
#include "DestructibleWall.h"
#include "ExitCell.h"

class Map : public Engine::Renderable
{
public:
	Map(unsigned int width, unsigned int height,const Engine::Vec3& block_size);
	~Map();

	void OnUpdate(const double& delta, bool remove);
	void AddWalls(const Wall& wall);
	void AddWalls(const DestructibleWall& wall);
	void AddFloor(const Floor& floor);
	void AddFloor(const ExitCell& floor);

	const ExitCell&						 GetExit() const;
	const Engine::Vec3&					 GetEntry() const;
	const std::vector<Wall>&			 GetWalls() const;
	const std::vector<Floor>&			 GetFloor() const;
	std::vector<DestructibleWall>&		 GetDestructibleWalls();
	const std::vector<DestructibleWall>& GetDestructibleWalls() const;

	void SetEntry(const Engine::Vec3& entry);
private:
	ExitCell					  mExit;
	unsigned int				  mWidth, mHeight;
	Engine::Vec3				  mEntry, mBlockSize;
	std::vector<Wall>			  mWalls;
	std::vector<Floor>			  mFloor;
	std::vector<DestructibleWall> mDestructibleWalls;

	void Render(Engine::Ref<Engine::RenderCommand> render_command, Engine::Ref<Engine::Shader> shader) const override;
};

