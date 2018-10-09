#include "Entity.h"
#include "Component.h"
#include "Core.h"

Entity::Entity()
{
}

Entity::~Entity()
{

}

void Entity::Tick()
{
	if (!m_components.empty())
	{
		for (int i = 0; i < m_components.size(); i++)
		{
			m_components[i]->HasBegun();

			m_components[i]->OnTick();
		}
	}
}

void Entity::Display()
{
	if (!m_components.empty())
	{
		for (int i = 0; i < m_components.size(); i++)
		{
			m_components[i]->OnDisplay();
		}
	}
}







