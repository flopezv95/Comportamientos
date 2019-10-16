#ifndef __INPUTMANAGER2__
#define __INPUTMANAGER2__
#include <vector>


/*
Para comunicar las entradas del mundo exterior al juego se creo un input manager que se
encarga de percibir cualquier input del teclado o raton en el juego y este se lo comunica
a la clase Tevent, el cual mande el mensaje de la position del raton, si el boton izquierdo
del raton fue pulsado o cualquier teclas fue pulsada.

Esto permitira entonces, que el jugador pueda interactual con el juego y controlarlo.

Para poder recibir estos mensajes del inputManager, se debe registrar al IListener que
se encarga de manejar los mensajes del exterior
*/

class TEvent;

class CInputManager2
{
public:


	class IListener
	{
	public:
		virtual void ManageEvent(TEvent* pEvent) {};
	};

	CInputManager2();
	~CInputManager2();

	void injectMouseEvent(int ibutton, int iAction);
	void injectKeyboardEvent(int ikey, int iAction);

	void DeregisterToEvent(IListener * pObserver);
	void RegisterToEvent(IListener * pObserver);
	
	void Update();

private:
	std::vector<IListener*>m_listeners;
	std::vector<TEvent*>m_events;
};



#endif