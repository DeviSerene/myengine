#include "MeshRenderer.h"
#include "ShaderProgram.h"
#include "Material.h"
#include "Mesh.h"
#include "Environment.h"
#include "Keyboard.h"
#include "Core.h"
#include "Entity.h"


void MeshRenderer::OnInit()
{
	/*
	std::shared_ptr<VertexBuffer> positions = std::make_shared<VertexBuffer>();
	positions->Add(glm::vec3(0.0f, 0.5f, 0.0f));
	positions->Add(glm::vec3(-0.5f, -0.5f, 0.0f));
	positions->Add(glm::vec3(0.5f, -0.5f, 0.0f));

	std::shared_ptr<VertexBuffer> colors = std::make_shared<VertexBuffer>();
	colors->Add(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	colors->Add(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	colors->Add(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	

	m_shape = std::make_shared<VertexArray>();
	m_shape->SetBuffer(IN_POSITION, positions);
	m_shape->SetBuffer(IN_COLOUR, colors);
	*/

	m_modelMatrix = glm::mat4(1.0f);
	m_invModelMatrix = glm::mat4(1.0f);

	m_cam = std::shared_ptr<glm::vec3>(new glm::vec3(0.0f, 0.0f, 0.0f));

	m_mesh = std::shared_ptr <Mesh>(new Mesh());
	m_mesh->LoadOBJ("Card.obj");
	m_mat = std::shared_ptr<Material>(new Material());
	m_mat->SetTexture("Card.bmp");
	m_mat->SetNormal("Card_normal.bmp");
	m_mat->SetHeightMap("Card_height.bmp");
	m_mat->LoadShaders("VertShader.txt", "FragShader.txt");
	m_mat->SetMatrices(m_modelMatrix, m_invModelMatrix, glm::mat4(1.0f), glm::mat4(1.0f));
	m_mat->SetLightPosition({ 1.0f, 0.0f, 0.0f });

	//m_shader = std::make_shared<ShaderProgram>("resources/shaders/simple.vert", "resources/shaders/simple.frag");
}

void MeshRenderer::OnDisplay()
{
	m_modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0,0,0));
	//m_modelMatrix = glm::rotate(m_modelMatrix, _rotation.y, glm::vec3(0, 1, 0));
	//m_modelMatrix = glm::rotate(m_modelMatrix, _rotation.z, glm::vec3(0, 0, 1));
	//m_modelMatrix = glm::rotate(m_modelMatrix, _rotation.x, glm::vec3(1, 0, 0));
	//m_modelMatrix = glm::scale(m_modelMatrix, 1);

	m_invModelMatrix = glm::rotate(glm::mat4(1.0f), -0.0f, glm::vec3(0, 1, 0));
	m_mat->SetMatrices(m_modelMatrix, m_invModelMatrix, GetCore()->GetVM(), GetCore()->GetPM());
	m_mat->SetCameraPosition(&GetCore()->GetCamera());
	// This activates the shader
	m_mat->Apply();
	m_mesh->Draw();
}
