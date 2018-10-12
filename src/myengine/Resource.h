#pragma once
#include <string>
#include <memory>

class Resource
{
public:
	std::string GetPath() { return m_path; }
	bool TimerFinished() { if (m_timer > 10.0f) return true; else return false; }

	void AddToTimer(float _deltaTime) { m_timer += _deltaTime; }
	void ResetTimer() { m_timer = 0; }

protected:
	std::string m_path;
	float m_timer;
};