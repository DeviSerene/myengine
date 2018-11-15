#pragma once
#include "myengine/Component.h"

class Stats : public Component
{
public:
	void OnInit();

private:
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
};