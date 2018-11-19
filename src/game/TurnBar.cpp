#include "TurnBar.h"
#include "myengine/Entity.h"
#include "Character.h"
#include "Enemy.h"

TurnBar::TurnBar()
{
}

void TurnBar::OnInit()
{
	m_canClick = true;
	m_active = true;
	m_nextTurn = GetCore()->GetResources()->Load<Texture>("assets/nextTurn.png");
	m_timer = 0;
	m_waitTime = 0;
}

void TurnBar::OnTick()
{
	if (!m_active)
		return;

	m_timer += GetCore()->GetDeltaTime();
	if (m_timer < m_waitTime)
		return;

	for (int i = 0; i < m_abilities.size(); i++)
	{
		if (!m_abilities[i]->IsFinished())
			return;
	}

	if (m_currentTurnOrder.empty())
	{
		NextTurn();
	}
	else
	{
		if (m_currentTurnOrder[0] >= m_party.size())
		{
			//enemies
			m_actionBar->SetActiveState(false);
			Actioned();
			m_waitTime = 1;
			m_timer = 0;
			std::cout << "Enemy ATTACK ";
		}
		else
		{
			//Handle BP
			if (GetCore()->GetKeyboard()->PressOnce(RB_BUTTON))
			{
				m_party[m_currentTurnOrder[0]]->GetComponent<Character>()->IncBP();
				m_waitTime = 0.075;
				m_timer = 0;
			}
			else if (GetCore()->GetKeyboard()->PressOnce(LB_BUTTON))
			{
				m_party[m_currentTurnOrder[0]]->GetComponent<Character>()->DecBP();
				m_waitTime = 0.075;
				m_timer = 0;
			}

			//its the player
			m_actionBar->SetActiveState(true);
			if (m_actionBar->TargettingEnemy())
			{
				for (int i = 0; i < m_enemies.size(); i++)
				{
					m_enemies[i]->GetComponent<Enemy>()->SetClickable(true);
					if (m_enemies[i]->GetComponent<Enemy>()->GetClicked())
					{
						//use ability/action against this enemy
						m_abilities[m_actionBar->AbilityUsed()]->SetPos(m_enemies[i]->GetComponent<Enemy>()->GetX(), m_enemies[i]->GetComponent<Enemy>()->GetY());
						m_abilities[m_actionBar->AbilityUsed()]->Begin();
						m_enemies[i]->GetComponent<Enemy>()->TakeDamage(m_abilities[m_actionBar->AbilityUsed()]->GetDamage(), m_abilities[m_actionBar->AbilityUsed()]->GetElement(), m_party[m_currentTurnOrder[0]]->GetComponent<Character>()->GetCurrentBP());
						m_party[m_currentTurnOrder[0]]->GetComponent<Character>()->RemoveBP(m_party[m_currentTurnOrder[0]]->GetComponent<Character>()->GetCurrentBP());
						UpdateBar();
						Actioned();
						m_actionBar->SetActiveState(false);
						for (int u = 0; u < m_enemies.size(); u++)
						{
							m_enemies[u]->GetComponent<Enemy>()->SetClickable(false);
						}
						m_waitTime = 1.5;
						m_timer = 0;
						std::cout << "ALLY ATTACK ";
						return;
					}
				}
			}
			else
			{
				for (int i = 0; i < m_enemies.size(); i++)
				{
					m_enemies[i]->GetComponent<Enemy>()->SetClickable(false);
				}
			}
		}
	}

}

void TurnBar::OnGui()
{
	if (!m_active)
		return;

	m_pos.x = -0.95f;
	m_pos.y = 0.85f;
	m_pos.z = 0.1f;
	m_pos.w = 0.1f;
	GetCore()->GetGui()->SetFrameInfo({ 1, 1, 1, 1 });

	if (!m_currentTurnOrder.empty())
	{
		for (int i = 0; i < m_currentTurnOrder.size(); i++)
		{
			GetCore()->GetGui()->SetTexture(m_icons[m_currentTurnOrder[i]]->GetTexture());
			GetCore()->GetGui()->Sprite(m_pos);
			m_pos.x += 0.115f;
		}
	}
	m_pos.x += 0.05f;
	m_pos.z = 0.3f;
	GetCore()->GetGui()->SetTexture(m_nextTurn->GetTexture());
	GetCore()->GetGui()->Sprite(m_pos);
	m_pos.x += 0.25f;
	m_pos.z = 0.1f;
	m_pos.w = 0.1f;
	//
	if (!m_nextTurnOrder.empty())
	{
		for (int i = 0; i < m_nextTurnOrder.size(); i++)
		{
			m_pos.x += 0.115f;
			GetCore()->GetGui()->SetTexture(m_icons[m_nextTurnOrder[i]]->GetTexture());
			GetCore()->GetGui()->Sprite(m_pos);
		}
	}
}


