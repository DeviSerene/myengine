#pragma once
#include "myengine/Component.h"
#include "myengine/Core.h"
#include "myengine/Resources.h"
#include "myengine/Texture.h"
#include <glm/glm.hpp>
#include <vector>
#include <memory>

class BattleBackground : public Component
{
public:
	void OnInit();
	void OnTick();
	void OnGui();

private:

	glm::vec4 clouds1;
	glm::vec4 clouds2;
	glm::vec4 backgroundAssets;
	std::vector<std::shared_ptr<Texture>> m_sprites;
};