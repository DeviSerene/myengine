#include "ActionBar.h"

void ActionBar::OnInit()
{
	m_attack = GetCore()->GetResources()->Load<Texture>("assets/bar0.png");
	m_skill = GetCore()->GetResources()->Load<Texture>("assets/bar1.png");
	m_action1 = GetCore()->GetResources()->Load<Texture>("assets/action_0.png");
	m_action2 = GetCore()->GetResources()->Load<Texture>("assets/action_1.png");

	m_attackGlow = GetCore()->GetResources()->Load<Texture>("assets/bar0_glow.png");
	m_skillGlow = GetCore()->GetResources()->Load<Texture>("assets/bar1_glow.png");
	m_action1Glow = GetCore()->GetResources()->Load<Texture>("assets/action_0_glow.png");
	m_action2Glow = GetCore()->GetResources()->Load<Texture>("assets/action_1_glow.png");

	m_clickedSkills = false;
	m_clickedAttack = false;
	m_clickedAction1 = false;
	m_clickedAction2 = false;

	m_pos.x = 0.15f;
	m_pos.y = -0.05f;
	m_pos.z = 0.3f;
	m_pos.w = 0.1f;
	m_canClick = true;
	m_timer = 0;
	m_active = true;
}

void ActionBar::OnTick()
{
	if (!m_active)
		return;
	if (m_canClick == false)
	{
		m_timer += GetCore()->GetDeltaTime();
		if (m_timer >= 0.25f)
		{
			m_canClick = true;
			m_timer = 0;
		}
	}
	//
	if (GetCore()->GetKeyboard()->PressOnce(B_BUTTON))
	{
		if (m_clickedAction1 || m_clickedAction2)
		{
			m_clickedAction1 = false;
			m_clickedAction2 = false;
		}
		else if (m_clickedSkills || m_clickedAttack)
		{
			m_clickedSkills = false;
			m_clickedAttack = false;
		}
	}
}

void ActionBar::OnGui()
{
	if (!m_active)
		return;
	m_pos.x = 0.15f;
	m_pos.y = -0.05f;
	m_pos.z = 0.3f;
	m_pos.w = 0.1f;

	GetCore()->GetGui()->SetFrameInfo({ 1, 1, 1, 1 });
	if (m_clickedAttack == false && m_clickedSkills == false)
	{
		//Draw the Attack Button
		GetCore()->GetGui()->SetTexture(m_attack->GetTexture());
		GetCore()->GetGui()->SetHighlight(m_attackGlow->GetTexture());
		GetCore()->GetGui()->SetPressed(m_attackGlow->GetTexture());
		if (GetCore()->GetGui()->Button(m_pos, "Ophilia"))
		{
			m_clickedAttack = true;
			m_canClick = false;
		}
		//Draw the Skills Button
		m_pos.y -= 0.1f;
		GetCore()->GetGui()->SetTexture(m_skill->GetTexture());
		GetCore()->GetGui()->SetHighlight(m_skillGlow->GetTexture());
		GetCore()->GetGui()->SetPressed(m_skillGlow->GetTexture());
		if (GetCore()->GetGui()->Button(m_pos, "Ophilia"))
		{
			m_clickedSkills = true;
			m_canClick = false;
		}
	}
	else if(m_clickedAttack == false && m_clickedSkills == true)
	{
		//Draw the Attack Sprite
		m_pos.x = m_pos.x - m_pos.z;
		GetCore()->GetGui()->SetTexture(m_attack->GetTexture());
		GetCore()->GetGui()->Sprite(m_pos);
		//Draw the Skills Clicked Sprite
		GetCore()->GetGui()->SetTexture(m_skillGlow->GetTexture());
		m_pos.y -= 0.1f;
		GetCore()->GetGui()->Sprite(m_pos);
		//list the skills
		m_pos.x = m_pos.x + m_pos.z;
		if (m_clickedAction1 == false && m_clickedAction2 == false)
		{
			//Draw the Skill1 Button
			GetCore()->GetGui()->SetTexture(m_action1->GetTexture());
			GetCore()->GetGui()->SetHighlight(m_action1Glow->GetTexture());
			GetCore()->GetGui()->SetPressed(m_action1Glow->GetTexture());
			if (GetCore()->GetGui()->Button(m_pos, "Ophilia") && m_canClick == true)
			{
				m_clickedAction1 = true;
			}
			//
			//Draw the Skill2 Button
			m_pos.y -= 0.1f;
			GetCore()->GetGui()->SetTexture(m_action2->GetTexture());
			GetCore()->GetGui()->SetHighlight(m_action2Glow->GetTexture());
			GetCore()->GetGui()->SetPressed(m_action2Glow->GetTexture());
			if (GetCore()->GetGui()->Button(m_pos, "Ophilia") && m_canClick == true)
			{
				m_clickedAction2 = true;
			}
		}
		else
		{
			//Draw the Skill1 Sprite
			if(m_clickedAction1)
				GetCore()->GetGui()->SetTexture(m_action1Glow->GetTexture());
			else
				GetCore()->GetGui()->SetTexture(m_action1->GetTexture());

			GetCore()->GetGui()->Sprite(m_pos);
			//
			//Draw the Skill2 Sprite
			m_pos.y -= 0.1f;
			if (m_clickedAction2)
				GetCore()->GetGui()->SetTexture(m_action2Glow->GetTexture());
			else
				GetCore()->GetGui()->SetTexture(m_action2->GetTexture());
			GetCore()->GetGui()->Sprite(m_pos);
		}
	}
	else
	{

		//Draw the Attack Clicked Sprite
		GetCore()->GetGui()->SetTexture(m_attackGlow->GetTexture());
		GetCore()->GetGui()->Sprite(m_pos);
		//Draw the Skills Sprite
		GetCore()->GetGui()->SetTexture(m_skill->GetTexture());
		m_pos.y -= 0.1f;
		GetCore()->GetGui()->Sprite(m_pos);
	}

}