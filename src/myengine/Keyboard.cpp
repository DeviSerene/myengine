#include "Keyboard.h"

Keyboard::Keyboard()
{
	InputButton A;
	A.SetInput(A_BUTTON);
	A.AddKey(SDLK_z);
	A.AddMouse(SDL_BUTTON_LEFT);
	A.m_pressed = false;
	m_inputs.push_back(A);
	///
	InputButton B;
	B.SetInput(B_BUTTON);
	B.AddKey(SDLK_x);
	B.AddMouse(SDL_BUTTON_RIGHT);
	B.m_pressed = false;
	m_inputs.push_back(B);
	///
	InputButton UP;
	UP.SetInput(UP_BUTTON);
	UP.AddKey(SDLK_w);
	UP.m_pressed = false;
	m_inputs.push_back(UP);
	///
	InputButton DOWN;
	DOWN.SetInput(DOWN_BUTTON);
	DOWN.AddKey(SDLK_s);
	DOWN.m_pressed = false;
	m_inputs.push_back(DOWN);
	///
	InputButton LEFT;
	LEFT.SetInput(LEFT_BUTTON);
	LEFT.AddKey(SDLK_a);
	LEFT.m_pressed = false;
	m_inputs.push_back(LEFT);
	///
	InputButton RIGHT;
	RIGHT.SetInput(RIGHT_BUTTON);
	RIGHT.AddKey(SDLK_d);
	RIGHT.m_pressed = false;
	m_inputs.push_back(RIGHT);
	///
	InputButton RB;
	RB.SetInput(RB_BUTTON);
	RB.AddKey(SDLK_e);
	RB.m_pressed = false;
	m_inputs.push_back(RB);
	///
	InputButton LB;
	LB.SetInput(LB_BUTTON);
	LB.AddKey(SDLK_q);
	LB.m_pressed = false;
	m_inputs.push_back(LB);
	///
	ev = { 0 };
	m_lastkey = NULL;
}

Keyboard::~Keyboard()
{
}

void Keyboard::Update()
{
	m_lastkey = NULL;
	ev = { 0 };
	while (SDL_PollEvent(&ev))
	{
		for (unsigned int i = 0; i < m_inputs.size(); i++)
		{
			bool kp = false;
			bool mp = false;

			if (ev.type == SDL_KEYUP)
			{
				for (unsigned int key = 0; key < m_inputs[i].m_mappedKeys.size(); key++)
				{
					if (ev.key.keysym.sym == m_inputs[i].m_mappedKeys[key]) //what key has been pressed?
					{
						kp = false;
						m_inputs[i].m_pressed = false;
					}
				}
			}
			if (ev.type == SDL_KEYDOWN)
			{
				for (unsigned int key = 0; key < m_inputs[i].m_mappedKeys.size(); key++)
				{
					m_lastkey = ev.key.keysym.sym;
					if (ev.key.keysym.sym == m_inputs[i].m_mappedKeys[key]) //what key has been pressed?
					{
						kp = true;
						m_inputs[i].m_pressed = true;
					}
				}
			}

			if (kp == false)
			{
				if (ev.type == SDL_MOUSEBUTTONUP)
				{
					for (unsigned int key = 0; key < m_inputs[i].m_mappedMouse.size(); key++)
					{
						if (ev.button.button == m_inputs[i].m_mappedMouse[key]) //what key has been pressed?
						{
							mp = false;
							m_inputs[i].m_pressed = false;
						}
					}
				}
				if (ev.type == SDL_MOUSEBUTTONDOWN)
				{
					for (unsigned int key = 0; key < m_inputs[i].m_mappedMouse.size(); key++)
					{
						if (ev.button.button == m_inputs[i].m_mappedMouse[key]) //what key has been pressed?
						{
							mp = true;
							m_inputs[i].m_pressed = true;
						}
					}
				}
			}

			/*
			if (mp == true || kp == true)
			{
			}
			else
			{
				m_inputs[i].m_pressed = false;
			}
			*/
		}
	}
}

bool Keyboard::Input(INPUTACTION _type) //has the key been pressed?
{
	for (unsigned int i = 0; i < m_inputs.size(); i++)
	{
		if (m_inputs[i].m_action == _type)
		{
			return m_inputs[i].m_pressed;
		}
	}
	return false;
}

SDL_Keycode Keyboard::ReturnKeyCode()
{
	return m_lastkey;
	ev = { 0 };
	while (SDL_PollEvent(&ev))
	{
		if (ev.type == SDL_KEYDOWN)
		{
			return ev.key.keysym.sym;
		}
	}
	return NULL;
}

bool Keyboard::ReBind(INPUTACTION _type, SDL_Keycode _newKey)
{
	if (_newKey != NULL)
	{
		for (unsigned int i = 0; i < m_inputs.size(); i++)
		{
			if (m_inputs[i].m_action == _type)
			{
				for (unsigned int u = 0; u < m_inputs.size(); u++)
				{
					if (m_inputs[u].m_action != m_inputs[i].m_action)
					{
						for (unsigned int k = 0; k < m_inputs[u].m_mappedKeys.size(); k++)
						{
							if (m_inputs[u].m_mappedKeys[k] == _newKey)
							{
								return false;
							}
						}
					}
				}
				m_inputs[i].m_mappedKeys.clear();
				m_inputs[i].AddKey(_newKey);
				return true;
			}
		}
	}
	return false;
}


bool Keyboard::PressOnce(INPUTACTION _type)
{
	for (unsigned int i = 0; i < m_inputs.size(); i++)
	{
		if (m_inputs[i].m_action == _type)
		{
			if (m_inputs[i].m_pressed)
			{
				m_inputs[i].m_pressed = false;
				return true;
			}
		}
	}
	return false;
}