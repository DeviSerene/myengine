#include <memory>
#include <vector>

class Core;

class Entity
{
public:
	std::shared_ptr<Core> GetCore() { return m_core; }


private:
	std::shared_ptr<Core> m_core;
	void tick() {};
	void displayer() {};

};