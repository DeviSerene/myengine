#include "Character.h"
#include "myengine/Sound.h"

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
	m_activeBP = 0;
	m_BP = 0;
	m_recoverBP = true;
	m_clickable = false;
	m_clicked = false;
	m_damageTimer = 1.5f;
}

void Character::OnTick()
{
	if (m_damageTimer < 1.5f)
	{
		m_damageTimer += GetCore()->GetDeltaTime();
		m_damagePos.y += 0.2f * GetCore()->GetDeltaTime();
	}

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
	
	if (m_clickable)
	{
		if (GetCore()->GetGui()->Button(m_pos, "Ophilia"))
		{
			m_clicked = true;
		}
	}
	else
	{
		GetCore()->GetGui()->Sprite(m_pos);
	}
	//draw the stats of the character
	m_stats->Draw(0.9f, GetCore()->GetGui(), m_BP, m_activeBP);
	
	if (m_damageTimer < 1.5f)
	{
		GetCore()->GetGui()->SetTexture(m_damage->GetTexture());
		GetCore()->GetGui()->Sprite(m_damagePos);
	}

}

void Character::NextTurn()
{
	if (m_recoverBP == false)
	{
		m_recoverBP = true;
	}
	else
	{
		m_BP++;
		if (m_BP > 5)
			m_BP = 5;
	}
	m_activeBP = 0;
	m_clicked = false;
}

void Character::IncBP()
{
	if (m_BP >= m_activeBP + 1)
	{
		if (m_activeBP < 3)
		{
			m_activeBP++;
			GetCore()->GetResources()->Load<Sound>("assets/incBP.ogg")->Play();
		}
	}
	//GetCore()->GetGui()->SetBlurInfo(glm::vec3(0.75f - ((float)m_activeBP * 0.2f), 0.75f - ((float)m_activeBP * 0.2f), 0.75f - ((float)m_activeBP * 0.2f)));
	m_blur->SetBlurInfo(glm::vec3(0.75f - ((float)m_activeBP * 0.2f), 0.75f - ((float)m_activeBP * 0.2f), 0.75f - ((float)m_activeBP * 0.2f)));
}


void Character::DecBP()
{
	if(m_activeBP > 0)
		GetCore()->GetResources()->Load<Sound>("assets/decBP.ogg")->Play();

	m_activeBP--; 
	if (m_activeBP < 0)
	{
		m_activeBP = 0;
	}
	//GetCore()->GetGui()->SetBlurInfo(glm::vec3(0.75f - ((float)m_activeBP * 0.2f)));
	m_blur->SetBlurInfo(glm::vec3(0.75f - ((float)m_activeBP * 0.2f)));
}
void Character::RemoveBP(int _n) 
{ 
	m_BP -= _n; 
	if (_n > 0)
		m_recoverBP = false; 

	//GetCore()->GetGui()->SetBlurInfo(glm::vec3(0.75f, 0.75f, 0.75f));
	m_blur->SetBlurInfo(glm::vec3(0.75f, 0.75f, 0.75f));
}

void Character::HealDamage(int _damage, int _bp)
{
	if (_bp)
	{
		_damage += ((float)_damage * ((float)_bp / 2.0f));
	}

	m_damage = GetCore()->GetResources()->Load<TextTexture>(std::to_string(_damage));
	m_damage->SetText({ 0,255,0,255 }, 12);
	m_damagePos.x = m_pos.x + (m_pos.z * 0.25);
	m_damagePos.y = m_pos.y + (m_pos.w * 0.5);
	m_damagePos.z = m_damage->GetWidth() * 0.005;
	m_damagePos.w = m_damage->GetHeight()* 0.005;
	m_damageTimer = 0;

	m_stats->HealDamage(_damage);

}

void Character::TakeDamage(int _damage)
{

	m_damage = GetCore()->GetResources()->Load<TextTexture>(std::to_string(_damage));
	m_damage->SetText({ 255,0,0,255 }, 12);
	m_damagePos.x = m_pos.x + (m_pos.z * 0.25);
	m_damagePos.y = m_pos.y + (m_pos.w * 0.5);
	m_damagePos.z = m_damage->GetWidth() * 0.005;
	m_damagePos.w = m_damage->GetHeight()* 0.005;
	m_damageTimer = 0;

	if (m_stats->TakeDamage(_damage))
	{
		m_dead = true;
	}

}