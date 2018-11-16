#include "Gui.h"
#include "Core.h"
#include "VertexBuffer.h"
#include "Resources.h"

Gui::Gui()
{
}

void Gui::Init(std::shared_ptr<Core> _c)
{
	m_core = _c;
	m_shader = _c->GetResources()->Load<Shader>("GuiShader");
	m_shader->LoadShaders("guiVert.txt", "guiFrag.txt");
	m_shader->AddUniform("in_Model");
	m_shader->AddUniform("in_Projection");
	m_shader->AddUniform("in_Texture");
	m_shader->AddUniform("in_FrameInfo");

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

	red = std::make_shared<VertexBuffer>();
	red->Add(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	red->Add(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	red->Add(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));

	red->Add(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
	red->Add(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	red->Add(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	
	green = std::make_shared<VertexBuffer>();
	green->Add(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
	green->Add(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
	green->Add(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));

	green->Add(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
	green->Add(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
	green->Add(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));

	blue = std::make_shared<VertexBuffer>();
	blue->Add(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
	blue->Add(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
	blue->Add(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));

	blue->Add(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
	blue->Add(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
	blue->Add(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));


	m_shape = _c->GetResources()->Load<VertexArray>("Square");
		//std::make_shared<VertexArray>();
	m_shape->SetBuffer(IN_POSITION, positions);
	m_shape->SetBuffer(IN_COLOUR, red);
	m_shape->SetBuffer(IN_UV, uv);

	m_frameInfo.x = 1.0f;
	m_frameInfo.y = 1.0f;
	m_frameInfo.z = 4.0f;
	m_frameInfo.w = 1.0f;
}

Gui::~Gui()
{

}

bool Gui::Button(glm::vec4 _pos, std::string _label)
{
	glUseProgram(m_shader->GetShader());

	glm::vec4 screenPos;
	screenPos.x = (1+_pos.x) * (m_core.lock()->GetScreenSize().x /2);
	if (_pos.y > 0)
	{
		screenPos.y = (_pos.y) * (m_core.lock()->GetScreenSize().y / 2);
	}
	else
	{
		screenPos.y = ((1+_pos.y) * (m_core.lock()->GetScreenSize().y / 2)) + (m_core.lock()->GetScreenSize().y / 2);
	}
	screenPos.z = screenPos.x + ((_pos.z / 2) * m_core.lock()->GetScreenSize().x);
	screenPos.w = screenPos.y +((_pos.w / 2) * m_core.lock()->GetScreenSize().y);
	//screenPos.y = screenPos.y - (screenPos.w/2);
	//screenPos.w = screenPos.y + (screenPos.w / 2);
	

	if (Intersect(screenPos, m_core.lock()->GetMouseLocation()))
	{
		if (m_core.lock()->GetKeyboard()->Input(A_BUTTON))
		{
			m_shape->SetBuffer(IN_COLOUR, green);
			glActiveTexture(GL_TEXTURE0);
			//glUniform1i(_shaderTex1SamplerLocation, 0);
			glUniform1i(m_shader->GetUniformLocation("in_Texture"), 0);
			glBindTexture(GL_TEXTURE_2D, pressed);

		}
		else
		{
			m_shape->SetBuffer(IN_COLOUR, blue);
			glActiveTexture(GL_TEXTURE0);
			glUniform1i(m_shader->GetUniformLocation("in_Texture"), 0);
			glBindTexture(GL_TEXTURE_2D, highlight);

		}
	}
	else
	{
		m_shape->SetBuffer(IN_COLOUR, red);
		glActiveTexture(GL_TEXTURE0);
		glUniform1i(m_shader->GetUniformLocation("in_Texture"), 0);
		glBindTexture(GL_TEXTURE_2D, texture);
	}

	///texture

	//Update the projection matrix
	m_shader->SetUniform(m_shader->GetUniformLocation("in_Proj"), m_core.lock()->GetPM());
	//update the model matrix;
	glm::mat4 modelmat = glm::mat4(1.0f);
	modelmat = glm::translate(modelmat, glm::vec3(_pos.x, _pos.y, 0));
	modelmat = glm::scale(modelmat, glm::vec3(_pos.z, _pos.w, 1));
	//modelmat = glm::scale(modelmat, glm::vec3(1, 1, 1));
	//SetUniform(_shaderModelMatLocation, modelmat);
	m_shader->SetUniform(m_shader->GetUniformLocation("in_Model"), modelmat);
	m_shader->SetUniform(m_shader->GetUniformLocation("in_FrameInfo"), m_frameInfo);

	glBindVertexArray(m_shape->GetId());

	//update texture coordinates

	// Tell OpenGL to draw it
	// Must specify the type of geometry to draw and the number of vertices
	glDrawArrays(GL_TRIANGLES, 0, m_shape->GetVertexCount());

	// Unbind VAO
	glBindVertexArray(0);
	///

	if (Intersect(screenPos, m_core.lock()->GetMouseLocation()))
	{
		if (m_core.lock()->GetKeyboard()->Input(A_BUTTON))
		{
			return true;
		}
	}

	return false;
}

glm::vec4 Gui::GetPos(glm::vec4 _pos)
{
	glm::vec4 screenPos;
	screenPos.x = (_pos.x / (m_core.lock()->GetScreenSize().x / 2)) - 1;// = (1 + _pos.x);
	screenPos.y = (_pos.y / (m_core.lock()->GetScreenSize().y / 2)) - 1;

	screenPos.z = ((_pos.z * 2) / m_core.lock()->GetScreenSize().x);
	screenPos.w = ((_pos.w * 2) / m_core.lock()->GetScreenSize().x);

	return screenPos;
}

void Gui::Sprite(glm::vec4 _pos)
{
	glUseProgram(m_shader->GetShader());

	glm::vec4 screenPos;
	screenPos.x = (1 + _pos.x) * (m_core.lock()->GetScreenSize().x / 2);
	if (_pos.y > 0)
	{
		screenPos.y = (_pos.y) * (m_core.lock()->GetScreenSize().y / 2);
	}
	else
	{
		screenPos.y = ((1 + _pos.y) * (m_core.lock()->GetScreenSize().y / 2)) + (m_core.lock()->GetScreenSize().y / 2);
	}
	screenPos.z = screenPos.x + ((_pos.z / 2) * m_core.lock()->GetScreenSize().x);
	screenPos.w = screenPos.y + ((_pos.w / 2) * m_core.lock()->GetScreenSize().y);


	m_shape->SetBuffer(IN_COLOUR, red);
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(m_shader->GetUniformLocation("in_Texture"), 0);
	glBindTexture(GL_TEXTURE_2D, texture);
	

	///texture

	//Update the projection matrix
	m_shader->SetUniform(m_shader->GetUniformLocation("in_Proj"), m_core.lock()->GetPM());
	//update the model matrix;
	glm::mat4 modelmat = glm::mat4(1.0f);
	modelmat = glm::translate(modelmat, glm::vec3(_pos.x, _pos.y, 0));
	modelmat = glm::scale(modelmat, glm::vec3(_pos.z, _pos.w, 1));
	m_shader->SetUniform(m_shader->GetUniformLocation("in_Model"), modelmat);

	/*
	m_frameInfo.x = 1.0f;
	m_frameInfo.y = 1.0f;
	m_frameInfo.z = 4.0f;
	m_frameInfo.w = 1.0f;
	*/
	//update texture coordinates
	m_shader->SetUniform(m_shader->GetUniformLocation("in_FrameInfo"), m_frameInfo);

	glBindVertexArray(m_shape->GetId());

	// Tell OpenGL to draw it
	// Must specify the type of geometry to draw and the number of vertices
	glDrawArrays(GL_TRIANGLES, 0, m_shape->GetVertexCount());

	// Unbind VAO
	glBindVertexArray(0);
	///
}

bool Gui::Intersect(glm::vec4 _pos, glm::vec2 _mouse)
{
	if (_mouse.x > _pos.x && _mouse.x < _pos.z)// && _mouse.y > _pos.y && _mouse.y < _pos.w)
	{
		if(_mouse.y < _pos.y && _mouse.y > (_pos.w- _pos.y))
		return true;
	}
	return false;
}

