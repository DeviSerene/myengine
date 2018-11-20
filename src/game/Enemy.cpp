#include "Enemy.h"

Enemy::Enemy()
{
	m_pos.x = -0.85f;
	m_pos.y = -0.5f;
	//
	m_filepath = "assets/characters/enemy_01";
	m_clicked = false;
	m_clickable = false;
}

Enemy::Enemy(float x, float y, std::string _filepath)
{

	m_pos.x = x;
	m_pos.y = y;
	//
	m_filepath = _filepath;
	m_BP = 1;
	m_maxBP = 1;
}

void Enemy::OnInit()
{
	m_sprite = GetCore()->GetResources()->Load<Texture>(m_filepath + ".png");
	m_glow = GetCore()->GetResources()->Load<Texture>(m_filepath + "_glow.png");
	m_brokenS = GetCore()->GetResources()->Load<Texture>(m_filepath + "_broken.png");
	m_break = GetCore()->GetResources()->Load<Texture>("assets/characters/break_1.png");

	float multiplier = (abs(m_pos.y) / 0.5f) *0.85;
	m_pos.z = 0.01f * m_sprite->GetWidth() * multiplier;
	m_pos.w = 0.01f * m_sprite->GetHeight()* multiplier;

	m_stats = std::shared_ptr<Stats>(new Stats(GetCore()->GetResources()->Load < TextTexture>("Monster"), GetCore()->GetResources()));

	m_dead = false;
	m_broken = false;
	m_recoverNextTurn = false;
	m_damageTimer = 1.5f;
	//GetCore()->GetResources()->Load<Texture>("assets/ele_unknown.png") //BE_SWORD, BE_STAFF, BE_AXE, BE_FIRE, BE_ICE, BE_LIGHT
	m_eleIcons.push_back(GetCore()->GetResources()->Load<Texture>("assets/ele_unknown.png"));
	m_eleIcons.push_back(GetCore()->GetResources()->Load<Texture>("assets/ele_staff.png"));
	m_eleIcons.push_back(GetCore()->GetResources()->Load<Texture>("assets/ele_staff.png"));
	m_eleIcons.push_back(GetCore()->GetResources()->Load<Texture>("assets/ele_staff.png"));
	m_eleIcons.push_back(GetCore()->GetResources()->Load<Texture>("assets/ele_light.png"));
	m_eleIcons.push_back(GetCore()->GetResources()->Load<Texture>("assets/ele_light.png"));
	m_eleIcons.push_back(GetCore()->GetResources()->Load<Texture>("assets/ele_light.png"));
}

void Enemy::OnTick()
{
	if (m_damageTimer < 1.5f)
	{
		m_damageTimer += GetCore()->GetDeltaTime();
		m_damagePos.y += 0.2f * GetCore()->GetDeltaTime();
	}
}

void Enemy::OnGui()
{
	if (!m_dead)
	{
		//draw the character sprite in the current frame
		if (m_broken)
			GetCore()->GetGui()->SetTexture(m_brokenS->GetTexture());
		else
			GetCore()->GetGui()->SetTexture(m_sprite->GetTexture());
		GetCore()->GetGui()->SetHighlight(m_glow->GetTexture());
		GetCore()->GetGui()->SetPressed(m_sprite->GetTexture());
		GetCore()->GetGui()->SetFrameInfo({ 1, 1, 1, 1 });
		if (m_clickable)
		{
			if (GetCore()->GetGui()->Button(m_pos, "Ophilia"))
			{
				std::cout << "Hit! ";
				m_clicked = true;
			}
		}
		else
		{
			GetCore()->GetGui()->Sprite(m_pos);
		}
		m_break = GetCore()->GetResources()->Load<Texture>("assets/characters/break_"+std::to_string(m_BP)+".png");
		GetCore()->GetGui()->SetTexture(m_break->GetTexture());
		GetCore()->GetGui()->Sprite(glm::vec4(m_pos.x - (0.075f), m_pos.y - 0.05f, 0.075f, 0.075f));
		///The elements
		for (int i = 0; i < m_weaknesses.size(); i++)
		{
			if (m_weakRevealed[i])
			{
				//show the actual icon
				GetCore()->GetGui()->SetTexture(m_eleIcons[m_weaknesses[i]+1]->GetTexture());
				GetCore()->GetGui()->Sprite(glm::vec4(m_pos.x + (0.075f*i), m_pos.y - 0.05f, 0.075f, 0.075f));

			}
			else
			{
				//show the ? icon
				GetCore()->GetGui()->SetTexture(m_eleIcons[0]->GetTexture());
				GetCore()->GetGui()->Sprite(glm::vec4(m_pos.x + (0.075f*i), m_pos.y - 0.05f, 0.075f, 0.075f));

			}
		}
	}

	if (m_damageTimer < 1.5f)
	{
		GetCore()->GetGui()->SetTexture(m_damage->GetTexture());
		GetCore()->GetGui()->Sprite(m_damagePos);
	}
}

void Enemy::TakeDamage(int _damage, BATTLE_ELEMENT _element, int _bp)
{
	if (!m_broken)
	{
		for (int i = 0; i < m_weaknesses.size(); i++)
		{
			if (m_weaknesses[i] == _element)
			{
				//break
				m_BP--;
				if (m_BP <= 0)
				{
					m_broken = true;
					m_recoverNextTurn = false;
				}
				_damage += (float)(_damage)* 0.5f;
				m_weakRevealed[i] = true;
			}
		}
	}
	else
	{
		_damage += _damage;
	}
	if (_bp)
	{
		_damage += ((float)_damage * ((float)_bp / 2.0f));
	}

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
		GetCore()->GetResources()->Load<Sound>("assets/enemyDeath.ogg")->Play();
	}

}

void Enemy::NextTurn()
{ 
	if (m_broken == true && m_recoverNextTurn == false)
	{
		m_recoverNextTurn = true;
	}
	else if (m_broken == true && m_recoverNextTurn == true) 
	{ 
		m_recoverNextTurn = false; 
		m_broken = false; 
		m_BP = m_maxBP;
	} 
}
