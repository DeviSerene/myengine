#include "Ability.h"

Ability::Ability(std::string _filepath, std::string _name, BATTLE_ELEMENT _element, int _damage)
{
	//
	m_filepath = _filepath;
	m_name = _name;
	m_element = _element;
	m_damage = _damage;
}

void Ability::OnInit()
{
	m_sprite = GetCore()->GetResources()->Load<Texture>(m_filepath);
	m_display = false;
	m_finished = true;
	m_pos.z = 0.5f;// *m_sprite->GetWidth();
	m_pos.w = 0.5f;// *m_sprite->GetHeight();
	m_timer = 0;
	m_frame = 0;
}

void Ability::OnTick()
{
	if (!m_display)
		return;

	m_timer += GetCore()->GetDeltaTime();
	if (m_timer > 0.2f)
	{
		m_frame++;
		if (m_frame >= 4)
		{
			m_frame = 0;
			m_finished = true;
			m_display = false;
		}
		m_timer = 0;
	}
}

void Ability::OnGui()
{
	if (!m_display)
		return;

	float multiplier = 1;// (abs(m_pos.y) / 0.5f) *0.85;
	GetCore()->GetGui()->SetTexture(m_sprite->GetTexture());
	GetCore()->GetGui()->SetFrameInfo({ m_frame , 1, 4, 1 });
	GetCore()->GetGui()->Sprite(glm::vec4(m_pos.x, m_pos.y, m_pos.z* multiplier, m_pos.w* multiplier));
}