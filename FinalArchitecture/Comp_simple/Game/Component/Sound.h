#ifndef __SOUND__
#define __SOUND__

/*
Se creo una Arquitectura basada en componentes para tener entidades mas independientes,
y que estas entidades esten definidas por los componenetes que tengan y puedan ser lo flexibles
que el programador quiera. Es decir, cada entidad puede tener cualquier componente
*/
#include "../../lib/openal/AL/al.h"
#include "../../lib/openal/AL/alc.h"
#include "Component2.h"

class CEntity2;
class AudioSource;


class CSound : public CComponent2
{
public:
	CSound(CEntity2 * pEntity, const char * psz_image_file);
	~CSound();
	virtual void ManageMessage(TMessage * pmessage);
	virtual void Update(float fDelta);
private:
	AudioSource* m_source;
	ALCdevice* m_myDevice;
	ALCcontext * m_context;
};


#endif