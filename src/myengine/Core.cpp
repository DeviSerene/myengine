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
	_viewMatrix = glm::translate(glm::mat4(1.0f), cameraPos);


	// Set up a projection matrix
	_projMatrix = glm::perspective(glm::radians(45.0f), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);
	// Position of the light, in world-space
	_lightPosition = glm::vec3(10, 10, 0);
	m_keyboard = std::shared_ptr<Keyboard>(new Keyboard());
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

}

void Core::Start()
{

	m_gui = std::shared_ptr<Gui>(new Gui());
	m_gui->Init(shared_from_this());
	m_running = true;
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);

	while (m_running)
	{
		mouse = false;
		SDL_Event event = { 0 };
		unsigned int current = SDL_GetTicks();
		m_deltaTs = (float)(current - m_lastTime) / 1000.0f;
		m_lastTime = current;
		/*
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				m_running = false;
			}
			if (event.type == SDL_MOUSEBUTTONDOWN) 
			{ 
				mouse = event.button.button; 
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
			m_keyboard->Update(event);
		}
		*/

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


		m_keyboard->Update();

		if (m_keyboard->Input(A_BUTTON))
		{
			std::cout << "A PRESSED" << std::endl;
		}
		if (m_keyboard->PressOnce(B_BUTTON))
		{
			rebindA = true;
			std::cout << "Press a key to rebind A: " << std::endl;
		}
		if (rebindA)
		{
			if (m_keyboard->ReturnKeyCode())
			{
				if (m_keyboard->ReBind(A_BUTTON, m_keyboard->ReturnKeyCode()))
				{
					std::cout << "A has been REBOUND" << std::endl;
					rebindA = false;
				}
			}
		}
		if (m_keyboard->Input(LEFT_BUTTON))
		{
			yaw -= 0.5f;
		//	cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * 0.05f;
			//_cameraAngleY -= 0.05f;
		}
		if (m_keyboard->Input(RIGHT_BUTTON))
		{
			yaw += 0.5f;
		//	cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * 0.05f;
			//_cameraAngleY += 0.05f;
		}
		if (m_keyboard->Input(LB_BUTTON))
		{
			pitch -= 0.5f;
			//	cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * 0.05f;
			//_cameraAngleY -= 0.05f;
		}
		if (m_keyboard->Input(RB_BUTTON))
		{
			pitch += 0.5f;
			//	cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * 0.05f;
			//_cameraAngleY += 0.05f;
		}
		if (m_keyboard->Input(UP_BUTTON))
		{
			cameraPos += 0.05f * cameraFront;
			//_cameraPosition -= glm::vec3(0.5f *_cameraPosition.x * _cameraAngleX, 0.5f  *_cameraPosition.y * _cameraAngleY, -0.05);
		}
		if (m_keyboard->Input(DOWN_BUTTON))
		{
			cameraPos -= 0.05f * cameraFront;
			//_cameraPosition += glm::vec3(0.5f  *_cameraPosition.x * _cameraAngleX, 0.5f  *_cameraPosition.y * _cameraAngleY, 0.05);
		}
		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;
		glm::vec3 front;
		front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
		front.y = sin(glm::radians(pitch));
		front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
		cameraFront = glm::normalize(front);
		// Start Drawing the Scene

		_viewMatrix = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		//_viewMatrix = glm::rotate(glm::mat4(1.0f), _cameraAngleX, glm::vec3(1, 0, 0));
		//_viewMatrix = glm::rotate(_viewMatrix, _cameraAngleY, glm::vec3(0, 1, 0));
		//_viewMatrix = glm::translate(_viewMatrix, _cameraPosition);
		glClearColor(0.0f, 0.0f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
		int x, y;
		SDL_GetWindowSize(m_window, &x, &y);
		// Set up a projection matrix
		_projMatrix = glm::perspective(glm::radians(45.0f), (float)x / (float)y, 0.1f, 100.0f);

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
		_projMatrix = glm::perspective(glm::radians(45.0f), (float)x / (float)y, 0.1f, 100.0f);

		SDL_GL_SwapWindow(m_window);
	}
}

