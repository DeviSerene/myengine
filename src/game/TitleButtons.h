#pragma once
#include "myengine/Component.h"
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <myengine/Core.h>
#include "myengine/Resources.h"
#include "myengine/Texture.h"
#include "myengine/TextTexture.h"
#include "myengine/Sound.h"

class TitleButtons : public Component
{
public:
	void OnInit(); //this will override the Components
	void OnGui();
	void OnTick();

private:
	std::shared_ptr<Texture> m_title;
	std::shared_ptr<Texture> m_play;
	std::shared_ptr<Texture> m_controls;
	std::shared_ptr<Texture> m_quit;
	std::shared_ptr<Texture> m_play2;
	std::shared_ptr<Texture> m_controls2;
	std::shared_ptr<Texture> m_quit2;
	std::shared_ptr<Sound> m_bgm;

	bool rebindA;
	bool rebindB;
};