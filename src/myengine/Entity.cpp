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
		for each (std::shared_ptr<Entity> baby in m_children)
			baby->Tick();
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
		for each (std::shared_ptr<Entity> baby in m_children)
			baby->Display();
	}
}

void Entity::Gui()
{
	if (!m_components.empty())
	{
		for (int i = 0; i < m_components.size(); i++)
		{
			m_components[i]->OnGui();
		}
		for each (std::shared_ptr<Entity> baby in m_children)
			baby->Gui();
	}
}







