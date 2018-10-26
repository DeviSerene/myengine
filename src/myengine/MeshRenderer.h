#pragma once
#include "Component.h" //inherits from component (as it is something that can be slot into an entity)
#include <memory>
#include <iostream>
#include <GLM/glm.hpp>
#include <GL/glew.h>
#include <GLM/gtc/matrix_transform.hpp>
#include "ShaderProgram.h"
#include "Texture.h"
//#include "DepthBuffer.h"

//this component is for displaying a 3D object on screen
//to do that, we need a VAO (organised information about the 3D object, like where the vertex positions, normals, texture coords...)
//Upload positions of triangle to GPU (VBO)
//Organise that data on the GPU(VAO)
//we also neeed to know what shader(s) to use when we want to display them
class Mesh; //forward declaration, #include them in the .cpp
class Material;
//class ShaderProgram;

class MeshRenderer : public Component
{
public:
	void OnInit(); //this will override the Components
	void OnDisplay();

private:

	// The actual model geometry
	std::shared_ptr<Mesh> m_mesh;
	// The material contains the shader
	std::shared_ptr<Material> m_mat;
	//std::shared_ptr<DepthBuffer> m_db;
	std::shared_ptr<glm::vec3> m_cam;
	std::shared_ptr<Texture> m_texture;
	std::shared_ptr<Texture> m_normal;
	std::shared_ptr<Texture> m_height;
	//std::shared_ptr <ShaderProgram> m_shader1;
	// Matrix for the position and orientation of the game object
	glm::mat4 m_modelMatrix;
	glm::mat4 m_invModelMatrix;

//	std::shared_ptr<ShaderProgram> m_shader;

};
