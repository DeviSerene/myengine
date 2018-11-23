#pragma once
#include <memory>
#include <vector>
#include "MyEngineException.h"
#include "Component.h"


class Core;
class Entity;

/*!
A scene contains Entities. Multiple scenes can be stored in the Core, to enable quick switching between them.
Tick, Display, etc, will tell all entities to do that action.
The user can create new Scenes by inheriting from this class, and then adding the scene to core.
*/

class Scene : public std::enable_shared_from_this<Scene>
{
public:
	Scene(std::shared_ptr<Core> _c);

	void Tick();
	void Display();
	void Gui();
	void PostProcess();

	std::shared_ptr<Entity> AddEntity();
	virtual void OnDeInit() {}

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

	virtual void OnInit() {}
protected:
	std::vector<std::shared_ptr<Entity>> m_entities;
	std::weak_ptr<Core> m_core;

};