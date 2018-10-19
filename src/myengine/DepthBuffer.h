#pragma once
#include <string>
#include <GLM/glm.hpp>
#include <GLM/gtc/type_ptr.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <memory>
#include <iostream>
#include <fstream>

class DepthBuffer
{
public:

	void SetUpDepthBuffer();
	void SetMVP(glm::vec3 _lightInvDir);

private:
	/////This is the depth buffer
	GLuint _depthBuffer;
	GLuint _depthTexture;
	glm::mat4 depthMVP;
	int depthMatrixID;


	bool LoadShaders(std::string vertFilename, std::string fragFilename);
	// The OpenGL shader program handle
	int _shaderProgram;

};