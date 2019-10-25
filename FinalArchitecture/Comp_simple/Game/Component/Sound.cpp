#include "../../stdafx.h"
#include "Sound.h"
#include "../ManageMessages/Message.h"
#include "../collider/graphics/GameSprite.h"
#include "../collider/graphics/Graphics.h"
#include "../../include/Audiobuffer.h"
#include "../../include/AudioSource.h"
#include "../../include/AudioStream.h"
#include "../../include/Listener.h"
#include "../Entity/Entity2.h"

extern CGraphics * g_pGR2;
//****************************************************************************************
//
//****************************************************************************************
CSound::CSound(CEntity2 * pEntity, const char * psz_image_file) :CComponent2(EAnimator, pEntity)
{
	m_myDevice = alcOpenDevice(NULL);
	m_context = NULL;
	if (m_myDevice != NULL)
	{
		m_context = alcCreateContext(m_myDevice, NULL);
		alcMakeContextCurrent(m_context);
	}
	m_source = AudioSource::load(psz_image_file);
	Listener listener;
	m_source->play();
}
//****************************************************************************************
//
//****************************************************************************************
CSound::~CSound()
{
	m_context = alcGetCurrentContext();
	m_myDevice = alcGetContextsDevice(m_context);
	alcDestroyContext(m_context);
	alcCloseDevice(m_myDevice);
	SAFE_DELETE(m_source);
}
//****************************************************************************************
//
//****************************************************************************************
void CSound::Update(float fDelta)
{
	AudioStream::updateAll();
}
//****************************************************************************************
//
//****************************************************************************************
void CSound::ManageMessage(TMessage * pMessage)
{

}
