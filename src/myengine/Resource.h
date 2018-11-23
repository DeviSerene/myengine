#pragma once
#include <string>
#include <memory>

/*!
Resource is a virtual class to be inherited by anything where the user wants to load resources from file. This can be OBJs, OGGs or images, but also shaders.
All resources have a path to the file, which is their identifier, and a timer. The timer ticks down when the object is out of scope, and will be deleted if it is unused for a certain time.
*/

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