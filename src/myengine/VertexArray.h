//a vertexArray organises the data stored on the vertex buffer in a way for the gpu
//this way, we can name buffers like "_inPosition" and give the location, same with _inColours or _texCoords etc
//this makes it easy to use in the shaders!
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <memory>
//instead of #include "VertexBuffer", we can forward declare it and that leaves less chance for things to go wrong

//A VAO is a collection of pointers to the data in the VBOs

enum VAType
{
	IN_POSITION, IN_COLOUR
};

class VertexBuffer;

class VertexArray
{
public:

	VertexArray();
	void SetBuffer(VAType _type, std::weak_ptr<VertexBuffer> _vertexBuffer);
	int GetVertexCount();
	GLuint GetId();

private:

	GLuint m_id;
	bool m_modified;
	std::shared_ptr<VertexBuffer> m_buffers[2];
};