void TurnBar::SetCombatants(std::vector<std::shared_ptr<Entity>> _party, std::vector<std::shared_ptr<Entity>> _enemies)
{ 
	m_party = _party; m_enemies = _enemies; 
	std::string file;
	for (int i = 0; i < m_party.size(); i++)
	{
		std::shared_ptr<Character> chara = m_party[i]->GetComponent<Character>();
		m_icons.push_back(GetCore()->GetResources()->Load<Texture>(chara->GetFilePath()+"_turn.png"));
	}
	for (int i = 0; i < m_enemies.size(); i++)
	{
		std::shared_ptr<Enemy> enemy = m_enemies[i]->GetComponent<Enemy>();
		m_icons.push_back(GetCore()->GetResources()->Load<Texture>(enemy->GetFilePath() + "_turn.png"));
	}
	SetNextTurnOrder();
	NextTurn();
}

void TurnBar::SetNextTurnOrder()
{
	m_nextTurnOrder.clear();
	std::vector<int> speedList;
	std::vector<int> order;
	for (int i = 0; i < m_party.size(); i++)
	{
		std::shared_ptr<Character> chara = m_party[i]->GetComponent<Character>();
		if (!chara->IsDead())
		{
			speedList.push_back(chara->GetSpeed() + (rand() % 50));
			order.push_back(i);
		}
	}
	for (int i = 0; i < m_enemies.size(); i++)
	{
		std::shared_ptr<Enemy> enemy = m_enemies[i]->GetComponent<Enemy>();
		if (!enemy->IsDead())
		{
			if (!enemy->IsBroken() || enemy->IsRecoveringNext())
			{
				if (enemy->IsRecoveringNext())
					speedList.push_back(enemy->GetSpeed() + (250));
				else speedList.push_back(enemy->GetSpeed() + (rand() % 50));
				order.push_back(i + m_party.size());
			}
		}
	}
	//we now have a list of speeds e.g. 85, 92, 50. This determines the order in turn;
	//							owner:	 1,  2,  3
	//We need to sort this
	int people = order.size();
	for (int u = 0; u < people; u++)
	{
		int chosenOne = 0;
		int chosenOneSpeed = 0;
		for (int i = 0; i < order.size(); i++)
		{
			if (speedList[i] > chosenOneSpeed)
			{
				chosenOneSpeed = speedList[i];
				chosenOne = i;
			}
		}
		m_nextTurnOrder.push_back(order[chosenOne]);
		speedList.erase(speedList.begin() + chosenOne);
		order.erase(order.begin() + chosenOne);
	}
}

void TurnBar::NextTurn()
{
	for (int p = 0; p < m_party.size(); p++)
	{
		std::shared_ptr<Character> c = m_party[p]->GetComponent<Character>();
		c->NextTurn();
	}
	for (int e = 0; e < m_enemies.size(); e++)
	{
		std::shared_ptr<Enemy> enemy = m_enemies[e]->GetComponent<Enemy>();
		enemy->NextTurn();
	}

	m_currentTurnOrder = m_nextTurnOrder;
	SetNextTurnOrder();
	m_waitTime = 1.25f;
	m_timer = 0;
}

void TurnBar::UpdateBar()
{
	if(!m_currentTurnOrder.empty())
	for (int i = 0; i < m_currentTurnOrder.size(); i++)
	{
		if (m_currentTurnOrder[i] >= m_party.size())
		{
			//enemies
				std::shared_ptr<Enemy> enemy = m_enemies[m_currentTurnOrder[i]- m_party.size()]->GetComponent<Enemy>();
				if (enemy->IsBroken() || enemy->IsDead())
				{
					m_currentTurnOrder.erase(m_currentTurnOrder.begin() + i);
				}
		}
	}

	
	if (!m_nextTurnOrder.empty())
	for (int i = 0; i < m_nextTurnOrder.size(); i++)
	{
		if (m_nextTurnOrder[i] >= m_party.size())
		{
			//enemies
			std::shared_ptr<Enemy> enemy = m_enemies[m_nextTurnOrder[i] - m_party.size()]->GetComponent<Enemy>();
			if (enemy->IsBroken() || enemy->IsDead())
			{
				if (!enemy->IsRecoveringNext() || enemy->IsDead())
				{
					m_nextTurnOrder.erase(m_nextTurnOrder.begin() + i);
				}
			}
		}
	}
	
}