#pragma once
#include <memory>

class Entity;
class Core;
class Keyboard;
class Scene;

/*!
Components are reusable pieces that are attached to gameobjects (Entities).
The Component class is a virtual class that should be inherited when Components are made.
Components will then be able to overrife the OnInit, OnTick, etc functions, to be able to bring in their own game logic.
A component can access their Entity, and from there, access the scene and Core, to access the rest of the resources.
*/

class Component
{
public:
	Component();
	~Component();

	std::shared_ptr<Entity> GetEntity();
	std::shared_ptr<Core> GetCore();
	std::shared_ptr<Keyboard> GetKeyboard();
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