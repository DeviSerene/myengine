
#ifndef __MESH__
#define __MESH__

#include <GLM/glm.hpp>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <string>
#include <math.h>
#include <vector>
#include "resource.h"

// For loading a mesh from OBJ file and keeping a reference for it
class Mesh : public Resource
{
public:

	Mesh();
	~Mesh();
	static std::shared_ptr<Mesh> Load(std::string filename);
	// OBJ file must be triangulated
	void LoadOBJ(std::string filename);

	// Draws the mesh - must have shaders applied for this to display!
	void Draw();

	std::string GetName() { return m_fileName; }
	std::vector<glm::vec3> GetPosData() { return orderedPositionData; }
protected:

	// OpenGL Vertex Array Object
	GLuint _VAO;

	// Number of vertices in the mesh
	unsigned int _numVertices;
	std::string m_fileName;
	std::vector<glm::vec3> orderedPositionData;

};


#endif
