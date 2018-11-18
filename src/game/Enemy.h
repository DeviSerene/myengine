#pragma once
#include "myengine/Component.h"
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <myengine/Core.h>
#include "myengine/Resources.h"
#include "myengine/Texture.h"
#include "myengine/TextTexture.h"
#include "Stats.h"
#include "Ability.h"

class Enemy : public Component
{
public:
	void OnInit(); //this will override the Components
	void OnGui();
	void OnTick();
	Enemy();
	Enemy(float x, float y, std::string _filepath);
	std::string GetFilePath() { return m_filepath; }
	bool IsDead() { return m_dead; }
	int GetSpeed() { return m_stats->GetSpeed(); }
	void SetClickable(bool _set) { m_clickable = _set; if (_set == false) m_clicked = false; }
	bool GetClicked() { return m_clicked; }
	float GetX() { return m_pos.x; }
	float GetY() { return m_pos.y; }
	bool IsBroken() { return m_broken; }
	bool IsRecoveringNext() { return m_recoverNextTurn; }
	void NextTurn();//
	void TakeDamage(int _damage, BATTLE_ELEMENT _element);
	void AddWeakness(BATTLE_ELEMENT _weakness){m_weaknesses.push_back(_weakness); m_weakRevealed.push_back(false); }
private:
	std::string m_filepath;
	glm::vec4 m_pos;
	glm::vec4 m_damagePos;
	std::shared_ptr<Texture> m_sprite;
	std::shared_ptr<Texture> m_glow;
	std::shared_ptr<Texture> m_brokenS;
	std::shared_ptr<TextTexture> m_damage;
	std::shared_ptr<TextTexture> m_breakText;
	std::shared_ptr < Stats> m_stats;
	bool m_dead;
	bool m_clickable;
	bool m_clicked;
	bool m_recoverNextTurn;
	bool m_broken;
	std::vector<BATTLE_ELEMENT> m_weaknesses;
	std::vector<bool> m_weakRevealed;
	std::vector < std::shared_ptr<Texture>> m_eleIcons;

	float m_damageTimer;
};