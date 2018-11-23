#pragma once
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "Mesh.h"

class Collisions
{
public:
	static bool TriangleCollision(glm::vec3 a1, glm::vec3 b1, glm::vec3 c1, glm::vec3 a2, glm::vec3 b2, glm::vec3 c2);

	static bool MeshCollision(std::vector<glm::vec3> _mesh, std::vector<glm::vec3> _mesh2);

	static bool BoxCollision(glm::vec3 _box1Pos, glm::vec3 _box1Size, glm::vec3 _box2Pos, glm::vec3 _box2Size);
};