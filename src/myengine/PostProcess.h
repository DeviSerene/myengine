#pragma once
#include <string>
#include "GL/glew.h"
#include "glm/glm.hpp"
#include "FrameBuffer.h"

class Core;
class Shader;
class VertexArray;

class PostProcess
{
public:
	void LoadShader(std::shared_ptr<Core> _core, std::string _name, std::string _vert, std::string _frag);


	void SetEffect(std::string _id, glm::mat4 _variable);
	void SetEffect(std::string _id, glm::vec4 _variable);
	void SetEffect(std::string _id, glm::vec3 _variable);
	void SetEffect(std::string _id, glm::vec2 _variable);
	void SetEffect(std::string _id, bool _variable);

	void SetTexture(std::string _uniform, GLuint _texture, int _textureNo);
	void AddEffect(std::string _id);

	void Draw(GLuint _oldTexture);

	std::string GetName() { return m_name; }
	GLuint GetTexture() { return m_fb->GetTexture(); }
	std::shared_ptr<FrameBuffer> GetFB() { return m_fb; }

private:
	std::string m_name;
	std::shared_ptr<Shader> m_shader;
	std::shared_ptr<FrameBuffer> m_fb;
	std::shared_ptr<VertexArray> m_shape;
};