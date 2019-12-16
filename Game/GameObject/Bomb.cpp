#include "pch.h"
#include "Bomb.h"

using namespace Engine;


Bomb::Bomb(
	Ref<Model> model,
	const Transform& transform,
	float power
)
	: GameObject(transform)
	, m_model(*model)
	, m_power(power)
	, m_material(true)
	, m_materials({
		std::make_shared<RawMaterial>(RawMaterial::Obsidian),
		std::make_shared<RawMaterial>()
	 })
{
	setScale(0.2);
	m_model.setMaterial(m_materials[0]);
}

Bomb::~Bomb()
{
}

void Bomb::onUpdate(
	const double& delta
)
{
	GameObject::onUpdate(delta);

	m_lifetime.lifetime += delta;


	if (m_lifetime.lifetime >= m_lifetime.timeUntilExplosion)
	{
		this->animate();
	}
}

void Bomb::animate()
{
	if (m_lifetime.lifetime >= m_lifetime.timesActualExplosion[2])
	{
		this->explode();
	}
	else if (m_lifetime.lifetime >= m_lifetime.timesActualExplosion[1])
	{
		m_model.setMaterial(m_materials[1]); 
		m_transform.setScale(m_transform.getScale() * m_lifetime.scaleFactor);
		m_lifetime.timesActualExplosion[1] += m_lifetime.timesActualExplosion[0];
	}
	else if (m_lifetime.lifetime >= m_lifetime.timesExplosion[1]
		&& m_lifetime.lifetime < m_lifetime.timesExplosion[2])
	{	
		m_model.setMaterial(
			(m_material ? m_materials[0] : m_materials[1])
		);
		m_material = !m_material;

		m_lifetime.timesExplosion[1] += m_lifetime.timesExplosion[0];
	}

}

void Bomb::explode()
{
	hasExploded = true;
	for (auto wall : m_surroundingWalls)
	{
		wall->explode();
	}
}

void Bomb::setModel(
	Ref<Model> model)
{
	m_model = *model;
}

void Bomb::getSurroundingWalls(
	Map& worldMap
)
{
	Vec4 majorPoints{
		m_transform.getPosition().x - (m_model.getSize().x / 2.0f * m_transform.getScale().x),
		m_transform.getPosition().x + (m_model.getSize().x / 2.0f * m_transform.getScale().x),
		m_transform.getPosition().z - (m_model.getSize().z / 2.0f * m_transform.getScale().z),
		m_transform.getPosition().z + (m_model.getSize().z / 2.0f * m_transform.getScale().z)
	};

	for (auto& wall : worldMap.getDestructibleWalls())
	{
		if (!wall.isEnabled())
			continue;

		auto boundingBox = wall.GetComponent<BoxCollider>();
		
		Vec3 vectorBetweenCenters = m_transform.getPosition() - wall.getTransform().getPosition();
		
		float distanceX = std::abs(vectorBetweenCenters.x);
		float distanceZ = std::abs(vectorBetweenCenters.z);

		float radiusX = m_model.getSize().x / 2.0f * m_transform.getScale().x;
		float radiusZ = m_model.getSize().z / 2.0f * m_transform.getScale().z;

		float wallSizeX = wall.getModel()->getSize().x * wall.getTransform().getScale().x;
		float wallSizeZ = wall.getModel()->getSize().z * wall.getTransform().getScale().z;

		if ((areAlignOnAxis(majorPoints[0], majorPoints[1], boundingBox->getMin().x, boundingBox->getMax().x)
		||   areAlignOnAxis(majorPoints[2], majorPoints[3], boundingBox->getMin().z, boundingBox->getMax().z))
		&&	(areCloseEnough(radiusX, wallSizeX, distanceX)
		||   areCloseEnough(radiusZ, wallSizeZ, distanceZ)))
		{

			m_surroundingWalls.push_back(&wall);
		}
	}
}

bool Bomb::areAlignOnAxis(
	float minBombPoint,
	float maxBombPoint,
	float minWallPoint,
	float maxWallPoint
)
{	//	 Check if the bomb is aligned with the wall, like this :
	//	 _______      _______      _______
	//  |\ ___ /| or |\ ___ /| or |\ ___ /|
	//	| |	  | |	 | |   | |	  | |   | |
	//   \|O__|/	  \|_O_|/	   \|__O|/
	//	   	
	return minWallPoint <= minBombPoint && maxBombPoint <= maxWallPoint;
}

bool Bomb::areCloseEnough(
	float bombRadius,
	float wallSize,
	float distance
)
{	//	  __
	// _O|__| -> min distance required between centers
	float min = bombRadius + (wallSize * 0.5f);
	//	  __
	// O_|__| -> max distance authorized between centers
	// It increases with bomb's power
	float max = (wallSize * m_power) - bombRadius;
	return distance >= min && distance <= max;
}
