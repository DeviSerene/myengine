#include "Core.h"
#include "Entity.h"
#include "Resources.h"
#include "TestResource.h"
#include "Sound.h"
#include "Texture.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

Core::Core()
{
	// Position of the light, in world-space
	_lightPosition = glm::vec3(0, 1, 0);
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

void Core::StartSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER | SDL_INIT_JOYSTICK) < 0)
	{
		throw MyEngineException("Unable to init SDL");
	}

	m_window = SDL_CreateWindow("Ophilia Traveller",
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

	//Initialize SDL_ttf
	if (TTF_Init() == -1)
	{
		throw MyEngineException("Unable to init SDL_TTF");
	}

	//Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		throw MyEngineException("Unable to init SDL_PNG");
	}

	m_keyboard = std::shared_ptr<Keyboard>(new Keyboard());
}

void Core::Start()
{
	//m_camera = AddEntity();
	//m_camera->AddComponent<Camera>();
	m_fb = std::shared_ptr<FrameBuffer>(new FrameBuffer());
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
		
		if (m_scene)
			m_scene->Tick();

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
		m_fb->Update(x, y);
		glBindFramebuffer(GL_FRAMEBUFFER, m_fb->GetBuffer());
		glClearColor(0.0f, 0.0f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
		// Set up a projection matrix
		if (m_camera)
		{
			_viewMatrix = m_camera->GetComponent<Camera>()->GetViewMatrix();
			_projMatrix = m_camera->GetComponent<Camera>()->GetProjMatrix();
		}
		glViewport(0, 0, x, y);

		if(m_scene)
			m_scene->Display();

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClearColor(0.0f, 0.0f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);
		// Draw GUI
		glDisable(GL_DEPTH_TEST);
		_projMatrix = glm::ortho(0, x, 0, y, 0, 100);
		m_gui->Flip(true);
		m_gui->SetTexture(m_fb->GetTexture());
		m_gui->SetHighlight(m_fb->GetTexture());
		//m_gui->SetHighlight(m_fb->GetDepth());
		m_gui->SetFrameInfo(glm::vec4(1, 1, 1, 1));
		glm::vec4 pos = { -1, -1, 2, 2 };
		m_gui->Sprite(pos);
		m_gui->Flip(false);
		if (m_scene)
			m_scene->Gui();

		SDL_GL_SwapWindow(m_window);
	}
}

glm::vec3 Core::GetCamera() { return m_camera->GetComponent<Camera>()->GetCameraPos(); }