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

private:
	void OnInit();
	void OnBegin();
	void OnTick();
	void OnDisplay();


	std::weak_ptr<Entity> m_entity;
};