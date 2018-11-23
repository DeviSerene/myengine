#pragma once
#include "Resource.h"
#include <memory>
#include <string>
#include <AL/al.h>
#include <vorbis/vorbisfile.h>
#include "glm/glm.hpp"

struct Sample;

/*!
Sounds are able to be played in 3D space with a player(where the sound is coming from) and a Listener (likely the camera).
Background Music can be looped with the PlayLoop fuction.
*/

class Sound : public Resource 
{
public:
	Sound();
	~Sound();
	Sound(std::string _path);
	static std::shared_ptr<Sound> Load(std::string _path);
	void Play(glm::vec3 _player, glm::vec3 _listener);
	void Play();
	void PlayLoop();
	void StopLooping();
	void Stop();
	void Play(float _volume, float _varMin, float _varMax);
private:
	std::shared_ptr<Sample> imp;
	ALuint sid;
};