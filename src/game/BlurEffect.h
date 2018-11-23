#pragma once
#include "myengine/Component.h"
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <myengine/Core.h>
#include "myengine/Resources.h"
#include "myengine/Texture.h"
#include "myengine/PostProcess.h"

class BlurEffect : public Component
{
public:
	void OnInit();
	void OnPostProcess();
	void OnTick();
	void OnGui();
	void screenshot(char filename[160], int x, int y);
private:
	std::shared_ptr<PostProcess> m_pp;
	std::shared_ptr<Camera> m_cam;
};