#pragma once
#include "Component.h" //inherits from component (as it is something that can be slot into an entity)
#include <memory>
#include <iostream>
#include <GLM/glm.hpp>
#include <GL/glew.h>
#include <GLM/gtc/matrix_transform.hpp>
#include "Texture.h"
#include <vector>

/*!
//this component is for displaying a 3D object on screen
//to do that, we need a VAO (organised information about the 3D object, like where the vertex positions, normals, texture coords...)
//Upload positions of triangle to GPU (VBO)
//Organise that data on the GPU(VAO)
//we also neeed to know what shader(s) to use when we want to display them
*/
class Mesh; //forward declaration, #include them in the .cpp
class Material;

class MeshRenderer : public Component
{
public:
	MeshRenderer();
	MeshRenderer(std::shared_ptr<Mesh> _mesh);
	MeshRenderer(std::shared_ptr<Mesh> _mesh, std::shared_ptr<Texture> _texture);
	void OnInit(); //this will override the Components
	void OnDisplay();
	glm::mat4 GetModelMatrix() { return m_modelMatrix; }
	void SetMesh(std::shared_ptr<Mesh> _mesh);
	std::vector<glm::vec3> GetTriangles();
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
	bool mesh;
//	std::shared_ptr<ShaderProgram> m_shader;

};
