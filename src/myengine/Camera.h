#pragma once
#include "Component.h" //inherits from component (as it is something that can be slot into an entity)
#include <memory>
#include <iostream>
#include <GLM/glm.hpp>
#include <GL/glew.h>
#include <GLM/gtc/matrix_transform.hpp>
#include "Transform.h"
#include "FrameBuffer.h"
#include "PostProcess.h"

/*!
Camera is a Component that can be added to GameObjects (Entities).
The camera does not use the Transform component and instead has its own position data.
The camera has a FrameBuffer, which is what it draws to.
*/

class Camera : public Component
{
public:
	Camera();
	~Camera();

	void OnTick();
	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjMatrix();
	glm::vec3 GetCameraPos() {return cameraPos;}
	void SetPos(glm::vec3 _cameraPos) { cameraPos = _cameraPos; }
	std::shared_ptr<FrameBuffer> GetFrameBuffer() { return m_fb; }
	void PostDraw() { m_displayTexture = m_fb->GetTexture(); }
	GLuint GetTexture() { return m_displayTexture; }
	void SetTexture(GLuint _tex) { m_displayTexture = _tex; }
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
	GLuint m_displayTexture;
	std::shared_ptr<FrameBuffer> m_fb;
};

