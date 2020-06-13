#include "pch.h"
#include "Bomb.h"

using namespace Engine;


Bomb::Bomb(Ref<Model> model, const Transform& transform, float power)
	: GameObject(transform)
	, mModel(*model)
	, mPower(power)
	, mMaterial(true)
	, mMaterials({
		CreateRef<RawMaterial>(RawMaterial::Obsidian),
		CreateRef<RawMaterial>()
	 })
{
	SetScale(0.2);
	mModel.SetMaterial(mMaterials[0]);
}

Bomb::~Bomb()
{
}

void Bomb::OnUpdate(const double& delta)
{
	GameObject::OnUpdate(delta);

	mLifetime.lifetime += delta;

	if (mLifetime.lifetime >= mLifetime.time_until_explosion)
	{
		this->Animate();
	}
}

void Bomb::IncreasePower()
{
	mPower += 1.0f;
}

void Bomb::Animate()
{
	if (mLifetime.lifetime >= mLifetime.time_actual_explosion[2])
	{
		this->Explode();
	}
	else if (mLifetime.lifetime >= mLifetime.time_actual_explosion[1])
	{
		mModel.SetMaterial(mMaterials[1]); 
		mTransform.SetScale(mTransform.GetScale() * mLifetime.scale_factor);
		mLifetime.time_actual_explosion[1] += mLifetime.time_actual_explosion[0];
	}
	else if (mLifetime.lifetime >= mLifetime.time_explosion[1]
		&& mLifetime.lifetime < mLifetime.time_explosion[2])
	{	
		mModel.SetMaterial(
			(mMaterial ? mMaterials[0] : mMaterials[1])
		);
		mMaterial = !mMaterial;

		mLifetime.time_explosion[1] += mLifetime.time_explosion[0];
	}
}

void Bomb::Explode()
{
	hasExploded = true;
	for (auto wall : mSurroundingWalls)
	{
		wall->Explode();
	}
}

void Bomb::SetModel(
	Ref<Model> model)
{
	mModel = *model;
}

const Engine::Model& Bomb::GetModel() const
{
	return mModel;
}

void Bomb::GetSurroundingWalls(
	Map& world_map
)
{
	Vec4 majorPoints{
		mTransform.GetPosition().x - (mModel.GetSize().x / 2.0f * mTransform.GetScale().x),
		mTransform.GetPosition().x + (mModel.GetSize().x / 2.0f * mTransform.GetScale().x),
		mTransform.GetPosition().z - (mModel.GetSize().z / 2.0f * mTransform.GetScale().z),
		mTransform.GetPosition().z + (mModel.GetSize().z / 2.0f * mTransform.GetScale().z)
	};

	for (auto& wall : world_map.GetDestructibleWalls())
	{
		if (!wall.IsEnabled())
			continue;

		auto boundingBox = wall.GetComponent<BoxCollider>();
		
		Vec3 vector_between_centers = mTransform.GetPosition() - wall.GetTransform().GetPosition();
		
		float distance_x = std::abs(vector_between_centers.x);
		float distance_z = std::abs(vector_between_centers.z);

		float radius_x = mModel.GetSize().x / 2.0f * mTransform.GetScale().x;
		float radius_z = mModel.GetSize().z / 2.0f * mTransform.GetScale().z;

		float wall_size_x = wall.GetModel()->GetSize().x * wall.GetTransform().GetScale().x;
		float wall_size_z = wall.GetModel()->GetSize().z * wall.GetTransform().GetScale().z;

		if ((AreAlignOnAxis(majorPoints[0], majorPoints[1], boundingBox->GetMin().x, boundingBox->GetMax().x)
		||   AreAlignOnAxis(majorPoints[2], majorPoints[3], boundingBox->GetMin().z, boundingBox->GetMax().z))
		&&	(AreCloseEnough(radius_x, wall_size_x, distance_x)
		||   AreCloseEnough(radius_z, wall_size_z, distance_z)))
		{

			mSurroundingWalls.push_back(&wall);
		}
	}
}

bool Bomb::AreAlignOnAxis(float min_bomb_point, float max_bomb_point, float min_wall_point, float max_wall_point)
{	//	 Check if the bomb is aligned with the wall, like this :
	//	 _______      _______      _______
	//  |\ ___ /| or |\ ___ /| or |\ ___ /|
	//	| |	  | |	 | |   | |	  | |   | |
	//   \|O__|/	  \|_O_|/	   \|__O|/
	//	   	
	return min_wall_point <= min_bomb_point && max_bomb_point <= max_wall_point;
}

bool Bomb::AreCloseEnough(float bomb_radius, float wall_size, float distance)
{	//	  __
	// _O|__| -> min distance required between centers
	float min = bomb_radius + (wall_size * 0.5f);
	//	  __
	// O_|__| -> max distance authorized between centers
	// It increases with bomb's power
	float max = (wall_size * mPower) - bomb_radius;
	return distance >= min && distance <= max;
}


void Bomb::Render(Engine::Ref<Engine::RenderCommand> render_command, Engine::Ref<Engine::Shader> shader) const
{
	GameObject::Render(render_command, shader);
	Renderable::Render(&mModel, render_command, shader);
}
