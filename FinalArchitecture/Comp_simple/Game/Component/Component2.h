#ifndef __COMPONENT2__
#define __COMPONENT2__

/*
Se creo una Arquitectura basada en componenetes para tener entidades mas independientes,
y que estas entidades esten definidas por los componenetes que tengan y puedan ser lo flexibles
que el programador quiera. Es decir, cada entidad puede tener cualquier componente.

Por esta razon se creo una clase base que es para los componenetes que tiene un enumerado
con todos los componentes disponibles, ademas tiene un update() para actualizar el estado
de cada componenetes y un ManageMessage() para poder manejar mensajes entre los componenetes
de una entidad.
*/

#include "../ManageMessages/Message.h"
class CEntity2;

class CComponent2
{
public:

	enum TType
	{
		ETransform,
		EText,
		EAnimator,
		EButton,
		EVelocity,
		ECollision,
		EGameOver,
		ELimitMovement,
	};

	CComponent2(TType type, CEntity2 * pEntity) { m_type = type; m_pEntity = pEntity; }

	virtual ~CComponent2() {};
	virtual void Update(float fDelta) = 0;
	virtual void ManageMessage(TMessage * pmessage) {};

	TType GetType() const { return m_type; }

protected:
	CEntity2 * GetEntity() const { return m_pEntity; }
private:

	TType m_type;
	CEntity2 * m_pEntity;
};

#endif
