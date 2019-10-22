#ifndef  __BUTTON__
#define __BUTTON__

/*
Se creo una Arquitectura basada en componenetes para tener entidades mas independientes,
y que estas entidades esten definidas por los componenetes que tengan y puedan ser lo flexibles
que el programador quiera. Es decir, cada entidad puede tener cualquier componente
*/

#include "Component2.h"
#include "../InputManager/InputManager2.h"
#include <functional>

class CButton : public CComponent2, public CInputManager2::IListener
{
public:
	CButton(CEntity2 * pEntity, std::function<void(CButton*)> callback, char key);
	CButton(CEntity2 * pEntity, std::function<void(CButton*)> callback, bool bUseLeftButton, int higherLimitX, int lowerLimitX, int higherLimitY, int lowerLimitY);

	~CButton();

	virtual void Update(float fDelta) {};

	virtual void ManageEvent(TEvent* pEvent) override;

private:
	std::function<void(CButton *)> m_callback;
	char m_ckey;
	bool m_bUseLeftButton;
	int m_iHigherLimitX;
	int m_iLowerLimitX;
	int m_iHigherLimitY;
	int m_iLowerLimitY;
};

#endif


