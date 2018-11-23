#pragma once
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_gamecontroller.h>
#define MAX_CONTROLLERS 1

/*!
Instead of any keyboard press, the user needs to set actions via INPUTACTION buttons.
These map to a standard game controller, which can be used in this engine.
Keys are initially bound, but cna be rebound during runtime by using the ReBind function for keyboard and ReBindButton for controllers.
Currently, gamepads must be connected before the program starts.
*/

enum INPUTACTION
{
	A_BUTTON, B_BUTTON, X_BUTTON, Y_BUTTON, 
	UP_BUTTON, DOWN_BUTTON, LEFT_BUTTON, RIGHT_BUTTON, 
	RUP_BUTTON, RDOWN_BUTTON, RLEFT_BUTTON, RRIGHT_BUTTON,
	RB_BUTTON, LB_BUTTON, RT_BUTTON, LT_BUTTON, 
	START_BUTTON, SELECT_BUTTON
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
	std::vector<SDL_GameControllerButton> m_mappedButtons;

	bool m_pressed;
	bool m_cPressed;
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
	int ReturnButton();
	bool ReBind(INPUTACTION _type, SDL_Keycode _newKey);
	bool ReBindButton(INPUTACTION _type, int _newKey);
	bool PressOnce(INPUTACTION _type);

	bool Quit() { return m_quit; }

private:
	bool m_quit;
	bool KeyPress(int i);
	bool MousePress(int i);
	bool ButtonPress(int i);
	bool AxisPress(int i);

	bool controllerConnected;
	std::vector<InputButton> m_inputs;
	SDL_Event ev;
	SDL_Keycode m_lastkey;
	SDL_GameControllerButton m_lastButton;
	SDL_GameController *ControllerHandles[MAX_CONTROLLERS];
};