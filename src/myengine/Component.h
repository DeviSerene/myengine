#pragma once
#include <memory>

class Entity;
class Core;
class Keyboard;
class Environment;
class Scene;

class Component
{
public:
	Component();
	~Component();

	std::shared_ptr<Entity> GetEntity();
	std::shared_ptr<Core> GetCore();
	std::shared_ptr<Keyboard> GetKeyboard();
	std::shared_ptr<Environment> GetEnvironment();
	std::shared_ptr<Scene> GetScene();

	void SetEntity(std::shared_ptr<Entity> _e) { m_entity = _e; }

	virtual void OnInit();
	virtual void OnBegin();
	virtual void OnTick();
	virtual void OnDisplay();
	virtual void OnGui();
	virtual void OnPostProcess();

	void HasBegun() { if (m_began == false) { OnBegin(); m_began = true; } }
private:

	bool m_began;

	std::weak_ptr<Entity> m_entity;
};