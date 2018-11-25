#include "TitleButtons.h"

void TitleButtons::OnInit()
{
	m_title = GetCore()->GetResources()->Load<Texture>("assets/menu/title.png");
	m_play = GetCore()->GetResources()->Load<Texture>("assets/menu/battle.png");
	m_controls = GetCore()->GetResources()->Load<Texture>("assets/menu/controls.png");
	m_quit = GetCore()->GetResources()->Load<Texture>("assets/menu/quit.png");
	m_play2 = GetCore()->GetResources()->Load<Texture>("assets/menu/battle2.png");
	m_controls2 = GetCore()->GetResources()->Load<Texture>("assets/menu/controls2.png");
	m_quit2 = GetCore()->GetResources()->Load<Texture>("assets/menu/quit2.png");

	m_bgm = GetCore()->GetResources()->Load<Sound>("assets/title.ogg");//
	m_bgm->PlayLoop();

	rebindA = false;
	rebindB = false;
}

void TitleButtons::OnTick()
{
	////This is code for rebinding a button/key;
	if (GetCore()->GetKeyboard()->PressOnce(Y_BUTTON))
	{
		rebindA = true;
		rebindB = false;
		std::cout << "Press a key to rebind RB: " << std::endl;
	}
	else if (rebindA)
	{
		if (GetCore()->GetKeyboard()->ReturnKeyCode())
		{
			if (GetCore()->GetKeyboard()->ReBind(RB_BUTTON, GetCore()->GetKeyboard()->ReturnKeyCode()))
			{
				std::cout << "RB has been REBOUND" << std::endl;
				rebindA = false;
			}

		}
		else if (GetCore()->GetKeyboard()->ReBindButton(RB_BUTTON, GetCore()->GetKeyboard()->ReturnButton()))
		{
			std::cout << "RB has been REBOUND" << std::endl;
			rebindA = false;
		}
	}
	else if (GetCore()->GetKeyboard()->PressOnce(X_BUTTON))
	{
		rebindA = false;
		rebindB = true;
		std::cout << "Press a key to rebind LB: " << std::endl;
	}
	else if (rebindB)
	{
		if (GetCore()->GetKeyboard()->ReturnKeyCode())
		{
			if (GetCore()->GetKeyboard()->ReBind(LB_BUTTON, GetCore()->GetKeyboard()->ReturnKeyCode()))
			{
				std::cout << "LB has been REBOUND" << std::endl;
				rebindB = false;
			}

		}
		else if (GetCore()->GetKeyboard()->ReBindButton(LB_BUTTON, GetCore()->GetKeyboard()->ReturnButton()))
		{
			std::cout << "LB has been REBOUND" << std::endl;
			rebindB = false;
		}
	}
}

void TitleButtons::OnGui()
{
	GetCore()->GetGui()->SetFrameInfo({ 1 , 1, 1, 1 });

	GetCore()->GetGui()->SetTexture(m_title->GetTexture());
	GetCore()->GetGui()->Sprite(glm::vec4(-0.5f, 0.25f, 1.0f, 0.25f));

	GetCore()->GetGui()->SetTexture(m_play->GetTexture());
	GetCore()->GetGui()->SetHighlight(m_play2->GetTexture());
	GetCore()->GetGui()->SetPressed(m_play->GetTexture());
	if (GetCore()->GetGui()->Button(glm::vec4(-0.25f, -0.450f, 0.5f, 0.125f), ""))
	{
		m_bgm->Stop();
		GetCore()->SetScene(1);
	}
	GetCore()->GetGui()->SetTexture(m_controls->GetTexture());
	GetCore()->GetGui()->SetHighlight(m_controls2->GetTexture());
	GetCore()->GetGui()->SetPressed(m_controls->GetTexture());
	//if (GetCore()->GetGui()->Button(glm::vec4(-0.25f, -0.600f, 0.5f, 0.125f), ""))
	//{
//
	//}
	GetCore()->GetGui()->SetTexture(m_quit->GetTexture());
	GetCore()->GetGui()->SetHighlight(m_quit2->GetTexture());
	GetCore()->GetGui()->SetPressed(m_quit->GetTexture());
	if (GetCore()->GetGui()->Button(glm::vec4(-0.25f, -0.750f, 0.5f, 0.125f), ""))
	{
		m_bgm->Stop();
		GetCore()->Stop();
	}

}