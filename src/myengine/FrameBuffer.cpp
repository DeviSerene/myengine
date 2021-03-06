#include "FrameBuffer.h"

FrameBuffer::FrameBuffer(bool _depth)
{
	m_x = 800;
	m_y = 600; 
	m_useD = _depth;

	Create();
}

FrameBuffer::~FrameBuffer()
{
	glDeleteTextures(1, &m_texture);
	glDeleteRenderbuffers(1, &m_depth);
	glDeleteFramebuffers(1, &m_buffer);
}

void FrameBuffer::Update(int x, int y)
{
	if (m_x != x || m_y != y)
	{
		m_x = x; 
		m_y = y;
		/////////
		glDeleteTextures(1, &m_texture);
		glDeleteRenderbuffers(1, &m_depth);
		glDeleteFramebuffers(1, &m_buffer);
		Create();
	}
}

void FrameBuffer::Create()
{
	glGenFramebuffers(1, &m_buffer);
	glBindFramebuffer(GL_FRAMEBUFFER, m_buffer);
	glGenTextures(1, &m_texture);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, m_texture);

	// Give an empty image to OpenGL ( the last "0" )
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_x, m_y, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, 1024, 768, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	// Poor filtering. Needed !
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glBindTexture(GL_TEXTURE_2D, 0);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_texture, 0);
	if (m_useD)
	{
		glGenRenderbuffers(1, &m_depth);
		glBindRenderbuffer(GL_RENDERBUFFER, m_depth);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, m_x, m_y);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depth);

	}
	// Set the list of draw buffers.
	GLenum DrawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers

}
