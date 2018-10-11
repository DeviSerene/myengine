#pragma once
#include <memory>
#include <vector>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>

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

	glm::vec3 GetCamera() { return _cameraPosition; }
	glm::mat4 GetVM() { return _viewMatrix; }
	glm::mat4 GetPM() { return _projMatrix; }
private:

	void StartSDL();

	bool m_running;
	std::vector<std::shared_ptr<Entity>> m_entities;
	SDL_Window* m_window;

	// This matrix represents the camera's position and orientation
	glm::mat4 _viewMatrix;

	// This matrix is like the camera's lens
	glm::mat4 _projMatrix;

	// Current rotation information about the camera
	float _cameraAngleX, _cameraAngleY, _cameraPanX, _cameraPanY, _cameraPanZ;

	// Position of the single point-light in the scene
	glm::vec3 _lightPosition;
	glm::vec3 _cameraPosition;
};
