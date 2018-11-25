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
#include "Collisions.h"

class Entity;
class Resources;
/*!
Core is the heart of the engine. It contains the loaded scenes, is an access point to get to Resources, Gui, etc and holds the game loop.
Loop: ChangeScenes, OnTick, OnDraw, OnPostProcess, OnGui
*/
class Core : public std::enable_shared_from_this<Core>
{
public:
	Core();
	~Core();

	static std::shared_ptr<Core> init();
	void Start();
	void Stop() { m_running = false; }

	///Getters
	std::shared_ptr<Keyboard> GetKeyboard() { return m_keyboard; }
	std::shared_ptr<Gui> GetGui() { return m_gui; }
	std::shared_ptr<Resources> GetResources() { return m_resources; }
	std::shared_ptr<Scene> GetScene() { return m_scenes[m_scene]; }
	glm::vec3 GetCamera();
	glm::mat4 GetVM() { return _viewMatrix; }
	glm::mat4 GetPM() { return _projMatrix; }
	glm::vec2 GetMouseLocation() { int x, y; SDL_GetMouseState(&x, &y); glm::vec2 ret; ret.x = x; ret.y = y; return ret; }
	glm::vec2 GetScreenSize() { int x, y; SDL_GetWindowSize(m_window, &x, &y); glm::vec2 ret; ret.x = x; ret.y = y; return ret; }
	SDL_Window* GetWindow() { return m_window; }

	///Add Cameras, Change Scenes etc
	void AddCamera(std::shared_ptr<Entity> _camera) { m_cameras.push_back(_camera); }
	void AddScene(std::shared_ptr<Scene> _scene) { m_scenes.push_back(_scene); }
	void SetScene(int _scene) { m_new = _scene; m_changeScene = true; }
	int GetSceneNo() { return m_scene; }

	float GetDeltaTime() { return m_deltaTs; }
private:
	bool m_running;
	//SDL
	void StartSDL();
	SDL_Window* m_window;
	//DeltaTime
	float m_lastTime;
	float m_deltaTs;
	//Features
	std::shared_ptr<Gui> m_gui;
	std::shared_ptr<Keyboard> m_keyboard;
	std::shared_ptr<Resources> m_resources;
	//Scenes
	void ChangeScene(int _scene);
	int m_scene;
	int m_new;
	bool m_changeScene;
	std::vector<std::shared_ptr<Scene>> m_scenes;
	//Audio
	ALCdevice* device;
	ALCcontext* context;


	// Position of the single point-light in the scene
	glm::vec3 _lightPosition;

	//Cameras
	int m_currentCamera;
	std::vector<std::shared_ptr<Entity>> m_cameras;
	//Current Matrices
	glm::mat4 _viewMatrix;
	glm::mat4 _projMatrix;


};
