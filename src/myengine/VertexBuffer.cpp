#include "VertexBuffer.h"

VertexBuffer::VertexBuffer()
{
	m_components = 0;
	m_dirty = false;

	glGenBuffers(1, &m_id);
}

void VertexBuffer::Add(glm::vec3 value)
{
	m_components = 3;

	m_data.push_back(value.x);
	m_data.push_back(value.y);
	m_data.push_back(value.z);
	m_dirty = true;
}

void VertexBuffer::Add(glm::vec4 value)
{
	m_components = 4;

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