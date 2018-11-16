#include "BattleBackground.h"

void BattleBackground::OnInit()
{

	clouds1.x = -1;
	clouds1.y = -1;
	clouds1.z = 2;
	clouds1.w = 2;

	clouds2.x = -3;
	clouds2.y = -1;
	clouds2.z = 2;
	clouds2.w = 2;

	backgroundAssets.x = -1;
	backgroundAssets.y = -1;
	backgroundAssets.z = 2;
	backgroundAssets.w = 2;
	m_sprites.push_back(GetCore()->GetResources()->Load<Texture>("assets/grass_background.png"));
	m_sprites.push_back(GetCore()->GetResources()->Load<Texture>("assets/grass_foreground.png"));
	m_sprites.push_back(GetCore()->GetResources()->Load<Texture>("assets/grass_parallax.png"));
}

void BattleBackground::OnTick()
{
	float movement = GetCore()->GetDeltaTime() * 0.05;
	clouds1.x += movement;
	clouds2.x += movement;

	if (clouds1.x >= 1)
		clouds1.x = -3;
	else if (clouds2.x >= 1)
		clouds2.x = -3;
	////
	//y movement
	////
	if (rand() % 25 == 0)
	{
		clouds1.y += movement;
		clouds2.y += movement;
	}if (rand() % 25 == 0)
	{
		clouds1.y -= movement;
		clouds2.y -= movement;
	}
}

void BattleBackground::OnGui()
{
	glm::vec4 fi;
	fi.x = 1;
	fi.y = 1;
	fi.z = 1;
	fi.w = 1;
	GetCore()->GetGui()->SetFrameInfo(fi);
	//GetCore()->GetGui()->SetTexture(m_sprites[0]->GetTexture());
	//GetCore()->GetGui()->Sprite(backgroundAssets);
	//GetCore()->GetGui()->SetTexture(m_sprites[1]->GetTexture());
	//GetCore()->GetGui()->Sprite(backgroundAssets);
	//GetCore()->GetGui()->SetTexture(m_sprites[2]->GetTexture());
	GetCore()->GetGui()->SetTexture(m_sprites[2]->GetTexture());
	GetCore()->GetGui()->Sprite(clouds1);
	GetCore()->GetGui()->Sprite(clouds2);
}