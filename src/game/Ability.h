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
#include "Stats.h"

enum BATTLE_ELEMENT
{
	BE_SWORD, BE_STAFF, BE_AXE, BE_FIRE, BE_ICE, BE_LIGHT
};

class Ability : public Component
{
public:
	Ability(std::string _filepath, std::string _name, BATTLE_ELEMENT _element, int _damage, int _sp);
	void OnInit(); //this will override the Components
	void OnGui();
	void OnTick();

	bool IsThis(std::string _name) { return (m_name == _name); }
	void SetPos(float x, float y) { m_pos.x = x; m_pos.y = y;}
	void Begin() { APlaySound();  m_display = true; m_finished = false; }
	bool IsFinished() { return m_finished; }
	int GetDamage() { return m_damage + ((rand()%10) - 5); }
	int GetCost() { return m_spCost; }
	BATTLE_ELEMENT GetElement() { return m_element; }
	void APlaySound() { GetCore()->GetResources()->Load<Sound>(m_filepath + ".ogg")->Play(glm::vec3(m_pos),glm::vec3(0)); }

private:
	std::string m_name;
	std::string m_filepath;
	glm::vec4 m_pos;
	std::shared_ptr<Texture> m_sprite;
	int m_damage;
	int m_spCost;
	float m_scale;
	BATTLE_ELEMENT m_element;

	int m_frame;
	float m_timer;

	bool m_display;
	bool m_finished;
};