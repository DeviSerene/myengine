#pragma once
#include "Component.h" //inherits from component (as it is something that can be slot into an entity)
#include <memory>
#include <iostream>
#include <GLM/glm.hpp>
#include <GL/glew.h>
#include <GLM/gtc/matrix_transform.hpp>
#include "Transform.h"

class Camera : public Component
{
public:
	Camera();
	~Camera();

	void OnTick();

	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjMatrix();

private:
	// This matrix represents the camera's position and orientation
	glm::mat4 _viewMatrix;
	// This matrix is like the camera's lens
	glm::mat4 _projMatrix;
	///
	glm::vec3 cameraPos;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;
	glm::vec3 cameraTarget;
	glm::vec3 cameraDirection;
	glm::vec3 cameraRight;
	float pitch = 0, yaw = -60;
};

