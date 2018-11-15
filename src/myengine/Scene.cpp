#include "Scene.h"
#include "Entity.h"
#include "Camera.h"
#include "Core.h"


Scene::Scene(std::shared_ptr<Core> _c)
{
	m_core = _c;
	std::shared_ptr<Entity> m_camera = AddEntity();
	m_camera->AddComponent<Camera>();
	_c->SetCamera(m_camera);
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

	for (std::vector<std::shared_ptr<Entity> >::iterator it = m_entities.begin();
		it != m_entities.end(); it++)
	{
		if (!(*it)->m_alive)
		{
			//if an error wants us to kill it, we should kill it
			it = m_entities.erase(it);
			it--;
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

void Scene::Gui()
{
	for (std::vector<std::shared_ptr<Entity> >::iterator it = m_entities.begin();
		it != m_entities.end(); it++)
	{
		(*it)->Gui();
	}
}
