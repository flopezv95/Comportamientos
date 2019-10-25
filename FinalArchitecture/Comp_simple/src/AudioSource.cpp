#include "../include/AudioSource.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include "../lib/openal/AL/al.h"
#include "../lib/openal/AL/alc.h"
#include "../include/Audiobuffer.h"
#include "../include/AudioStream.h"
#include <string.h>

AudioSource::AudioSource(AudioBuffer* buffer)
{
	alGenSources(1, &this->source);
	alSourcei(this->source, AL_BUFFER, buffer->getAlBuffer());
	alSourcef(this->source, AL_PITCH, 1);
	alSourcef(this->source, AL_GAIN, 1);
	alSource3f(this->source, AL_POSITION, 0, 0, 0);
	alSource3f(this->source, AL_VELOCITY, 0, 0, 0);
	this->isStreaming = false;
}
//Constructor para cuando se hace streaming de un fichero .wav
AudioSource::AudioSource(bool isStreaming)
{
	alGenSources(1, &this->source);
	alSourcef(this->source, AL_PITCH, 1);
	alSourcef(this->source, AL_GAIN, 1);
	alSource3f(this->source, AL_POSITION, 0, 0, 0);
	alSource3f(this->source, AL_VELOCITY, 0, 0, 0);
	this->isStreaming = isStreaming;
}

AudioSource::~AudioSource()
{
	alDeleteSources(1, &this->source);
}

AudioSource* AudioSource::load(const char* filename)
{
	AudioSource* audioSource=new AudioSource(true);
	AudioStream* myAudioStream = AudioStream::load(filename, audioSource);
	return myAudioStream->GetSource();
}

void AudioSource::setPitch(float newPitch)
{
	this->pitch = newPitch;
	alSourcef(this->source, AL_PITCH, this->pitch);
}

void AudioSource::setGain(float newGain)
{
	this->gain = newGain;
	alSourcef(this->source, AL_GAIN, this->gain);
}

void AudioSource::setPosition(float x, float y, float z)
{
	this->poisition_x1 = x;
	this->poisition_y1 = y;
	this->poisition_z1 = z;
	alSource3f(this->source, AL_POSITION, this->poisition_x1, this->poisition_y1, this->poisition_z1);
}

void AudioSource::setVelocity(float x, float y, float z)
{
	this->velocity_x1 = x;
	this->velocity_y1 = y;
	this->velocity_z1 = z;
	alSource3f(this->source, AL_VELOCITY, this->velocity_x1, this->velocity_y1, this->velocity_z1);
}

void AudioSource::setLooping(bool bIsloop)
{
	if (bIsloop)
	{
		this->loop = bIsloop;
	}
	else
	{
		this->loop = bIsloop;
		
	}
}

void AudioSource::play()
{
	if (this->loop && !this->isStreaming) //Aqui agregamos la condition si el looping se realiza aqui o en la funcion de streaming
	{
		alSourcei(this->source, AL_LOOPING, 1);
	}
	alSourcePlay(this->source);

}

void AudioSource::stop()
{
	alSourceStop(this->source);
}

void AudioSource::pause()
{
	alSourcePause(this->source);
}

bool AudioSource::isPlaying() const
{
	int isPlaying;
	alGetSourcei(this->source, AL_SOURCE_STATE, &isPlaying);
	if (isPlaying == AL_PLAYING)
	{
		return true;
	}
	else
	{
		return false;
	}
}

unsigned int AudioSource::GetSource()
{
	return this->source;
}