#pragma once
#include "Component.h" //inherits from component (as it is something that can be slot into an entity)
#include <memory>
#include <iostream>
#include <GLM/glm.hpp>
#include <GL/glew.h>
#include <GLM/gtc/matrix_transform.hpp>
#include "Transform.h"

class Collider : public Component
{
public:
	Collider();
	Collider(glm::vec3 _size);
	~Collider(){}
	glm::vec3 GetSize() { return m_boxSize; }

private:
	glm::vec3 m_boxSize;

};