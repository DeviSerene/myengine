#pragma once
#include <memory>
#include <vector>
#include "MyEngineException.h"
#include "Component.h"


class Core;
class Entity;

class Scene : public std::enable_shared_from_this<Scene>
{
public:
	Scene(std::shared_ptr<Core> _c);

	void Tick();
	void Display();
	void Gui();

	std::shared_ptr<Entity> AddEntity();

	template <typename T>
	std::vector<std::shared_ptr<T>> GetAllComponents()
	{
		std::vector<std::shared_ptr<T>> ret;
		for each (std::shared_ptr<Entity> entity in m_entities)
		{
			if (entity->GetComponent<T>())
			{
				ret.push_back(entity->GetComponent<T>());
			}
		}
		return ret;
	}

private:
	std::vector<std::shared_ptr<Entity>> m_entities;
	std::weak_ptr<Core> m_core;

};