#include "Core.h"
#include "Entity.h"
#include "Resources.h"
#include "TestResource.h"
#include "Sound.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

Core::Core()
{
	_cameraAngleX = 0.0f, _cameraAngleY = 0.0f;
	// This represents the camera's orientation and position
	_cameraPosition = { 0, -0.09, -1.0f };
	_viewMatrix = glm::translate(glm::mat4(1.0f), _cameraPosition);


	// Set up a projection matrix
	_projMatrix = glm::perspective(glm::radians(45.0f), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);
	// Position of the light, in world-space
	_lightPosition = glm::vec3(10, 10, 0);

}

std::shared_ptr<Core> Core::init() 
{ 
	std::shared_ptr<Core> c = std::shared_ptr<Core>(new Core()); 
	c->StartSDL(); 
	c->m_resources = std::shared_ptr<Resources>(new Resources());
	c->m_lastTime = 0;

	//audio
	c->device = alcOpenDevice(NULL);

	if (!c->device)
	{
		throw MyEngineException("Unable to create audio device");
	}

	c->context = alcCreateContext(c->device, NULL);

	if (!c->context)
	{
		alcCloseDevice(c->device);
		throw MyEngineException("Unable to create audio context");
	}

	if (!alcMakeContextCurrent(c->context))
	{
		alcDestroyContext(c->context);
		alcCloseDevice(c->device);
		throw MyEngineException("Unable to make audio context current");
	}
	//end audio

	return c; 
}

Core::~Core()
{

	SDL_DestroyWindow(m_window);
	SDL_Quit();
	alcMakeContextCurrent(NULL);
	alcDestroyContext(context);
	alcCloseDevice(device);
}


std::shared_ptr<Entity> Core::AddEntity()
{
	//std::shared_ptr<Sound> s = m_resources->Load<Sound>("fan2.ogg");
	//s->Play();

	std::shared_ptr<Entity> rtn = std::shared_ptr<Entity>(new Entity());
	m_entities.push_back(rtn);
	rtn->SetCore(shared_from_this());
	rtn->m_alive = true;
	rtn->Init();
	
	return rtn;
}


void Core::StartSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		throw MyEngineException("Unable to init SDL Video");
	}

	m_window = SDL_CreateWindow("Triangle",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

	if (!SDL_GL_CreateContext(m_window))
	{
		throw MyEngineException("Unable to create SDL Window");
	}
	if (glewInit() != GLEW_OK)
	{
		throw MyEngineException("Unable to init GLEW");
	}

}

void Core::Start()
{
	m_running = true;
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	while (m_running)
	{
		SDL_Event event = { 0 };
		unsigned int current = SDL_GetTicks();
		m_deltaTs = (float)(current - m_lastTime) / 1000.0f;
		m_lastTime = current;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				m_running = false;
			}
			if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym) //what key has been pressed?
				{
				case SDLK_q:
					_cameraPosition.x += 0.01f;
					break;
				case SDLK_w:
					_cameraPosition.x -= 0.01f;
					break;
				case SDLK_e:
					_cameraPosition.y += 0.01f;
					break;
				case SDLK_r:
					_cameraPosition.y -= 0.01f;
					break;
				case SDLK_t:
					_cameraPosition.z += 0.01f;
					break;
				case SDLK_y:
					_cameraPosition.z -= 0.01f;
					break;
				case SDLK_a:
					_cameraAngleX += 0.05f;
					break;
				case SDLK_d:
					_cameraAngleX -= 0.05f;
					break;
				case SDLK_z:
					_cameraAngleY += 0.05f;
					break;
				case SDLK_c:
					_cameraAngleY -= 0.05f;
					break;
				}
			}
		}
		m_resources->CleanUp(m_deltaTs);

		for (std::vector<std::shared_ptr<Entity> >::iterator it = m_entities.begin();
			it != m_entities.end(); it++)
		{
			try
			{
				(*it)->Tick();
			}
			catch (MyEngineException e)
			{
				(*it)->m_alive = false;
			}
		}

		for (std::vector<std::shared_ptr<Entity> >::iterator it = m_entities.begin();
			it != m_entities.end(); it++)
		{
			if (!(*it)->m_alive)
			{
				//if an error wants us to kill it, we should kill it
				it = m_entities.erase(it);
				it--;
			}
		}

		//

		_viewMatrix = glm::rotate(glm::mat4(1.0f), _cameraAngleX, glm::vec3(1, 0, 0));
		_viewMatrix = glm::rotate(_viewMatrix, _cameraAngleY, glm::vec3(0, 1, 0));
		_viewMatrix = glm::translate(_viewMatrix, _cameraPosition);
		glClearColor(0.0f, 0.0f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);
		int x, y;
		SDL_GetWindowSize(m_window, &x, &y);
		glViewport(0, 0, x, y);
		// Set up a projection matrix
		_projMatrix = glm::perspective(glm::radians(45.0f), (float)x / (float)y, 0.1f, 100.0f);

		for (std::vector<std::shared_ptr<Entity> >::iterator it = m_entities.begin();
			it != m_entities.end(); it++)
		{
			(*it)->Display();
		}

		SDL_GL_SwapWindow(m_window);
	}
}

