#pragma once
#include "Resource.h"
#include <memory>
#include <string>

struct Sample;

class Sound : public Resource 
{
public:
	Sound();
	Sound(std::string _path);
	static std::shared_ptr<Sound> Load(std::string _path);
	void Play();
	void PlayLoop();
	void StopLooping();
	void Stop();
	void Play(float _volume, float _varMin, float _varMax);
private:
	std::shared_ptr<Sample> imp;
};