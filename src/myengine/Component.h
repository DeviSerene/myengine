#include <memory>

class Entity;
class Core;
class Keyboard;
class Environment;

class Component
{
public:
	Component();
	~Component();

	std::shared_ptr<Entity> GetEntity();
	std::shared_ptr<Core> GetCore();
	std::shared_ptr<Keyboard> GetKeyboard();
	std::shared_ptr<Environment> GetEnvironment();

	void SetEntity(std::shared_ptr<Entity> _e) { m_entity = _e; }

	virtual void OnInit();

private:
	virtual void OnBegin();
	virtual void OnTick();
	virtual void OnDisplay();


	std::weak_ptr<Entity> m_entity;
};