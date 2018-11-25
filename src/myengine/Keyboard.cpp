#include "Keyboard.h"
#include <iostream>
#define JOYSTICK_DEAD_ZONE 8000

Keyboard::Keyboard()
{
	m_quit = false;
	controllerConnected = false;

	InputButton A;
	A.SetInput(A_BUTTON);
	A.AddKey(SDLK_z);
	A.AddMouse(SDL_BUTTON_LEFT);
	A.m_pressed = false;
	A.m_cPressed = false;
	A.m_axis = -1;
	A.m_mappedButtons.push_back(SDL_CONTROLLER_BUTTON_A);
	m_inputs.push_back(A);
	///
	InputButton B;
	B.SetInput(B_BUTTON);
	B.AddKey(SDLK_x);
	B.AddMouse(SDL_BUTTON_RIGHT);
	B.m_pressed = false;
	B.m_cPressed = false;
	B.m_axis = -1;
	B.m_mappedButtons.push_back(SDL_CONTROLLER_BUTTON_B);
	m_inputs.push_back(B);
	///
	InputButton X;
	X.SetInput(X_BUTTON);
	X.AddKey(SDLK_c);
	X.m_pressed = false;
	X.m_cPressed = false;
	X.m_axis = -1;
	X.m_mappedButtons.push_back(SDL_CONTROLLER_BUTTON_X);
	m_inputs.push_back(X);
	///
	InputButton Y;
	Y.SetInput(Y_BUTTON);
	Y.AddKey(SDLK_v);
	Y.m_pressed = false;
	Y.m_cPressed = false;
	Y.m_axis = -1;
	Y.m_mappedButtons.push_back(SDL_CONTROLLER_BUTTON_Y);
	m_inputs.push_back(Y);


	///
	InputButton UP;
	UP.SetInput(UP_BUTTON);
	UP.AddKey(SDLK_w);
	UP.m_pressed = false;
	UP.m_cPressed = false;
	UP.m_axis = SDL_CONTROLLER_AXIS_LEFTY;
	UP.m_direction = -1;
	UP.m_mappedButtons.push_back(SDL_CONTROLLER_BUTTON_DPAD_UP);
	m_inputs.push_back(UP);
	///
	InputButton DOWN;
	DOWN.SetInput(DOWN_BUTTON);
	DOWN.AddKey(SDLK_s);
	DOWN.m_pressed = false;
	DOWN.m_cPressed = false;
	DOWN.m_axis = SDL_CONTROLLER_AXIS_LEFTY;
	DOWN.m_direction = 1;
	DOWN.m_mappedButtons.push_back(SDL_CONTROLLER_BUTTON_DPAD_DOWN);
	m_inputs.push_back(DOWN);
	///
	InputButton LEFT;
	LEFT.SetInput(LEFT_BUTTON);
	LEFT.AddKey(SDLK_a);
	LEFT.m_pressed = false;
	LEFT.m_cPressed = false;
	LEFT.m_axis = SDL_CONTROLLER_AXIS_LEFTX;
	LEFT.m_direction = -1;
	LEFT.m_mappedButtons.push_back(SDL_CONTROLLER_BUTTON_DPAD_LEFT);
	m_inputs.push_back(LEFT);
	///
	InputButton RIGHT;
	RIGHT.SetInput(RIGHT_BUTTON);
	RIGHT.AddKey(SDLK_d);
	RIGHT.m_pressed = false;
	RIGHT.m_cPressed = false;
	RIGHT.m_axis = SDL_CONTROLLER_AXIS_LEFTX;
	RIGHT.m_direction = 1;
	RIGHT.m_mappedButtons.push_back(SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
	m_inputs.push_back(RIGHT);
	///

	///
	InputButton RUP;
	RUP.SetInput(RUP_BUTTON);
	RUP.AddKey(SDLK_8);
	RUP.m_pressed = false;
	RUP.m_cPressed = false;
	RUP.m_axis = SDL_CONTROLLER_AXIS_RIGHTY;
	RUP.m_direction = -1;
	m_inputs.push_back(RUP);
	///
	InputButton RDOWN;
	RDOWN.SetInput(RDOWN_BUTTON);
	RDOWN.AddKey(SDLK_2);
	RDOWN.m_pressed = false;
	RDOWN.m_cPressed = false;
	RDOWN.m_axis = SDL_CONTROLLER_AXIS_RIGHTY;
	RDOWN.m_direction = 1;
	m_inputs.push_back(RDOWN);
	///
	InputButton RLEFT;
	RLEFT.SetInput(RLEFT_BUTTON);
	RLEFT.AddKey(SDLK_4);
	RLEFT.m_pressed = false;
	RLEFT.m_cPressed = false;
	RLEFT.m_axis = SDL_CONTROLLER_AXIS_RIGHTX;
	RLEFT.m_direction = -1;
	m_inputs.push_back(RLEFT);
	///
	InputButton RRIGHT;
	RRIGHT.SetInput(RRIGHT_BUTTON);
	RRIGHT.AddKey(SDLK_6);
	RRIGHT.m_pressed = false;
	RRIGHT.m_cPressed = false;
	RRIGHT.m_axis = SDL_CONTROLLER_AXIS_RIGHTX;
	RRIGHT.m_direction = 1;
	m_inputs.push_back(RRIGHT);
	///


	InputButton RB;
	RB.SetInput(RB_BUTTON);
	RB.AddKey(SDLK_e);
	RB.m_pressed = false;
	RB.m_cPressed = false;
	RB.m_axis = -1;
	RB.m_direction = -1;
	RB.m_mappedButtons.push_back(SDL_CONTROLLER_BUTTON_RIGHTSHOULDER);
	m_inputs.push_back(RB);
	///
	InputButton LB;
	LB.SetInput(LB_BUTTON);
	LB.AddKey(SDLK_q);
	LB.m_pressed = false;
	LB.m_cPressed = false;
	LB.m_axis = -1;
	LB.m_direction = 1;
	LB.m_mappedButtons.push_back(SDL_CONTROLLER_BUTTON_LEFTSHOULDER);
	m_inputs.push_back(LB);
	///
	InputButton RT;
	RT.SetInput(RT_BUTTON);
	RT.AddKey(SDLK_f);
	RT.m_pressed = false;
	RT.m_cPressed = false;
	RT.m_axis = SDL_CONTROLLER_AXIS_TRIGGERRIGHT;
	RT.m_direction = 1;
	m_inputs.push_back(RB);
	///
	InputButton LT;
	LT.SetInput(LT_BUTTON);
	LT.AddKey(SDLK_r);
	LT.m_pressed = false;
	LT.m_cPressed = false;
	LT.m_axis = SDL_CONTROLLER_AXIS_TRIGGERLEFT;
	LT.m_direction = 1;
	m_inputs.push_back(LB);

	///
	InputButton START;
	START.SetInput(X_BUTTON);
	START.AddKey(SDLK_RETURN);
	START.m_pressed = false;
	START.m_cPressed = false;
	START.m_axis = -1;
	START.m_mappedButtons.push_back(SDL_CONTROLLER_BUTTON_START);
	m_inputs.push_back(START);
	///
	InputButton SELECT;
	SELECT.SetInput(SELECT_BUTTON);
	SELECT.AddKey(SDLK_SPACE);
	SELECT.m_pressed = false;
	SELECT.m_cPressed = false;
	SELECT.m_axis = -1;
	SELECT.m_mappedButtons.push_back(SDL_CONTROLLER_BUTTON_BACK);
	m_inputs.push_back(SELECT);
	//

	ev = { 0 };
	m_lastkey = NULL;

	///set up the joypads
	int attachedJoysticks = SDL_NumJoysticks();
	int cIndex = 0;
	for (int pad = 0; pad < attachedJoysticks; pad++)
	{
		if (!SDL_IsGameController(pad)) //if this isn't a game pad, we want to skip it
		{
			continue;
		}
		if (cIndex >= MAX_CONTROLLERS) //if we have already attached 4 gamepads
		{
			break; //we no longer need to add any
		}
		controllerConnected = true;
		ControllerHandles[cIndex] = SDL_GameControllerOpen(pad); //add the controller to our list of controllers
		cIndex++;
	}

}

Keyboard::~Keyboard()
{
	if (controllerConnected)
	{
		for (int ControllerIndex = 0; ControllerIndex < MAX_CONTROLLERS; ++ControllerIndex)
		{
			if (ControllerHandles[ControllerIndex])
			{
				SDL_GameControllerClose(ControllerHandles[ControllerIndex]);
			}
		}
	}
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
			bool jp = false;
			bool bp = false;

			if (ev.type == SDL_QUIT)
			{
				m_quit = true;
			}

			kp = KeyPress(i);
			if (kp == false)
			{
				mp = MousePress(i);
			}
			if (controllerConnected)
			{
				if (kp == false && mp == false)
				{
					jp = AxisPress(i);
				}
				if (kp == false && mp == false && jp == false)
				{
					bp = ButtonPress(i);
				}
			}
		}
	}
}


