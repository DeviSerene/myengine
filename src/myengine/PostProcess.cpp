#include "PostProcess.h"
#include "Core.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Shader.h"
#include "Resource.h"
#include "Resources.h"

void PostProcess::LoadShader(std::shared_ptr<Core> _core, std::string _name, std::string _vert, std::string _frag) 
{
	m_name = _name;
	m_shader = _core->GetResources()->Load<Shader>(_name);
	m_shader->LoadShaders(_vert, _frag);
	m_fb = std::shared_ptr<FrameBuffer>(new FrameBuffer(false));
	m_shape = _core->GetResources()->Load<VertexArray>("Square");
	/*m_shape = _core->GetResources()->Load<VertexArray>("SquarePP");

	std::shared_ptr<VertexBuffer> positions = std::make_shared<VertexBuffer>();
	positions->Add(glm::vec3(0.0f, 0.0f, 0.0f));
	positions->Add(glm::vec3(1.0f, 1.0f, 0.0f));
	positions->Add(glm::vec3(0.0f, 1.0f, 0.0f));

	positions->Add(glm::vec3(1.0f, 1.0f, 0.0f));
	positions->Add(glm::vec3(0.0f, 0.0f, 0.0f));
	positions->Add(glm::vec3(1.0f, 0.0f, 0.0f));

	std::shared_ptr<VertexBuffer> uv = std::make_shared<VertexBuffer>();
	uv->Add(glm::vec2(0.0f, 0.0f));
	uv->Add(glm::vec2(1.0f, 1.0f));
	uv->Add(glm::vec2(0.0f, 1.0f));
	uv->Add(glm::vec2(1.0f, 1.0f));
	uv->Add(glm::vec2(0.0f, 0.0f));
	uv->Add(glm::vec2(1.0f, 0.0f));

	std::shared_ptr<VertexBuffer> red = std::make_shared<VertexBuffer>();
	red->Add(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	red->Add(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	red->Add(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));

	red->Add(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
	red->Add(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	red->Add(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));

	m_shape->SetBuffer(IN_POSITION, positions);
	m_shape->SetBuffer(IN_COLOUR, red);
	m_shape->SetBuffer(IN_UV, uv);
	*/
}

void PostProcess::Draw(GLuint _oldTexture)
{
	SetTexture("in_Texture", _oldTexture, 0);

	glBindFramebuffer(GL_FRAMEBUFFER, m_fb->GetBuffer());
	glClearColor(0.0f, 0.0f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);

	glUseProgram(m_shader->GetShader());
	glBindVertexArray(m_shape->GetId());
	glDrawArrays(GL_TRIANGLES, 0, m_shape->GetVertexCount());
	glBindVertexArray(0);
}

void PostProcess::SetEffect(std::string _id, glm::mat4 _variable)
{ 
	glUseProgram(m_shader->GetShader()); 
	m_shader->AddUniform(_id); 
	m_shader->SetUniform(m_shader->GetUniformLocation(_id), _variable); 
}

void PostProcess::SetEffect(std::string _id, glm::vec4 _variable)
{
	glUseProgram(m_shader->GetShader());
	m_shader->AddUniform(_id);
	m_shader->SetUniform(m_shader->GetUniformLocation(_id), _variable);
}
void PostProcess::SetEffect(std::string _id, glm::vec3 _variable)
{
	glUseProgram(m_shader->GetShader());
	m_shader->AddUniform(_id);
	m_shader->SetUniform(m_shader->GetUniformLocation(_id), _variable);
}
void PostProcess::SetEffect(std::string _id, glm::vec2 _variable)
{
	glUseProgram(m_shader->GetShader());
	m_shader->AddUniform(_id);
	m_shader->SetUniform(m_shader->GetUniformLocation(_id), _variable);
}
void PostProcess::SetEffect(std::string _id, bool _variable)
{
	glUseProgram(m_shader->GetShader());
	m_shader->AddUniform(_id);
	m_shader->SetUniform(m_shader->GetUniformLocation(_id), _variable);
}

void PostProcess::SetTexture(std::string _uniform, GLuint _texture, int _textureNo)
{
	glUseProgram(m_shader->GetShader());
	m_shader->SetTexture(_uniform, _texture, _textureNo);
}

void PostProcess::AddEffect(std::string _id)
{
	glUseProgram(m_shader->GetShader());
	m_shader->AddUniform(_id);
}