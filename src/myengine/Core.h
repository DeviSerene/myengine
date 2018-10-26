#pragma once
#include <iostream>
#include <exception>
#include "MyEngineException.h"
#include <string>
#include <memory>
#include <vector>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <AL/al.h>
#include <AL/alc.h>
#include "Gui.h"

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
	std::shared_ptr<Entity> AddEntity();

	std::shared_ptr<Gui> GetGui() { return m_gui; }
	std::shared_ptr<Resources> GetResources() { return m_resources; }
	glm::vec3 GetCamera() { return _cameraPosition; }
	glm::mat4 GetVM() { return _viewMatrix; }
	glm::mat4 GetPM() { return _projMatrix; }

	float GetDeltaTime() { return m_deltaTs; }
private:

	void StartSDL();
	float m_lastTime;
	float m_deltaTs;
	bool m_running;
	std::shared_ptr<Gui> m_gui;
	std::shared_ptr<Resources> m_resources;
	std::vector<std::shared_ptr<Entity>> m_entities;
	SDL_Window* m_window;
	ALCdevice* device;
	ALCcontext* context;



	// This matrix represents the camera's position and orientation
	glm::mat4 _viewMatrix;

	// This matrix is like the camera's lens
	glm::mat4 _projMatrix;

	// Current rotation information about the camera
	float _cameraAngleX, _cameraAngleY;

	// Position of the single point-light in the scene
	glm::vec3 _lightPosition;
	glm::vec3 _cameraPosition;

	

};
