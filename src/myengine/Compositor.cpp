#include "Compositor.h"
#include "Core.h"
#include "VertexBuffer.h"
#include "Resources.h"

Compositor::Compositor(std::shared_ptr<Core> _c)
{
	m_x = 800;
	m_y = 600;
	Creation();
	m_core = _c;
	m_shape = _c->GetResources()->Load<VertexArray>("Square");

	m_shader = _c->GetResources()->Load<Shader>("CompositorShader");
	m_shader->LoadShaders("CompVert.txt", "CompFrag.txt");
	m_shader->AddUniform("in_Model");
	m_shader->AddUniform("in_Projection");
	m_shader->AddUniform("in_FrameOne");
	m_shader->AddUniform("in_FrameTwo");
	m_shader->AddUniform("in_ScreenSize");
}

Compositor::~Compositor()
{

}

void Compositor::Composition(std::vector<std::shared_ptr<FrameBuffer>> _fbs, COMPOSITION_TYPE _ct)
{
	glUseProgram(m_shader->GetShader());
	//Textures
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(m_shader->GetUniformLocation("in_FrameOne"), 0);
	glBindTexture(GL_TEXTURE_2D, _fbs[0]->GetTexture());
	//
	glActiveTexture(GL_TEXTURE1);
	glUniform1i(m_shader->GetUniformLocation("in_FrameTwo"), 1);
	glBindTexture(GL_TEXTURE_2D, _fbs[1]->GetTexture());

	glm::mat4 modelmat = glm::mat4(1.0f);
	modelmat = glm::translate(modelmat, glm::vec3(-1, -1, 0));
	modelmat = glm::scale(modelmat, glm::vec3(2, 2, 1));

	m_shader->SetUniform(m_shader->GetUniformLocation("in_Projection"), m_core.lock()->GetPM());
	m_shader->SetUniform(m_shader->GetUniformLocation("in_Model"), modelmat);
	m_shader->SetUniform(m_shader->GetUniformLocation("in_ScreenSize"), m_core.lock()->GetScreenSize()); 
	//DRAW
	glBindVertexArray(m_shape->GetId());
	glDrawArrays(GL_TRIANGLES, 0, m_shape->GetVertexCount());
	glBindVertexArray(0);
	///
}

void Compositor::Update(int x, int y)
{
	if (m_x != x || m_y != y)
	{
		m_x = x; 
		m_y = y;
		/////////
		Creation();
	}
}

void Compositor::Creation()
{

	glGenFramebuffers(1, &m_buffer);
	glBindFramebuffer(GL_FRAMEBUFFER, m_buffer);
	glGenTextures(1, &m_texture);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, m_texture);

	// Give an empty image to OpenGL ( the last "0" )
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_x, m_y, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
	// Poor filtering. Needed !
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenRenderbuffers(1, &m_depth);
	glBindRenderbuffer(GL_RENDERBUFFER, m_depth);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, m_x, m_y);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depth);

	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_texture, 0);

	// Set the list of draw buffers.
	GLenum DrawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers

}