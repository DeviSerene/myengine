#pragma once
#include "myengine/TextTexture.h"
#include <memory>
#include "myengine/Resources.h"
#include <glm/glm.hpp>
#include "myengine/Gui.h"

class Stats
{
public:
	Stats(std::shared_ptr<TextTexture> _name, std::shared_ptr<Resources> _resources);
	void Draw(float _posY, std::shared_ptr <Gui> _gui, int _bp, int _bpH);
	int GetSpeed() { return m_spd; }
	bool TakeDamage(int _damage) { m_curHP -= _damage; if (m_curHP < 0) m_curHP = 0; SetStats(); if (m_curHP <= 0)return true; else return false; }
	void HealDamage(int _damage) { m_curHP += _damage; if (m_curHP >= m_maxHP) m_curHP = m_maxHP; SetStats();}
	void ChangeSP(int _amount) { m_curMP += _amount; if (m_curMP < 0) { m_curMP = 0; }else if (m_curMP > m_maxMP) { m_curMP = m_maxMP; }SetStats();}
	bool CanCast(int _amount) { if (m_curMP >= _amount) return true; else return false; }
	void SetMHP(int _a) { m_maxHP = _a; m_curHP = _a; }

private:

	void SetStats();

	int m_maxHP;
	int m_curHP;
	int m_maxMP;
	int m_curMP;

	int m_str;
	int m_mag;

	int m_def;
	int m_res;

	int m_spd;
	int m_crit;
	////
	std::shared_ptr<Resources> m_resources;
	std::shared_ptr<TextTexture> m_name;
	std::shared_ptr<TextTexture> m_hpText;
	std::shared_ptr<TextTexture> m_mpText;
	std::shared_ptr<Texture> m_statusBar;
	std::shared_ptr<Texture> m_hpBar;
	std::shared_ptr<Texture> m_mpBar;
	std::shared_ptr<Texture> m_bp;
	std::shared_ptr<Texture> m_bpEmpty;
	std::shared_ptr<Texture> m_bpH;
};