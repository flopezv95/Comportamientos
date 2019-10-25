#pragma once
#include "AudioSource.h"
#include <vector>
#include <array>
#ifdef STB_VORBIS //Ver si la libreria se esta usando
#include "../lib/stb_vorbis.c"
#else
#endif 

class AudioStream {
public:
	static AudioStream* load(const char* filename, AudioSource* source);
	~AudioStream();

	void setLooping(bool looping) { mShouldLoop = looping; }

	static void updateAll();
	//Agregue una funcion extra que me permite saber el numero de la fuente que esta relacionada con el streaming
	AudioSource*GetSource();
protected:
	//La definicion y la declaracion del constructor tambien cambia un poco para hacer el codigo mas entendible
	AudioStream(const char* filename, AudioSource* source);
	void update();
	bool stream(unsigned int buffer);

private:

	static std::vector<AudioStream*> mStreams;
	AudioSource*		mSource;
#ifdef STB_VORBIS //Ver si la libreria se esta usando
	stb_vorbis*			mStream;
	stb_vorbis_info		mInfo;
#else
#endif // #define  STB_TRUETYPE_IMPLEMENTATION
	unsigned int mBuffers[2];
	size_t bufferSize;
	unsigned int mFormat;
	size_t			mSamplesLeft;
	bool				mShouldLoop;
};
