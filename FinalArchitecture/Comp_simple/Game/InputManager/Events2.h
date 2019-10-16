#ifndef __EVENTS2__
#define __EVENTS2__

/*
Para comunicar las entradas del mundo exterior al juego se creo un input manager que se
encarga de percibir cualquier input del teclado o raton en el juego y este se lo comunica
a la clase Tevent, el cual mande el mensaje de la position del raton, si el boton izquierdo 
del raton fue pulsado o cualquier teclas fue pulsada
*/

//***************************************************************************************
//TEvent
//***************************************************************************************

class TEvent
{
public:

	enum TType
	{
		EMouseDownLeft,
		EKeyboardDown, 
		EMousePosition
	};
	TEvent(TType type) { m_type = type; }
    TType GetType() const { return m_type;}
private:
	TType m_type;
};




//***************************************************************************************
//TEventMouse
//***************************************************************************************


class TEventMouseDownLeft : public TEvent
{
public:
	TEventMouseDownLeft(int x, int y) : TEvent (EMouseDownLeft)
	{ 
		m_ix = x; 
		m_iy = y; 
	}

	int Getx() { return m_ix; }
	int Gety() { return m_iy; }
private:
	int m_ix;
	int m_iy;
};

//***************************************************************************************
//TEventKeyboard
//***************************************************************************************


class TEventKeyboardDown : public TEvent
{
public:
	TEventKeyboardDown(unsigned int key) : TEvent(EKeyboardDown)
	{
		m_ikey = key;
	}

	int Getkey() { return m_ikey; }
private:
	unsigned int m_ikey;
};

//*********************************************************************************************
//
//**********************************************************************************************


#endif