bool Keyboard::KeyPress(int i)
{
	bool kp = false;
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
	return kp;
}

bool Keyboard::MousePress(int i) 
{
	bool mp = false;
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
	return mp;
}

bool Keyboard::ButtonPress(int i)
{
	bool bp = false;
	if (controllerConnected)
	{
		if (ControllerHandles[0] != 0 && SDL_GameControllerGetAttached(ControllerHandles[0]))
		{

			for (unsigned int key = 0; key < m_inputs[i].m_mappedButtons.size(); key++)
			{
				//m_inputs[i].m_pressed = SDL_GameControllerGetButton(ControllerHandles[0], m_inputs[i].m_mappedButtons[key]);
				if (SDL_GameControllerGetButton(ControllerHandles[0], m_inputs[i].m_mappedButtons[key])) //what key has been pressed?
				{
					bp = true;
					m_inputs[i].m_cPressed = true;
					break;
				}
				else
				{
					bp = false;
					m_inputs[i].m_cPressed = false;
				}
			}
		}
	}
	return bp;
}

bool Keyboard::AxisPress(int i)
{
	bool jp = false;
	if (controllerConnected)
	{
		if (ControllerHandles[0] != 0 && SDL_GameControllerGetAttached(ControllerHandles[0]))
		{
			if (m_inputs[i].m_axis >= 0)
			{
				if (SDL_GameControllerGetAxis(ControllerHandles[0], (SDL_GameControllerAxis)m_inputs[i].m_axis) > JOYSTICK_DEAD_ZONE && m_inputs[i].m_direction == 1) //what key has been pressed?
				{
					m_inputs[i].m_cPressed = true;
					jp = true;
				}
				else if (SDL_GameControllerGetAxis(ControllerHandles[0], (SDL_GameControllerAxis)m_inputs[i].m_axis) < -JOYSTICK_DEAD_ZONE && m_inputs[i].m_direction == -1) //what key has been pressed?
				{
					//std::cout << "Axis: " << SDL_GameControllerGetAxis(ControllerHandles[0], (SDL_GameControllerAxis)m_inputs[i].m_axis) << std::endl;
					m_inputs[i].m_cPressed = true;
					jp = true;
				}
				else if (SDL_GameControllerGetAxis(ControllerHandles[0], (SDL_GameControllerAxis)m_inputs[i].m_axis) > 5 && ((SDL_GameControllerAxis)m_inputs[i].m_axis == SDL_CONTROLLER_AXIS_TRIGGERRIGHT || (SDL_GameControllerAxis)m_inputs[i].m_axis == SDL_CONTROLLER_AXIS_TRIGGERLEFT)) //what key has been pressed?
				{
					//std::cout << "Axis: " << SDL_GameControllerGetAxis(ControllerHandles[0], (SDL_GameControllerAxis)m_inputs[i].m_axis) << std::endl;
					m_inputs[i].m_cPressed = true;
					jp = true;
				}
				else
				{
					m_inputs[i].m_cPressed = false;
					jp = false;
				}
			}
		}
	}
	return jp;
}

