#pragma once
#include "AudioBuffer.h"

class AudioSource
{
public:
	//Funcion para crear una fuente a partir de un fichero .wav
	static AudioSource* load(const char* filename);
	//Funcion para crear una fuente a partir de un buffer
	AudioSource(AudioBuffer* buffer);
	//Constructor para cuando se hace el streaming
	AudioSource(bool isStreaming);
	~AudioSource();
	void setPitch(float pitch);
	void setGain(float gain);
	void setLooping(bool loop);
	void setPosition(float x, float y, float z);
	void setVelocity(float x, float y, float z);
	//Funcion que devuelve el numero de la fuente creada
	unsigned int GetSource();

	void play();
	void stop();
	void pause();
	bool isPlaying() const;


private:
	unsigned int source;
	float pitch;
	float gain;
	float poisition_x1, poisition_y1, poisition_z1;
	float velocity_x1, velocity_y1, velocity_z1;
	bool loop;
	//Variable miembro que  nos indica si vamos a ser o no streaming
	bool isStreaming;
};

