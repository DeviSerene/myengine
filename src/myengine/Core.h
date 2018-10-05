#include <memory>
#include <vector>
#include <SDL2/SDL.h>
#include <GL/glew.h>

class Entity;

class Core : public std::enable_shared_from_this<Core>
{
public:
	Core();
	~Core();

	static std::shared_ptr<Core> init() { std::shared_ptr<Core> c = std::shared_ptr<Core>(new Core()); c->StartSDL(); return c; };
	void Start();
	void Stop();
	std::shared_ptr<Entity> AddEntity();

private:

	void StartSDL();

	bool running;
	std::vector<std::shared_ptr<Entity>> m_entities;
	SDL_Window* m_window;
};