bool Keyboard::Input(INPUTACTION _type) //has the key been pressed?
{
	for (unsigned int i = 0; i < m_inputs.size(); i++)
	{
		if (m_inputs[i].m_action == _type)
		{
			return m_inputs[i].m_pressed || m_inputs[i].m_cPressed;
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

int Keyboard::ReturnButton()
{
	if (controllerConnected) 
	{
		int index = 0;
		if (ControllerHandles[index] != 0 && SDL_GameControllerGetAttached(ControllerHandles[index]))
		{
			if (SDL_GameControllerGetButton(ControllerHandles[index], SDL_CONTROLLER_BUTTON_DPAD_UP))
				return SDL_CONTROLLER_BUTTON_DPAD_UP;
			if (SDL_GameControllerGetButton(ControllerHandles[index], SDL_CONTROLLER_BUTTON_DPAD_DOWN))
				return SDL_CONTROLLER_BUTTON_DPAD_DOWN;
			if (SDL_GameControllerGetButton(ControllerHandles[index], SDL_CONTROLLER_BUTTON_DPAD_LEFT))
				return SDL_CONTROLLER_BUTTON_DPAD_LEFT;
			if (SDL_GameControllerGetButton(ControllerHandles[index], SDL_CONTROLLER_BUTTON_DPAD_RIGHT))
				return SDL_CONTROLLER_BUTTON_DPAD_RIGHT;
			if (SDL_GameControllerGetButton(ControllerHandles[index], SDL_CONTROLLER_BUTTON_START))
				return SDL_CONTROLLER_BUTTON_START;
			if (SDL_GameControllerGetButton(ControllerHandles[index], SDL_CONTROLLER_BUTTON_BACK))
				return SDL_CONTROLLER_BUTTON_BACK;
			if (SDL_GameControllerGetButton(ControllerHandles[index], SDL_CONTROLLER_BUTTON_LEFTSHOULDER))
				return SDL_CONTROLLER_BUTTON_LEFTSHOULDER;
			if (SDL_GameControllerGetButton(ControllerHandles[index], SDL_CONTROLLER_BUTTON_RIGHTSHOULDER))
				return SDL_CONTROLLER_BUTTON_RIGHTSHOULDER;
			if (SDL_GameControllerGetButton(ControllerHandles[index], SDL_CONTROLLER_BUTTON_A))
				return SDL_CONTROLLER_BUTTON_A;
			if (SDL_GameControllerGetButton(ControllerHandles[index], SDL_CONTROLLER_BUTTON_B))
				return SDL_CONTROLLER_BUTTON_B;
			if (SDL_GameControllerGetButton(ControllerHandles[index], SDL_CONTROLLER_BUTTON_X))
				return SDL_CONTROLLER_BUTTON_X;
			if (SDL_GameControllerGetButton(ControllerHandles[index], SDL_CONTROLLER_BUTTON_Y))
				return SDL_CONTROLLER_BUTTON_Y;
		}
		else
		{
			return -1;
		}
	}
	return -1;
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
							//	m_inputs[u].m_mappedKeys.clear();
							//	m_inputs[u].m_mappedKeys = oldKeys;
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

bool Keyboard::ReBindButton(INPUTACTION _type, int _newKey)
{
	if (controllerConnected)
	{//controller keys
		if (_newKey != -1)
		{
			for (unsigned int i = 0; i < m_inputs.size(); i++)
			{
				if (m_inputs[i].m_action == _type)
				{
					for (unsigned int u = 0; u < m_inputs.size(); u++)
					{
						if (m_inputs[u].m_action != m_inputs[i].m_action)
						{
							std::vector<SDL_GameControllerButton> _oldButtons = m_inputs[i].m_mappedButtons;
							for (unsigned int k = 0; k < m_inputs[u].m_mappedButtons.size(); k++)
							{
								if (m_inputs[u].m_mappedButtons[k] == (SDL_GameControllerButton)_newKey)
								{
									//m_inputs[u].m_mappedButtons.erase(m_inputs[u].m_mappedButtons.begin() + k);
									m_inputs[u].m_mappedButtons.clear();
									m_inputs[u].m_mappedButtons = _oldButtons;
								}
							}
						}
					}
					m_inputs[i].m_mappedButtons.clear();
					m_inputs[i].m_mappedButtons.push_back((SDL_GameControllerButton)_newKey);
					return true;
				}
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
			if (m_inputs[i].m_cPressed)
			{
				m_inputs[i].m_cPressed = false;
				return true;
			}
		}
	}
	return false;
}