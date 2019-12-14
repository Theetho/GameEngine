#include "pch.h"
#include "Bomb.h"

using namespace Engine;


Bomb::Bomb(
	Ref<Model> model,
	const Transform& transform
)
	: GameObject(transform)
	, m_model(*model)
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
		this->explode();
	}
}

void Bomb::explode()
{
	if (m_lifetime.lifetime >= m_lifetime.timesActualExplosion[2])
	{
		this->hasExploded = true;
	}
	else if (m_lifetime.lifetime >= m_lifetime.timesActualExplosion[1])
	{
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

void Bomb::setModel(
	Ref<Model> model)
{
	m_model = *model;
}