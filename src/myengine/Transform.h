#pragma once
#include "Component.h" //inherits from component (as it is something that can be slot into an entity)
#include <memory>
#include <iostream>
#include <GLM/glm.hpp>
#include <GL/glew.h>
#include <GLM/gtc/matrix_transform.hpp>

class Transform : public Component
{
public:
	Transform();
	Transform(glm::vec3 _p, glm::vec3 _r, glm::vec3 _s);
	void OnInit(); //this will override the Components
	void OnTick();

	glm::vec3 GetPosition();
	glm::vec3 GetRotation();
	glm::vec3 GetScale();

	glm::vec3 GetFront() { return m_front; }
	glm::vec3 GetUp() { return m_up; }
	glm::vec3 GetRight() { return m_right; }

private:
	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;

	glm::vec3 m_front;
	glm::vec3 m_up;
	glm::vec3 m_right;

};