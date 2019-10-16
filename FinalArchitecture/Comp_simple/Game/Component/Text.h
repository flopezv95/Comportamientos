#ifndef __TEXT__
#define __TEXT__

/*
Se creo una Arquitectura basada en componenetes para tener entidades mas independientes,
y que estas entidades esten definidas por los componenetes que tengan y puedan ser lo flexibles
que el programador quiera. Es decir, cada entidad puede tener cualquier componente
*/

#include "Component2.h"
#include "../../include\string.h"
#include "../collider/graphics/Graphics.h"

class CEntity2;
class Font;

class CText : public CComponent2
{
public:
	CText(CEntity2 * pEntity, const String & filename, const String & textToWrite,double x, double y);
	~CText();

	virtual void Update(float fDelta);
private:
	Font * m_pText;
	String m_string;
	Text * m_pmyText;
};


#endif

