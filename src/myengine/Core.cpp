#include "Core.h"
#include "Entity.h"
#include "Resources.h"
#include "TestResource.h"
#include "Sound.h"
#include "Texture.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

Core::Core()
{
	// Position of the light, in world-space
	_lightPosition = glm::vec3(10, 10, 0);
	rebindA = false;

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
	//c->m_fb = std::shared_ptr<FrameBuffer>(new FrameBuffer());


	c->m_gui = std::shared_ptr<Gui>(new Gui());
	c->m_gui->Init(c->shared_from_this());

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
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER | SDL_INIT_JOYSTICK) < 0)
	{
		throw MyEngineException("Unable to init SDL");
	}

	m_window = SDL_CreateWindow("Hello World",
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

	m_keyboard = std::shared_ptr<Keyboard>(new Keyboard());
}

void Core::Start()
{
	m_camera = AddEntity();
	m_camera->AddComponent<Camera>();
	m_running = true;
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST); 
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glDisable(GL_BLEND);

	while (m_running)
	{
		m_running = !m_keyboard->Quit();
		//
		unsigned int current = SDL_GetTicks();
		m_deltaTs = (float)(current - m_lastTime) / 1000.0f;
		m_lastTime = current;
		//
		SDL_Event event = { 0 };
		m_keyboard->Update();

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
		////
		if (m_keyboard->Input(A_BUTTON))
		{
			std::cout << "A PRESSED" << std::endl;
		}
		if (m_keyboard->Input(B_BUTTON))
		{
			rebindA = true;
			std::cout << "Press a key to rebind A: " << std::endl;
		}
		else if (rebindA)
		{
			if (m_keyboard->ReturnKeyCode())
			{
				if (m_keyboard->ReBind(A_BUTTON, m_keyboard->ReturnKeyCode()))
				{
					std::cout << "A has been REBOUND" << std::endl;
					rebindA = false;
				}
				
			}
			else if (m_keyboard->ReBindButton(A_BUTTON, m_keyboard->ReturnButton()))
			{
				std::cout << "A has been REBOUND" << std::endl;
				rebindA = false;
			}
		}
		if (m_keyboard->Input(RT_BUTTON))
		{
			std::cout << "RIGHT TRIGGERD  ";
			//_cameraPosition += glm::vec3(0.5f  *_cameraPosition.x * _cameraAngleX, 0.5f  *_cameraPosition.y * _cameraAngleY, 0.05);
		}

		// Start Drawing the Scene
		int x, y;
		SDL_GetWindowSize(m_window, &x, &y);
		glClearColor(0.0f, 0.0f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
		// Set up a projection matrix
		_viewMatrix = m_camera->GetComponent<Camera>()->GetViewMatrix();
		_projMatrix = m_camera->GetComponent<Camera>()->GetProjMatrix();
		
		/*
		glBindFramebuffer(GL_FRAMEBUFFER, m_fb->GetBuffer());
		glViewport(0, 0, 1024, 768);
		for (std::vector<std::shared_ptr<Entity> >::iterator it = m_entities.begin();
			it != m_entities.end(); it++)
		{
			(*it)->Display();
		}
		*/

		glViewport(0, 0, x, y);
		for (std::vector<std::shared_ptr<Entity> >::iterator it = m_entities.begin();
			it != m_entities.end(); it++)
		{
			(*it)->Display();
		}
		// Draw GUI
		glDisable(GL_DEPTH_TEST);
		_projMatrix = glm::ortho(0, x, 0, y, 0, 100);
		for (std::vector<std::shared_ptr<Entity> >::iterator it = m_entities.begin();
			it != m_entities.end(); it++)
		{
			(*it)->Gui();
		}

		SDL_GL_SwapWindow(m_window);
	}
}

