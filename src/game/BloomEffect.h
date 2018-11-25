#pragma once
#include "myengine/Component.h"
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <myengine/Core.h>
#include "myengine/Resources.h"
#include "myengine/Texture.h"
#include "myengine/PostProcess.h"

class BloomEffect : public Component
{
public:
	void OnInit();
	void OnPostProcess();
	void OnTick();
	void OnGui();
	void screenshot(char filename[160], int x, int y);
	void SetColInfo(glm::vec3 _colourInfo) { m_colourInfo = _colourInfo; }
private:
	std::shared_ptr<PostProcess> m_lightKey;
	std::shared_ptr<PostProcess> m_blur;
	std::shared_ptr<PostProcess> m_pass;
	std::shared_ptr<PostProcess> m_merge;
	std::shared_ptr<Camera> m_cam;
	glm::vec3 m_colourInfo;
};