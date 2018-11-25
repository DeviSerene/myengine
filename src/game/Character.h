#pragma once
#include "myengine/Component.h"
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <myengine/Core.h>
#include "myengine/Resources.h"
#include "myengine/Texture.h"
#include "myengine/TextTexture.h"
#include "BlurEffect.h"
#include "Stats.h"

class Character : public Component
{
public:
	void SetBlurEffect(std::shared_ptr<BlurEffect> _be) { m_blur = _be; }
	void OnInit(); //this will override the Components
	void OnGui();
	void OnTick();
	std::string GetFilePath() { return m_spritePath; }
	bool IsDead() { return m_dead; }
	int GetSpeed() {return m_stats->GetSpeed(); }

	void NextTurn();
	int GetCurrentBP() { return m_activeBP; }
	void IncBP();
	void DecBP();
	void RemoveBP(int _n);
	void SetClickable(bool _b) { m_clickable = _b; if (_b == false)m_clicked = false; }
	bool GetClicked() {return m_clicked; }
	float GetX() { return m_pos.x; }
	float GetY() { return m_pos.y; }
	void TakeDamage(int _amount);
	void HealDamage(int _amount, int _bp);
	void RemoveSP(int _amount) { m_stats->ChangeSP(-_amount); }
	bool CanCast(int _amount) { return m_stats->CanCast(_amount); }
	std::shared_ptr<BlurEffect> GetBlurEffect() { return m_blur; }

private:
	std::string m_spritePath;
	int m_animation;
	int m_frame;
	float m_timer;
	glm::vec4 m_pos;
	glm::vec4 test;
	std::shared_ptr<Texture> m_spritesheet;
	std::shared_ptr<Texture> m_glowSheet;
	std::shared_ptr <Stats> m_stats;
	std::shared_ptr<BlurEffect> m_blur;

	glm::vec4 m_damagePos;
	std::shared_ptr<TextTexture> m_damage;
	float m_damageTimer;

	int m_BP;
	int m_activeBP;
	bool m_recoverBP;
	bool m_clickable;
	bool m_clicked;

	bool m_dead;
};