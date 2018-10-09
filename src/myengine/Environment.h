#pragma once

class Environment
{
public:
	Environment();
	~Environment();

	float GetDeltaTime() { return m_deltaTime; }

private:
	float m_deltaTime;
};