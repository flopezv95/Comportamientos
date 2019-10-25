#pragma once
#include <stdint.h>

class AudioBuffer
{
public:
	~AudioBuffer();
	static AudioBuffer*	load(const char* filename);
	uint32_t			getAlBuffer() const;

private:
	AudioBuffer(unsigned int format, void*data, int size, int freq);
	uint32_t buffer;
	unsigned int format;
	void*data;
	int size;
	int freq;
};
