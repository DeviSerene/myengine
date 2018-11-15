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
	m_spritesheet = GetCore()->GetResources()->Load<Texture>(m_spritePath + ".png");
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

	float a = (float)(m_frame + 1) / 4.0f;
	std::cout << "X% = " << a << std::endl;

	GetCore()->GetGui()->SetTexture(m_spritesheet->GetTexture());
	GetCore()->GetGui()->SetFrameInfo({ (float)(m_frame + 1),1.0f,4.0f,1.0f });
	GetCore()->GetGui()->Sprite(m_pos);
}