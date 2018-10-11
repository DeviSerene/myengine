
#include "Mesh.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>


Mesh::Mesh()
{
	// Initialise stuff here

	_VAO = 0;
	// Creates one VAO
	glGenVertexArrays(1, &_VAO);

	_numVertices = 0;

}

Mesh::~Mesh()
{
	// Clean up stuff here
	glDeleteVertexArrays(1, &_VAO);
}


void Mesh::LoadOBJ(std::string filename)
{
	// Find file
	std::ifstream inputFile(filename);
	m_fileName = filename;

	if (inputFile.is_open())
	{
		// OBJ files can store texture coordinates, positions and normals
		std::vector<glm::vec2> rawUVData;
		std::vector<glm::vec3> rawPositionData;
		std::vector<glm::vec3> rawNormalData;

		std::vector<glm::vec2> orderedUVData;
		std::vector<glm::vec3> orderedNormalData;

		std::vector<glm::vec3> tangentData;
		std::vector<glm::vec3> bitangentData;

		std::string currentLine;

		while (std::getline(inputFile, currentLine))
		{
			std::stringstream currentLineStream(currentLine);
			//std::cout<< currentLine <<std::endl;

			if (!currentLine.substr(0, 2).compare(0, 2, "vt"))
			{
				std::string junk;
				float x, y;
				currentLineStream >> junk >> x >> y;
				rawUVData.push_back(glm::vec2(x, 1.0f - y));
			}
			else if (!currentLine.substr(0, 2).compare(0, 2, "vn"))
			{
				std::string junk;
				float x, y, z;
				currentLineStream >> junk >> x >> y >> z;
				rawNormalData.push_back(glm::vec3(x, y, z));
			}
			else if (!currentLine.substr(0, 2).compare(0, 1, "v"))
			{
				std::string junk;
				float x, y, z;
				currentLineStream >> junk >> x >> y >> z;
				rawPositionData.push_back(glm::vec3(x, y, z));
			}
			else if (!currentLine.substr(0, 2).compare(0, 1, "f"))
			{
				std::string junk;
				std::string verts[4];

				currentLineStream >> junk >> verts[0] >> verts[1] >> verts[2] >> verts[3];

				if (verts[3].empty())
				{
					for (unsigned int i = 0; i < 3; i++)
					{
						std::stringstream currentSection(verts[i]);

						// There is just position data
						unsigned int posID = 0;
						unsigned int uvID = 0;
						unsigned int normID = 0;

						if (verts[i].find('/') == std::string::npos)
						{
							// No texcoords or normals
							currentSection >> posID;
						}
						else if (verts[i].find("//") != std::string::npos)
						{
							// No texcoords
							char junk;
							currentSection >> posID >> junk >> junk >> normID;
						}
						else
						{
							char junk;
							currentSection >> posID >> junk >> uvID >> junk >> normID;
						}

						if (posID > 0)
						{
							orderedPositionData.push_back(rawPositionData[posID - 1]);
							//		std::cout << rawPositionData[posID - 1].x << " " << rawPositionData[posID - 1].y << " " << rawPositionData[posID - 1].z << "\n";
						}
						if (uvID > 0)
						{
							orderedUVData.push_back(rawUVData[uvID - 1]);
						}
						if (normID > 0)
						{
							orderedNormalData.push_back(rawNormalData[normID - 1]);
						}

					}
				}
				else
				{
					std::cerr << "WARNING: This OBJ loader only works with triangles but a quad has been detected. Please triangulate your mesh." << std::endl;
					inputFile.close();
					return;
				}

			}
		}

		inputFile.close();

		_numVertices = orderedPositionData.size();

		if (_numVertices > 0)
		{

			glBindVertexArray(_VAO);

			// Variable for storing a VBO
			GLuint posBuffer = 0;
			// Create a generic 'buffer'
			glGenBuffers(1, &posBuffer);
			// Tell OpenGL that we want to activate the buffer and that it's a VBO
			glBindBuffer(GL_ARRAY_BUFFER, posBuffer);
			// With this buffer active, we can now send our data to OpenGL
			// We need to tell it how much data to send
			// We can also tell OpenGL how we intend to use this buffer - here we say GL_STATIC_DRAW because we're only writing it once
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * _numVertices * 3, &orderedPositionData[0], GL_STATIC_DRAW);

			// This tells OpenGL how we link the vertex data to the shader
			// (We will look at this properly in the lectures)
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(0);

			if (orderedNormalData.size() > 0)
			{
				// Variable for storing a VBO
				GLuint normBuffer = 0;
				// Create a generic 'buffer'
				glGenBuffers(1, &normBuffer);
				// Tell OpenGL that we want to activate the buffer and that it's a VBO
				glBindBuffer(GL_ARRAY_BUFFER, normBuffer);
				// With this buffer active, we can now send our data to OpenGL
				// We need to tell it how much data to send
				// We can also tell OpenGL how we intend to use this buffer - here we say GL_STATIC_DRAW because we're only writing it once
				glBufferData(GL_ARRAY_BUFFER, sizeof(float) * _numVertices * 3, &orderedNormalData[0], GL_STATIC_DRAW);

				// This tells OpenGL how we link the vertex data to the shader
				// (We will look at this properly in the lectures)
				glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
				glEnableVertexAttribArray(1);
			}


			if (orderedUVData.size() > 0)
			{
				// Variable for storing a VBO
				GLuint texBuffer = 0;
				// Create a generic 'buffer'
				glGenBuffers(1, &texBuffer);
				// Tell OpenGL that we want to activate the buffer and that it's a VBO
				glBindBuffer(GL_ARRAY_BUFFER, texBuffer);
				// With this buffer active, we can now send our data to OpenGL
				// We need to tell it how much data to send
				// We can also tell OpenGL how we intend to use this buffer - here we say GL_STATIC_DRAW because we're only writing it once
				glBufferData(GL_ARRAY_BUFFER, sizeof(float) * _numVertices * 2, &orderedUVData[0], GL_STATIC_DRAW);

				// This tells OpenGL how we link the vertex data to the shader
				// (We will look at this properly in the lectures)
				glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
				glEnableVertexAttribArray(2);
			}

			//I have no idea what I'm doing for normal maps, but let's give it a shot:
			if (orderedUVData.size() > 0)
			{
				for (int i = 0; i < orderedPositionData.size(); i += 3)
				{

					// Shortcuts for vertices
					glm::vec3 &v0 = orderedPositionData[i + 0];
					glm::vec3 &v1 = orderedPositionData[i + 1];
					glm::vec3 &v2 = orderedPositionData[i + 2];

					// Shortcuts for UVs
					glm::vec2 &uv0 = orderedUVData[i + 0];
					glm::vec2 &uv1 = orderedUVData[i + 1];
					glm::vec2 &uv2 = orderedUVData[i + 2];

					// Edges of the triangle : postion delta
					glm::vec3 deltaPos1 = v1 - v0;
					glm::vec3 deltaPos2 = v2 - v0;

					// UV delta
					glm::vec2 deltaUV1 = uv1 - uv0;
					glm::vec2 deltaUV2 = uv2 - uv0;

					float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
					glm::vec3 tangent = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y)*r;
					glm::vec3 bitangent = (deltaPos2 * deltaUV1.x - deltaPos1 * deltaUV2.x)*r;

					// Set the same tangent for all three vertices of the triangle. //tangentData.push_back(tangent);
					tangentData.push_back(glm::normalize(tangent - orderedNormalData[i] * glm::dot(orderedNormalData[i], tangent)));
					tangentData.push_back(glm::normalize(tangent - orderedNormalData[i + 1] * glm::dot(orderedNormalData[i + 1], tangent)));
					tangentData.push_back(glm::normalize(tangent - orderedNormalData[i + 2] * glm::dot(orderedNormalData[i + 2], tangent)));

					// Same thing for binormals
					bitangentData.push_back(glm::normalize(bitangent - orderedNormalData[i] * glm::dot(orderedNormalData[i], bitangent)));
					bitangentData.push_back(glm::normalize(bitangent - orderedNormalData[i + 1] * glm::dot(orderedNormalData[i + 1], bitangent)));
					bitangentData.push_back(glm::normalize(bitangent - orderedNormalData[i + 2] * glm::dot(orderedNormalData[i + 2], bitangent)));


				}

				// Variable for storing a VBO
				GLuint tangentBuffer = 0;
				// Create a generic 'buffer'
				glGenBuffers(1, &tangentBuffer);
				// Tell OpenGL that we want to activate the buffer and that it's a VBO
				glBindBuffer(GL_ARRAY_BUFFER, tangentBuffer);
				// With this buffer active, we can now send our data to OpenGL
				// We need to tell it how much data to send
				// We can also tell OpenGL how we intend to use this buffer - here we say GL_STATIC_DRAW because we're only writing it once
				glBufferData(GL_ARRAY_BUFFER, sizeof(float) * _numVertices * 3, &tangentData[0], GL_STATIC_DRAW);
				glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, 0);
				glEnableVertexAttribArray(3);

				// Variable for storing a VBO
				GLuint bitangentBuffer = 0;
				// Create a generic 'buffer'
				glGenBuffers(1, &bitangentBuffer);
				// Tell OpenGL that we want to activate the buffer and that it's a VBO
				glBindBuffer(GL_ARRAY_BUFFER, bitangentBuffer);
				// With this buffer active, we can now send our data to OpenGL
				// We need to tell it how much data to send
				// We can also tell OpenGL how we intend to use this buffer - here we say GL_STATIC_DRAW because we're only writing it once
				glBufferData(GL_ARRAY_BUFFER, sizeof(float) * _numVertices * 3, &bitangentData[0], GL_STATIC_DRAW);
				glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, 0);
				glEnableVertexAttribArray(4);
			}

		}





	}
	else
	{
		std::cerr << "WARNING: File not found: " << filename << std::endl;
	}
}

void Mesh::Draw()
{
	// Activate the VAO
	glBindVertexArray(_VAO);

	// Tell OpenGL to draw it
	// Must specify the type of geometry to draw and the number of vertices
	glDrawArrays(GL_TRIANGLES, 0, _numVertices);

	// Unbind VAO
	glBindVertexArray(0);
}

