#include "VertexBuffer.h"

VertexBuffer::VertexBuffer()
{
	m_components = 0;
	m_dirty = false;
	m_id = 0;

	glGenBuffers(1, &m_id);
}

void VertexBuffer::Add(glm::vec2 value)
{
	if (m_components == 0)
	{
		m_components = 2;
	}
	else if (m_components != 2)
	{
		return;
	}

	m_data.push_back(value.x);
	m_data.push_back(value.y);
	m_dirty = true;
}

void VertexBuffer::Add(glm::vec3 value)
{
	if (m_components == 0)
	{
		m_components = 3;
	}
	else if (m_components != 3)
	{
		return;
	}
	
	m_data.push_back(value.x);
	m_data.push_back(value.y);
	m_data.push_back(value.z);
	m_dirty = true;
}

void VertexBuffer::Add(glm::vec4 value)
{
	if (m_components == 0)
	{
		m_components = 4;
	}
	else if (m_components != 4)
	{
		return; //componenets must be kept the same number, else it could try to read data that isn't there and things could go weird
	}

	m_data.push_back(value.x);
	m_data.push_back(value.y);
	m_data.push_back(value.z);
	m_data.push_back(value.w);
	m_dirty = true;
}

GLuint VertexBuffer::GetId()
{
	if (m_dirty)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_id);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * m_data.size(), &m_data.at(0), GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		m_dirty = false;
	}

	return m_id;
}