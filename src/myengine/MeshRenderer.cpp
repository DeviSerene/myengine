#include "MeshRenderer.h"
#include "ShaderProgram.h"
#include "Material.h"
#include "Mesh.h"
#include "Environment.h"
#include "Keyboard.h"
#include "Core.h"
#include "Resources.h"
#include "Entity.h"
#include "Transform.h"


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

	m_mesh = GetCore()->GetResources()->Load<Mesh>("Card.obj"); //std::shared_ptr <Mesh>(new Mesh());
	m_texture = GetCore()->GetResources()->Load<Texture>("Card.bmp");
	m_normal = GetCore()->GetResources()->Load<Texture>("Card_normal.bmp");
	m_height = GetCore()->GetResources()->Load<Texture>("Card_height.bmp");
	//m_mesh->LoadOBJ("Card.obj");
	//m_db = std::shared_ptr<DepthBuffer>(new DepthBuffer());
	//m_db->LoadShaders("depthVertShader.txt", "depthFragShader.txt");
	m_mat = GetCore()->GetResources()->Create<Material>();
	//m_mat->SetTexture("Card.bmp");
	//m_mat->SetNormal("Card_normal.bmp");
	//m_mat->SetHeightMap("Card_height.bmp");
	m_mat->LoadShaders("VertShader.txt", "FragShader.txt");
	m_mat->SetMatrices(m_modelMatrix, m_invModelMatrix, glm::mat4(1.0f), glm::mat4(1.0f));
	m_mat->SetLightPosition({ 1.0f, 0.0f, 0.0f });
	//m_shader1 = std::make_shared<ShaderProgram>("resources/shaders/VertShader.txt", "resources/shaders/FragShader.txt");
	
	//m_shader1 = std::make_shared<ShaderProgram>("VertShader.txt", "FragShader.txt");
	//m_shader1->SetTexture("Card.bmp");
	//m_shader1->SetNormal("Card_normal.bmp");
	//m_shader1->SetHeightMap("Card_height.bmp");
	//m_shader1->SetUniform("modelMat", m_modelMatrix);
	//m_shader1->SetUniform("invModelMat", m_invModelMatrix);
}

void MeshRenderer::OnDisplay()
{
	std::shared_ptr<Transform> myTransform = GetEntity()->GetComponent<Transform>();
	if (myTransform)
	{
		
		m_modelMatrix = glm::translate(glm::mat4(1.0f), myTransform->GetPosition());
		m_modelMatrix = glm::rotate(m_modelMatrix, myTransform->GetRotation().y, glm::vec3(0, 1, 0));
		m_modelMatrix = glm::rotate(m_modelMatrix, myTransform->GetRotation().z, glm::vec3(0, 0, 1));
		m_modelMatrix = glm::rotate(m_modelMatrix, myTransform->GetRotation().x, glm::vec3(1, 0, 0));
		m_modelMatrix = glm::scale(m_modelMatrix, myTransform->GetScale());
		
		m_invModelMatrix = glm::rotate(glm::mat4(1.0f), -0.0f, glm::vec3(0, 1, 0));
		
		/*
		m_shader1->SetUniform("modelMat", m_modelMatrix);
		m_shader1->SetUniform("invModelMat", m_invModelMatrix);
		m_shader1->SetUniform("viewMat", GetCore()->GetVM());
		m_shader1->SetUniform("projMat", GetCore()->GetPM());

		m_shader1->Apply();
		m_mesh->Draw();
		*/
		//needs a transform to proceed
		m_mat->SetMatrices(m_modelMatrix, m_invModelMatrix, GetCore()->GetVM(), GetCore()->GetPM());
		m_mat->SetCameraPosition(&GetCore()->GetCamera());
		// This activates the shader
		m_mat->SetTex(0, m_texture->GetTexture());
		m_mat->SetTex(1, m_normal->GetTexture());
		m_mat->SetTex(2, m_height->GetTexture());
		m_mat->Apply();
		//m_db->SetMVP({ 0.5f,2,2 });
		m_mesh->Draw();
	}
	else
	{
		//needs a transform to proceed
		/*m_shader1->SetUniform("modelMat", m_modelMatrix);
		m_shader1->SetUniform("invModelMat", m_invModelMatrix);
		m_shader1->SetUniform("viewMat", GetCore()->GetVM());
		m_shader1->SetUniform("projMat", GetCore()->GetPM());*/
		// This activates the shader
		m_mat->Apply();
		m_mesh->Draw();
		//m_shader1->Apply();
		//m_mesh->Draw();
	}
	

}
