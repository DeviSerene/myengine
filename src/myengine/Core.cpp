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
}

std::shared_ptr<Core> Core::init() 
{ 
	std::shared_ptr<Core> c = std::shared_ptr<Core>(new Core()); 
	c->StartSDL(); 
	c->m_resources = std::shared_ptr<Resources>(new Resources());
	c->m_lastTime = 0;
	c->m_scene = 10;
	c->m_new = 10;
	c->m_changeScene = false;

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
	//c->m_compositor = std::shared_ptr<Compositor>(new Compositor(c->shared_from_this()));

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
	m_running = true;
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST); 
	glEnable(GL_BLEND);
	//sprites use alpha values, so they need to blend
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	while (m_running)
	{
		if (m_changeScene) //Is there a scene we need to switch to?
		{
			ChangeScene(m_new);
		}

		// DELTA TIME
		unsigned int current = SDL_GetTicks();
		m_deltaTs = (float)(current - m_lastTime) / 1000.0f;
		m_lastTime = current;

		//Handle Input
		m_keyboard->Update();
		m_running = !m_keyboard->Quit(); //Did the INPUT tell us to quit?
		//Cleanse Resources
		m_resources->CleanUp(m_deltaTs);
		
		//If we have a scene, go through each entity and Tick them
		if (m_scenes.size() > m_scene) 
			m_scenes[m_scene]->Tick();

		

		// Start Drawing the Scene
		int x, y;
		SDL_GetWindowSize(m_window, &x, &y);
		if (m_cameras.empty())
			return;
		for (int i = 0; i < m_cameras.size(); i++)
		{
			if (m_cameras[i])
			{
				glBindFramebuffer(GL_FRAMEBUFFER, m_cameras[i]->GetComponent<Camera>()->GetFrameBuffer()->GetBuffer());
				glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
				glClear(GL_COLOR_BUFFER_BIT);
				glClear(GL_DEPTH_BUFFER_BIT);
				glEnable(GL_DEPTH_TEST);
				// Set up a projection matrix

				m_currentCamera = i;
				_viewMatrix = m_cameras[i]->GetComponent<Camera>()->GetViewMatrix();
				_projMatrix = m_cameras[i]->GetComponent<Camera>()->GetProjMatrix();
				glViewport(0, 0, x, y);

				if (m_scenes.size() > m_scene)
				{
					m_scenes[m_scene]->Display();
					m_cameras[i]->GetComponent<Camera>()->PostDraw();
				}
			}

		}
		//PostProcessStuff
		_projMatrix = glm::ortho(0, x, 0, y, 0, 100);
		for (int i = 0; i < m_cameras.size(); i++)
		{
			if (m_cameras[i])
			{
				m_cameras[i]->PostProcess();
			}
		}
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);
		// Draw GUI
		glDisable(GL_DEPTH_TEST);
		m_gui->Flip(true);
		glm::vec4 pos = { -1, -1, 2, 2 };
		/*if (m_fbs.size() >= 2)
		{
			//m_gui->SetTexture(m_fbs[1]->GetTexture());
			m_gui->SetTexture(m_fbs[0]->GetTexture());
			m_gui->SetFrameInfo(glm::vec4(2, 1, 4, 1));
			pos = glm::vec4(-1, -1, 0.5f, 2.0f);
			m_gui->Sprite(pos);
			m_gui->SetFrameInfo(glm::vec4(3, 1, 4, 1));
			pos = glm::vec4(-0.5f, -1, 0.5f, 2.0f);
			m_gui->Sprite(pos);
			
			m_gui->SetTexture(m_fbs[1]->GetTexture());
			m_gui->SetFrameInfo(glm::vec4(2, 1, 4, 1));
			pos = glm::vec4(0, -1, 0.5f, 2);
			m_gui->Sprite(pos);
			m_gui->SetFrameInfo(glm::vec4(3, 1, 4, 1));
			pos = glm::vec4(0.5f, -1, 0.5f, 2);
			m_gui->Sprite(pos);
			
		}
		else*/
		//{
			m_gui->SetTexture(m_cameras[0]->GetComponent<Camera>()->GetTexture());
			m_gui->SetFrameInfo(glm::vec4(1, 1, 1, 1));
		//	m_gui->Sprite(pos);
		//}
		m_gui->Flip(false);
		if (m_scenes.size() > m_scene)
			m_scenes[m_scene]->Gui();

		

		SDL_GL_SwapWindow(m_window);
	}
}

glm::vec3 Core::GetCamera() { return m_cameras[m_currentCamera]->GetComponent<Camera>()->GetCameraPos(); }

void Core::ChangeScene(int _scene) 
{ 
	int old = m_scene;  
	m_scene = _scene; 
	if (m_scenes.size() > m_scene) 
	{ 
		if(m_scenes.size() > old)
			m_scenes[old]->OnDeInit(); 
		m_cameras.clear();
		//m_fbs.clear();
		m_scenes[m_scene]->OnInit(); 
	} 
	m_changeScene = false;
}
