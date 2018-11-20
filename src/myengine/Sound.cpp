#include "Sound.h"
#include <AL/al.h>
#include <vorbis/vorbisfile.h>

#include <iostream>
#include <vector>

struct Sample
{
	//buffer
	ALuint id;

	~Sample()
	{
		//clean up 
		alDeleteBuffers(1, &id);
	}

	void LoadOgg(std::string _file, std::vector<char> &buffer, ALenum &format, ALsizei &freq)
	{
		int endian = 0;
		int bitStream = 0;
		long bytes = 0;
		char array[2048] = { 0 };
		vorbis_info *pInfo = NULL;
		OggVorbis_File oggFile = { 0 };

		//Open the file from the filestring, and put it in the oggVorbis file
		if (ov_fopen(_file.c_str(), &oggFile) != 0)
		{
			std::cout << "Uh oh, failed to open: " << _file << " in Sound.cpp" << std::endl;
			throw std::exception();
		}

		// Extract information from the file header
		pInfo = ov_info(&oggFile, -1);
		// Record the format required by OpenAL
		if (pInfo->channels == 1)
		{
			format = AL_FORMAT_MONO16;
		}
		else
		{
			format = AL_FORMAT_STEREO16;
		}
		freq = pInfo->rate;
		// Keep reading bytes from the file to populate the output buffer
		while (true)
		{
			// Read bytes into temporary array
			bytes = ov_read(&oggFile, array, 2048, endian, 2, 1, &bitStream);

			if (bytes < 0)
			{
				ov_clear(&oggFile);
				std::cout << "Failed to decode: " << _file << " in Sound.cpp" << std::endl;
				throw std::exception();
			}
			else if (bytes == 0)
			{
				break;
			}

			// Copy from temporary array into output buffer
			buffer.insert(buffer.end(), array, array + bytes);
		}

		// Clean up and close the file
		ov_clear(&oggFile);
	}
};

Sound::Sound() { }

Sound::Sound(std::string path)
{
	Load(path);
}

std::shared_ptr<Sound> Sound::Load(std::string path)
{
	std::shared_ptr<Sound> rtn = std::shared_ptr<Sound>(new Sound());
	rtn->imp = std::make_shared<Sample>();
	rtn->m_timer = 0;
	rtn->m_path = path;

	ALenum format = 0;
	ALsizei freq = 0;
	std::vector<char> bufferData;

	alGenBuffers(1, &rtn->imp->id);

	rtn->imp->LoadOgg(path, bufferData, format, freq);

	alBufferData(rtn->imp->id, format, &bufferData[0],
		static_cast<ALsizei>(bufferData.size()), freq);

	return rtn;
}

void Sound::Play()
{
	std::cout << "Sound Played";
	ALuint sid = 0;
	alGenSources(1, &sid);
	alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);
	alSource3f(sid, AL_POSITION, 0.0f, 0.0f, 0.0f);
	alSourcei(sid, AL_BUFFER, imp->id);
	alSourcePlay(sid);

	//audioSources.push_back(sid);
}

void Sound::PlayLoop()
{
	alSourcei(imp->id, AL_LOOPING, 1);
	std::cout << "Sound Played Loop";
	ALuint sid = 0;
	alGenSources(1, &sid);
	alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);
	alSource3f(sid, AL_POSITION, 0.0f, 0.0f, 0.0f);
	alSourcei(sid, AL_BUFFER, imp->id);
	alSourcePlay(sid);

}

void Sound::StopLooping()
{ 
	alSourcei(imp->id, AL_LOOPING, 0);
	alSourceStop(imp->id);
}


void Sound::Stop()
{
	alSourceStop(imp->id);
}

void Sound::Play(float vol, float varMin, float varMax)
{
	//For better rand resolution
	varMin *= 1000.0f;
	varMax *= 1000.0f;
	float variance = (std::rand() % ((int)varMin + 1 - (int)varMax) + (int)varMin) / 1000.0f;
	//return std::rand() % (max + 1 - min) + min;
	ALuint sid = 0;
	alGenSources(1, &sid);
	alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);
	alSource3f(sid, AL_POSITION, 0.0f, 0.0f, 0.0f);
	alSourcei(sid, AL_BUFFER, imp->id);
	alSourcef(sid, AL_PITCH, variance);
	alSourcef(sid, AL_GAIN, vol);
	alSourcePlay(sid);

	//audioSources.push_back(sid);
}
