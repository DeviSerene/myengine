#pragma once
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_gamecontroller.h>
#define MAX_CONTROLLERS 1

enum INPUTACTION
{
	A_BUTTON, B_BUTTON, UP_BUTTON, DOWN_BUTTON, LEFT_BUTTON, RIGHT_BUTTON, RB_BUTTON, LB_BUTTON
};

struct InputButton
{
	void SetInput(INPUTACTION _action) { m_action = _action; }
	void AddKey(SDL_Keycode _key) { m_mappedKeys.push_back(_key); }
	void AddMouse(int _key) { m_mappedMouse.push_back(_key); }

	INPUTACTION m_action;
	std::vector<SDL_Keycode> m_mappedKeys;
	std::vector<int> m_mappedMouse;
	int m_axis;
	int m_direction;
	bool m_pressed;
};

class Keyboard
{
public:
	Keyboard();
	~Keyboard();

	void Poll();
	void Update();
	bool Input(INPUTACTION _type); //has the key been pressed?
	SDL_Keycode ReturnKeyCode();
	bool ReBind(INPUTACTION _type, SDL_Keycode _newKey);
	bool PressOnce(INPUTACTION _type);

private:
	std::vector<InputButton> m_inputs;
	SDL_Event ev;
	SDL_Keycode m_lastkey;
	SDL_GameController *ControllerHandles[MAX_CONTROLLERS];
};