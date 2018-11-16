#pragma once
#include "myengine/Component.h"
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <myengine/Core.h>
#include "myengine/Resources.h"
#include "myengine/Texture.h"
#include "myengine/TextTexture.h"

class Character : public Component
{
public:
	void OnInit(); //this will override the Components
	void OnGui();
	void OnTick();

private:
	std::string m_spritePath;
	int m_animation;
	int m_frame;
	float m_timer;
	glm::vec4 m_pos;
	glm::vec4 test;
	std::shared_ptr<Texture> m_spritesheet;
	std::shared_ptr<Texture> m_glowSheet;
	std::shared_ptr<TextTexture> m_name;
};