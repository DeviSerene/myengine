#pragma once
#include "myengine/Component.h"
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <myengine/Core.h>
#include "myengine/Resources.h"
#include "myengine/Texture.h"

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
	std::vector<std::shared_ptr<Texture>> m_idleSprites;
};