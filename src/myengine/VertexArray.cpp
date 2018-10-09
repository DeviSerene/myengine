#include "VertexArray.h"
#include "VertexBuffer.h"

VertexArray::VertexArray()
{
	m_modified = false;
	//generate a vertex array at id
	glGenVertexArrays(1, &m_id);
}


void VertexArray::SetBuffer(VAType _type, std::weak_ptr<VertexBuffer> _vertexBuffer)
{
	switch (_type)
	{
	case IN_POSITION:
		m_buffers[0] = _vertexBuffer.lock();
		break;
	case IN_COLOUR:
		m_buffers[1] = _vertexBuffer.lock();
		break;
	default:
		break;
	}

	//data was modified
	m_modified = true;
}


int VertexArray::GetVertexCount() 
{ 
	//we need to find the number of vertixes in this object
	//the data size in the vbo includes (x,y,z), if we just count all the xs, then we have the number of vertixes
	//if we had 3 vertexes, then we would have 9 pieces of data (xyz[1],xyz[2],xyz[3])
	//so we need to divide that 9 by the number of parts in one vertex!
	if (m_buffers[0])
		return m_buffers[0]->GetDataSize() / m_buffers[0]->GetComponents(); //the datasize (all xyz,etc) / the number of parts (xyz,etc)
	else
		return 0;
}

GLuint VertexArray::GetId()
{
	if (m_modified)
	{
		glBindVertexArray(m_id);

		for (int i = 0; i < 2; i++)
		{
			if (m_buffers[i]) //was something defined here?
			{
				glBindBuffer(GL_ARRAY_BUFFER, m_buffers[i]->GetId()); //bind the buffer

				glVertexAttribPointer(i, m_buffers[i]->GetComponents(), GL_FLOAT, GL_FALSE,
					m_buffers[i]->GetComponents() * sizeof(GLfloat), (void *)0);
				//point to the data!

				glEnableVertexAttribArray(i); //enable the pointer to be used
			}
			else
			{
				glDisableVertexAttribArray(i); //it's not here so we shouldn't use it!
			}
		}

		//unbind
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		m_modified = false; //the data has been bound so no need to redo this unless it is modified again
	}

	return m_id;
}