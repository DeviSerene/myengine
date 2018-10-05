#include "Core.h"
#include "Entity.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

Core::Core()
{
}

Core::~Core()
{

	SDL_DestroyWindow(m_window);
	SDL_Quit();

}


std::shared_ptr<Entity> Core::AddEntity()
{
	std::shared_ptr<Entity> rtn = std::shared_ptr<Entity>(new Entity());
	m_entities.push_back(rtn);
	rtn->SetCore(shared_from_this());

	rtn->Init();
	
	return rtn;
}


void Core::StartSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		throw std::exception();
	}

	m_window = SDL_CreateWindow("Triangle",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

	if (!SDL_GL_CreateContext(m_window))
	{
		throw std::exception();
	}
	if (glewInit() != GLEW_OK)
	{
		throw std::exception();
	}

}