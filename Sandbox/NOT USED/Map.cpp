#include "pch.h"
#include "Map.h"

using namespace Engine;

Map::Map(unsigned int width, unsigned int height, const Vec3& block_size)
	: mWidth(width)
	, mHeight(height)
	, mBlockSize(block_size)
	, mEntry()
{}

Map::~Map()
{}

void Map::OnUpdate(const double& delta, bool remove)
{
	// We only remove the walls that exploded
	// when their is no more bombs in the world
	// otherwise their are some problems with
	// pointers in the destructible walls vector
	// (bombs explode the wrong walls)
	if (!remove)
		return;

	mDestructibleWalls.erase(
		std::remove_if(
			mDestructibleWalls.begin(),
			mDestructibleWalls.end(),
			[](const DestructibleWall& wall)
			{
				return wall.hasExploded;
			}
		),
		mDestructibleWalls.end()
	);
}

void Map::AddWalls(const Wall& wall)
{
	mWalls.push_back(std::move(wall));
}

void Map::AddWalls(const DestructibleWall& wall)
{
	mDestructibleWalls.push_back(std::move(wall));
}

void Map::AddFloor(const Floor& floor)
{
	mFloor.push_back(std::move(floor));
}

void Map::AddFloor(const ExitCell& floor)
{
	mExit = floor;
}

const ExitCell& Map::GetExit() const
{
	return mExit;
}

const Engine::Vec3& Map::GetEntry() const
{
	return mEntry;
}

const std::vector<Wall>& Map::GetWalls() const
{
	return mWalls;
}

const std::vector<DestructibleWall>& Map::GetDestructibleWalls() const
{
	return mDestructibleWalls;
}

std::vector<DestructibleWall>& Map::GetDestructibleWalls()
{
	return mDestructibleWalls;
}

const std::vector<Floor>& Map::GetFloor() const
{
	return mFloor;
}

void Map::SetEntry(const Engine::Vec3& entry)
{
	mEntry = entry;
}

void Map::Render(Ref<RenderCommand> render_command, Ref<Shader> shader) const
{
	for (auto& wall : mWalls)
	{
		Renderable::Render(&wall, render_command, shader);
	}
	for (auto& wall : mDestructibleWalls)
	{
		Renderable::Render(&wall, render_command, shader);
	}
	for (auto& floor : mFloor)
	{
		Renderable::Render(&floor, render_command, shader);
	}
	Renderable::Render(&mExit, render_command, shader);
}
