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
	void SetBlurInfo(glm::vec3 _blurInfo) { m_blurInfo = _blurInfo; }
private:
	std::shared_ptr<PostProcess> m_pp;
	std::shared_ptr<Camera> m_cam;
	glm::vec3 m_blurInfo;
};