#pragma once
#include <iostream>
#include <exception>
#include "MyEngineException.h"
#include "Framebuffer.h"
#include <string>
#include <memory>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_gamecontroller.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/sdl_image.h>
#include <GL/glew.h>
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <AL/al.h>
#include <AL/alc.h>
#include "Gui.h"
#include "Keyboard.h"
#include "Transform.h"
#include "Camera.h"
#include "Scene.h"
#include "Compositor.h"

class Entity;
class Resources;

class Core : public std::enable_shared_from_this<Core>
{
public:
	Core();
	~Core();

	static std::shared_ptr<Core> init();
	void Start();
	void Stop();

	std::shared_ptr<Keyboard> GetKeyboard() { return m_keyboard; }
	std::shared_ptr<Gui> GetGui() { return m_gui; }
	std::shared_ptr<Resources> GetResources() { return m_resources; }
	glm::vec3 GetCamera();
	glm::mat4 GetVM() { return _viewMatrix; }
	glm::mat4 GetPM() { return _projMatrix; }
	glm::vec2 GetMouseLocation() { int x, y; SDL_GetMouseState(&x, &y); glm::vec2 ret; ret.x = x; ret.y = y; return ret; }
	glm::vec2 GetScreenSize() { int x, y; SDL_GetWindowSize(m_window, &x, &y); glm::vec2 ret; ret.x = x; ret.y = y; return ret; }
	SDL_Window* GetWindow() { return m_window; }

	void AddCamera(std::shared_ptr<Entity> _camera) { m_cameras.push_back(_camera); }
	void SetScene(std::shared_ptr<Scene> _scene) { m_scene = _scene; }

	float GetDeltaTime() { return m_deltaTs; }
private:

	void StartSDL();
	float m_lastTime;
	float m_deltaTs;
	bool m_running;
	//std::shared_ptr<FrameBuffer> m_fb;
	std::shared_ptr<Gui> m_gui;
	std::shared_ptr<Keyboard> m_keyboard;
	std::shared_ptr<Resources> m_resources;
	std::shared_ptr<Compositor> m_compositor;
	//std::vector<std::shared_ptr<Entity>> m_entities;
	std::shared_ptr<Scene> m_scene;
	SDL_Window* m_window;
	ALCdevice* device;
	ALCcontext* context;

	bool rebindA;

	// Position of the single point-light in the scene
	glm::vec3 _lightPosition;

	//std::shared_ptr<Entity> m_camera;
	int m_currentCamera;
	std::vector<std::shared_ptr<Entity>> m_cameras;
	std::vector<std::shared_ptr<FrameBuffer>> m_fbs;
	glm::mat4 _viewMatrix;
	glm::mat4 _projMatrix;


};
