#pragma once
#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>

class VertexBuffer
{
public:
	VertexBuffer();
	void Add(glm::vec3 value);
	void Add(glm::vec4 value);

	//Getters
	int GetComponents() { return m_components; }
	int GetDataSize() { return m_data.size(); }
	GLuint GetId(); //this one is a bit more complicated in that we need to bind the buffer data, if it is 'dirty' (has been modified/has new data), before returning the ID

private:
	GLuint m_id;
	int m_components; //are we dealing with vec3s or vec4s? KEEP IT CONSISTENT!
	std::vector<GLfloat> m_data; 
	bool m_dirty; //has the data been modified (via Add())? If so, we need to rebind it
};