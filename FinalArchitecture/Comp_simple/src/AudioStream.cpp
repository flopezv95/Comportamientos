#define  STB_VORBIS
#include "../include/AudioStream.h"
#include "../lib/openal/AL/al.h"
#include "../lib/openal/AL/alc.h"

std::vector<AudioStream*> AudioStream::mStreams;
//Declaracion del constructor de un streaming con su fuente asociada
AudioStream::AudioStream(const char* filename, AudioSource* source)
{
	int channel;
	this->mStream = stb_vorbis_open_filename(filename, nullptr, nullptr);
	this->mInfo = stb_vorbis_get_info(this->mStream);
	this->mSamplesLeft = (stb_vorbis_stream_length_in_samples(this->mStream))*(this->mInfo.channels);
	channel = this->mInfo.channels;
	if (channel == 1)
	{
		this->mFormat = AL_FORMAT_MONO16;
	}
	else
	{
		this->mFormat = AL_FORMAT_STEREO16;
	}
	this->mSource = source;
	this->mShouldLoop = true;
}

AudioStream::~AudioStream()
{
	for (unsigned i = 0; i < mStreams.size(); i++)
	{
		delete mStreams[i];
	}
}

AudioStream*AudioStream::load(const char* filename, AudioSource* source)
{
	AudioStream* audioStream=new AudioStream(filename, source);
	alGenBuffers(2, audioStream->mBuffers);
	audioStream->stream(audioStream->mBuffers[0]);
	audioStream->stream(audioStream->mBuffers[1]);
	alSourceQueueBuffers(audioStream->mSource->GetSource(), 2, audioStream->mBuffers);
	mStreams.push_back(audioStream);
	return audioStream;
}


bool AudioStream::stream(unsigned int buffer)
{
	bool ret = false;
	bool exit = false;
	const unsigned int bufferSize = 32768; // El tamaño de cada buffer se define aqui para poder cambiarlo si se desea
	short pcm[bufferSize];
	int  size = 0;
	int  result = 0;
	//En este bucle vems cuanto va a ser el tamaño del buffer que vamos a meter a la fuente
	while (size < bufferSize || !exit) {
		result = stb_vorbis_get_samples_short_interleaved(this->mStream, this->mInfo.channels, pcm + size, bufferSize - size);
		if (result > 0)
		{
			size += result * this->mInfo.channels;
		}
		else
		{
			exit = true;
		}
	}
	//Aqui hacemos el volcado de datos al buffer
	alBufferData(buffer, this->mFormat, pcm, size * sizeof(ALshort), this->mInfo.sample_rate);
	//Vemos cuantos datos nos faltan por leer
	this->mSamplesLeft = this->mSamplesLeft - size;
	//Aqui vemos si nos faltan datos por leer que sean mayores al buffersize
	if (this->mSamplesLeft< (bufferSize))
	{
		ret = false; //Si esto se cumple devolvemos false para inicializar de nuevo la lectura del archivo
	}
	else
	{
		ret = true; //Si aqun quedan datos seguimos recorriendo el fichero y llenando los buffers.
	}
	
	return ret;
}

void AudioStream::updateAll()
{
	for (unsigned i = 0; i < mStreams.size(); i++)
	{
		mStreams[i]->update();
	}
}

void AudioStream::update()
{
	ALint processed = 0;
	alGetSourcei(this->mSource->GetSource(), AL_BUFFERS_PROCESSED, &processed);
	//Mientras haya algun buffer reproduciendose, vamos a pasar al buffer siguiente o empezar de nuevo
	while (processed--)
	{
		ALuint buffer = 0;
		alSourceUnqueueBuffers(this->mSource->GetSource(), 1, &buffer); 
		if (this->stream(buffer))//Si aun quedan datos para leer, metemos ese nuevo buffer en la fuente
		{
			alSourceQueueBuffers(this->mSource->GetSource(), 1, &buffer);
		}
		else //Si no quedan datos para leer
		{
			if (mShouldLoop) //Si queremos que se repita el audio
			{
				stb_vorbis_seek_start(this->mStream); //Volvemos al principio del archivo
				this->mSamplesLeft = (stb_vorbis_stream_length_in_samples(this->mStream))*(this->mInfo.channels); //Volvemos a definir la cantidad de datos que queremos leer
				if (this->stream(buffer))//Cargamos el buufer
				{
					alSourceQueueBuffers(this->mSource->GetSource(), 1, &buffer);
				}
			}
		}
	}
}

AudioSource* AudioStream::GetSource()
{
	return this->mSource;
}