#include "Character.h"

void Character::OnInit()
{
	m_spritePath = "assets/characters/ophilia";
	m_animation = 0;
	m_frame = 0;
	m_timer = 0;
	m_pos.x = 0.35f;
	m_pos.y = -0.5f;
	m_pos.z = 0.5f;
	m_pos.w = 0.7f;

	m_idleSprites.push_back(GetCore()->GetResources()->Load<Texture>(m_spritePath+"_0_0.png"));
	m_idleSprites.push_back(GetCore()->GetResources()->Load<Texture>(m_spritePath + "_0_1.png"));
	m_idleSprites.push_back(GetCore()->GetResources()->Load<Texture>(m_spritePath + "_0_2.png"));
	m_idleSprites.push_back(GetCore()->GetResources()->Load<Texture>(m_spritePath + "_0_3.png"));
}

void Character::OnTick()
{
	m_timer += GetCore()->GetDeltaTime();

	if (m_timer > 0.25f)
	{
		m_frame++;
		if (m_frame >= 4)
		{
			m_frame = 0;
		}
		m_timer = 0;
	}

}

void Character::OnGui()
{
	GLuint texture = m_idleSprites[m_frame]->GetTexture();

	GetCore()->GetGui()->SetTexture(texture);
	GetCore()->GetGui()->Sprite(m_pos);
}