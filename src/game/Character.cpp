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
	//

	test.x = -0.85f;
	test.y = -0.5f;
	test.z = 0.5f;
	test.w = 0.7f;

	m_spritesheet = GetCore()->GetResources()->Load<Texture>(m_spritePath + ".png");
	m_glowSheet = GetCore()->GetResources()->Load<Texture>(m_spritePath + "_glow.png");
	m_stats = std::shared_ptr<Stats>(new Stats(GetCore()->GetResources()->Load < TextTexture>("Ophilia"), GetCore()->GetResources()));
	m_dead = false;
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
	//draw the character sprite in the current frame
	GetCore()->GetGui()->SetTexture(m_spritesheet->GetTexture());
	GetCore()->GetGui()->SetHighlight(m_glowSheet->GetTexture());
	GetCore()->GetGui()->SetPressed(m_glowSheet->GetTexture());
	GetCore()->GetGui()->SetFrameInfo({ m_frame + 1, m_animation + 1, 4, 1 });
	
	if (GetCore()->GetGui()->Button(m_pos, "Ophilia"))
	{
		std::cout << "Hit! ";
	}
	//draw the name of the character
	m_stats->Draw(0.9f, GetCore()->GetGui());
	//GetCore()->GetGui()->SetTexture(m_name->GetTexture());
	//GetCore()->GetGui()->SetFrameInfo({ 1,1,1,1 });
	//GetCore()->GetGui()->Sprite({ m_pos.x, m_pos.y+ m_pos.w,0.005f * m_name->GetWidth(),0.005f * m_name->GetHeight() });

}