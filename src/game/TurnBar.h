#pragma once
#include "myengine/Component.h"
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <myengine/Core.h>
#include "myengine/Resources.h"
#include "myengine/Texture.h"
#include "myengine/Sound.h"
#include "ActionBar.h"
#include "Ability.h"

class TurnBar : public Component
{
public:
	TurnBar();
	void OnInit(); //this will override the Components
	void OnGui();
	void OnTick();

	void PlayMusic(std::string _music);
	void SetAB(std::shared_ptr<ActionBar> _actionBar) { m_actionBar = _actionBar; }
	void SetAbilities(std::vector<std::shared_ptr<Ability>> _ab) { m_abilities = _ab; }
	void SetCombatants(std::vector<std::shared_ptr<Entity>> _party, std::vector<std::shared_ptr<Entity>> _enemies);
	void SetNextTurnOrder();
	void NextTurn();
	void Actioned() { m_currentTurnOrder.erase(m_currentTurnOrder.begin()); }

private:
	bool m_active;

	glm::vec4 m_pos;
	glm::vec3 m_blurinfo;
	glm::vec3 m_darkinfo;
	//textures
	std::shared_ptr<Sound> m_bgm;
	std::shared_ptr<Sound> m_victory;
	std::shared_ptr<Sound> m_defeat;
	std::shared_ptr<Texture> m_nextTurn;
	std::vector<std::shared_ptr<Texture>> m_icons;
	std::vector<std::shared_ptr<Entity>> m_party;
	std::vector<std::shared_ptr<Entity>> m_enemies;
	std::vector<std::shared_ptr<Ability>> m_abilities;
	std::shared_ptr<ActionBar> m_actionBar;
	//switches
	std::vector<int> m_currentTurnOrder;
	std::vector<int> m_nextTurnOrder;

	bool m_finished;
	bool m_canClick;
	float m_timer;
	float m_waitTime;
	void UpdateBar();
};