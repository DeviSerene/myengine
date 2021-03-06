#include "Scene.h"
#include "Entity.h"
#include "Camera.h"
#include "Core.h"
#include "game/BattleScene.h"
#include "game/BossScene.h"


Scene::Scene(std::shared_ptr<Core> _c)
{
	m_core = _c;
}

std::shared_ptr<Entity> Scene::AddEntity()
{
	std::shared_ptr<Entity> rtn = std::shared_ptr<Entity>(new Entity());
	m_entities.push_back(rtn);
	rtn->SetCore(m_core.lock());
	rtn->m_alive = true;
	rtn->Init();

	return rtn;
}

void Scene::Tick()
{
	if (m_entities.empty())
		return;

	for (std::vector<std::shared_ptr<Entity> >::iterator it = m_entities.begin();
		it != m_entities.end(); it++)
	{
		try
		{
			(*it)->Tick();
		}
		catch (MyEngineException e)
		{
			(*it)->m_alive = false;
		}
	}
	for (int i = 0; i < m_entities.size(); i++)
	{
		if (!m_entities[i]->m_alive)
		{
			//if an error wants us to kill it, we should kill it
			m_entities.erase(m_entities.begin()+i);
			i--;
		}
	}
}

void Scene::Display()
{

	for (std::vector<std::shared_ptr<Entity> >::iterator it = m_entities.begin();
		it != m_entities.end(); it++)
	{
		(*it)->Display();
	}
}

void Scene::PostProcess()
{

	for (std::vector<std::shared_ptr<Entity> >::iterator it = m_entities.begin();
		it != m_entities.end(); it++)
	{
		(*it)->PostProcess();
	}
}

void Scene::Gui()
{
	for (std::vector<std::shared_ptr<Entity> >::iterator it = m_entities.begin();
		it != m_entities.end(); it++)
	{
		(*it)->Gui();
	}
}
