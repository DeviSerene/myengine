#include "GameOver.h"

void GameOver::OnInit()
{
	m_title = GetCore()->GetResources()->Load<Texture>("assets/menu/gameover.png");

	//m_bgm = GetCore()->GetResources()->Load<Sound>("assets/death.ogg");//
	//m_bgm->Play();
	m_timer = 0;
}

void GameOver::OnTick()
{
	m_timer += GetCore()->GetDeltaTime();

	if (m_timer >= 5.0f)
	{
	//	m_bgm->Stop();
		GetCore()->GetResources()->StopAllSounds();
		GetCore()->SetScene(0);
	}

}

void GameOver::OnGui()
{
	GetCore()->GetGui()->SetFrameInfo({ 1 , 1, 1, 1 });

	GetCore()->GetGui()->SetTexture(m_title->GetTexture());
	GetCore()->GetGui()->Sprite(glm::vec4(-0.5f, 0.25f, 1.0f, 0.25f));

}