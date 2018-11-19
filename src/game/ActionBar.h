#pragma once
#include "myengine/Component.h"
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <myengine/Core.h>
#include "myengine/Resources.h"
#include "myengine/Texture.h"

class ActionBar : public Component
{
public:
	void OnInit(); //this will override the Components
	void OnGui();
	void OnTick();

	void SetActiveState(bool _set) { m_active = _set; if (_set == false) { m_clickedSkills = false; m_clickedAttack = false; m_clickedAction1 = false; m_clickedAction2 = false; } }
	bool TargettingEnemy() { return (m_clickedAttack || m_clickedAction2); }
	bool TargettingAlly() { return m_clickedAction1; }
	int AbilityUsed() { if (m_clickedAttack)return 0; if (m_clickedAction1)return 1; if (m_clickedAction2)return 2; return -1; }

private:
	bool m_active;

	glm::vec4 m_pos;
	glm::vec4 m_skillbar;
	//textures
	std::shared_ptr<Texture> m_attack;
	std::shared_ptr<Texture> m_skill;
	std::shared_ptr<Texture> m_action1;
	std::shared_ptr<Texture> m_action2;
	std::shared_ptr<Texture> m_attackGlow;
	std::shared_ptr<Texture> m_skillGlow;
	std::shared_ptr<Texture> m_action1Glow;
	std::shared_ptr<Texture> m_action2Glow;
	//switches
	bool m_clickedSkills;
	bool m_clickedAttack;
	bool m_clickedAction1;
	bool m_clickedAction2;

	bool m_canClick;
	float m_timer;
};