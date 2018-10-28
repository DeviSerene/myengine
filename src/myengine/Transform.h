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
	Transform() {m_position.x = 1;m_position.y = 1;m_position.z = 1;m_rotation.x = 0; m_rotation.y = 0;m_rotation.z = 0; m_scale.x = 1;m_scale.y = 1;m_scale.z = 1;}
	Transform(glm::vec3 _p, glm::vec3 _r, glm::vec3 _s) {m_position = _p;m_rotation = _r;m_scale = _s;}
	void OnInit(); //this will override the Components
	void OnTick() {}// m_rotation.x += 0.01f; }

	glm::vec3 GetPosition() { return m_position; }
	glm::vec3 GetRotation() { return m_rotation; }
	glm::vec3 GetScale() { return m_scale; }

private:
	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;
};