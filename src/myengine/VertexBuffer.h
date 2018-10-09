#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>

class VertexBuffer
{
public:
	VertexBuffer();
	void Add(glm::vec3 value);
	void Add(glm::vec4 value);
	int GetComponents() { return m_components; }
	int GetDataSize() { return m_data.size(); }
	GLuint GetId();

private:
	GLuint m_id;
	int m_components;
	std::vector<GLfloat> m_data;
	bool m_dirty;
};