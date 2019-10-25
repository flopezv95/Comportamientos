#include <iostream>
#include <fstream>
#include <cstring>
#include "../lib/openal/AL/al.h"
#include "../lib/openal/AL/alc.h"
#include "../include/Audiobuffer.h"
#include <string.h>
//#include "stb_vorbis.c" //Para la primera pparte de la practica hay que descomentar esto y no agregar el audioStream->Crea conflicto

char* loadWav(const char* fn, int& chan, int& samplerate, int& bps, int& size);
bool isWav(const char* fn);

AudioBuffer::AudioBuffer(unsigned int format, void*data, int size, int freq)
{
	alGenBuffers(1, &this->buffer);
	alBufferData(this->buffer, format, data, size, freq);
	this->format = format;
	this->data = data;
	this->freq = freq;
}

AudioBuffer::~AudioBuffer()
{
	alDeleteBuffers(1, &this->buffer);
}

AudioBuffer* AudioBuffer::load(const char* filename)
{
	int channel;
	int sampleRates;
	int bps;
	int size;
	bool isWavFile = isWav(filename);
	if (isWavFile)
	{
		char*data = loadWav(filename, channel, sampleRates, bps, size);

		unsigned int format = 0;
		if (channel == 1)
		{
			if (bps == 8)
			{
				format = AL_FORMAT_MONO8;
			}
			else if (bps == 16)
			{
				format = AL_FORMAT_MONO16;
			}
		}
		else
		{
			if (bps == 8)
			{
				format = AL_FORMAT_STEREO8;
			}
			else if (bps == 16)
			{
				format = AL_FORMAT_STEREO16;
			}
		}

		AudioBuffer* Audio = new AudioBuffer(format, reinterpret_cast<void*>(data), size, sampleRates);

		return Audio;
	}
	else
	{
		return nullptr;
	}
}

uint32_t AudioBuffer::getAlBuffer() const
{
	return this->buffer;
}

char* loadWav(const char* fn, int& chan, int& samplerate, int& bps, int& size)
{
	char buffer[4];
	bool end = false;
	std::ifstream in(fn, std::ios::binary);
	in.read(buffer, 4);
	if (strncmp(buffer, "RIFF", 4) != 0)
	{
		std::cout << "this is not a valid WAVE file" << std::endl;
		return NULL;
	}
	in.read(buffer, 4);
	in.read(buffer, 4);      //WAVE
	in.read(buffer, 4);      //fmt
	in.read(buffer, 4);      //16
	in.read(buffer, 2);      //1
	in.read(buffer, 2);
	chan = ((static_cast<int>(buffer[3]) & 0x000000ff) << 32) + ((static_cast<int>(buffer[2]) & 0x000000ff) << 16) + ((static_cast<int>(buffer[1]) & 0x000000ff) << 8) + ((static_cast<int>(buffer[0]) & 0x000000ff) << 0);
	in.read(buffer, 4);
	samplerate = ((static_cast<int>(buffer[3]) & 0x000000ff) << 32) + ((static_cast<int>(buffer[2]) & 0x000000ff) << 16) + ((static_cast<int>(buffer[1]) & 0x000000ff) << 8) + ((static_cast<int>(buffer[0]) & 0x000000ff) << 0);
	in.read(buffer, 4);
	in.read(buffer, 2);
	in.read(buffer, 2);
	bps = ((static_cast<int>(buffer[3]) & 0x000000ff) << 32) + ((static_cast<int>(buffer[2]) & 0x000000ff) << 16) + ((static_cast<int>(buffer[1]) & 0x000000ff) << 8) + ((static_cast<int>(buffer[0]) & 0x000000ff) << 0);
	in.read(buffer, 1);
	while (!end)
	{

		if (strncmp(buffer, "d", 1) == 0)
		{
			in.read(buffer, 1);
			if (strncmp(buffer, "a", 1) == 0)
			{
				in.read(buffer, 1);

				if (strncmp(buffer, "t", 1) == 0)
				{
					in.read(buffer, 1);
					if (strncmp(buffer, "a", 1) == 0)
					{
						end = true;
					}
				}
			}
		}
		else
			in.read(buffer, 1);
	}
	in.read(buffer, 4);
	size = ((static_cast<int>(buffer[3]) & 0x000000ff) << 32) + ((static_cast<int>(buffer[2]) & 0x000000ff) << 16) + ((static_cast<int>(buffer[1]) & 0x000000ff) << 8) + ((static_cast<int>(buffer[0]) & 0x000000ff) << 0);
	char* data = new char[size];
	in.read(data, size);
	return data;
}

bool isWav(const char* fn)
{
	char fileName[50];
	strcpy_s(fileName, fn);
	for (unsigned int i = 0; i <= strlen(fileName); i++) {
		if (fileName[i] == '.')
		{
			if (fileName[i + 1] == 'w')
			{
				if (fileName[i + 2] == 'a')
				{
					if (fileName[i + 3] == 'v')
					{
						return true;
					}
				}
			}
		}
	}
	return false;
}