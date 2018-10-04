#include <memory>
#include <vector>

class Entity;

class Core
{
public:
	Core();
	~Core();

	static std::shared_ptr<Core> init() { return (std::shared_ptr<Core>)new Core(); };
	void Start();
	void Stop();
	std::shared_ptr<Entity> AddEntity();

private:
	bool running;
	std::vector<std::shared_ptr<Entity>> m_entities;
};
