#include "../include/Listener.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include "../lib/openal/AL/al.h"
#include "../lib/openal/AL/alc.h"
#include "../include/Audiobuffer.h"
#include <string.h>

Listener::Listener() 
{
	alListener3f(AL_POSITION, 0, 0, 0);
	alListener3f(AL_ORIENTATION, 0, 0, 0);
	alListener3f(AL_VELOCITY, 0, 0, 0);
}

void Listener::setListenerOrientation(float x, float y, float z)
{
	alListener3f(AL_ORIENTATION, x, y, z);
}

void Listener::setListenerPosition(float x, float y, float z)
{
	alListener3f(AL_POSITION, x, y, z);
}

void Listener::setListenerVelocity(float x, float y, float z)
{
	alListener3f(AL_VELOCITY, x, y, z);
}