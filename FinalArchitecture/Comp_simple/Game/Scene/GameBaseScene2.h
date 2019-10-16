#ifndef  __GAMEBASESCENE2__
#define __GAMEBASESCENE2__

/*
Para el juego, este se separo en diferentes escenas que son controladas por la clase SceneManager
Cada escena tiene sus entidades, es decir cada esa esta conformada por un numero finito de entidades.

Cabe destacar que para que una imagen se perciba y se dibuje en el mundo esta tiene que estar 
en una escena.

Se creo una escena base que tiene una funcion Update para la logica de los componenetes,
y funciones para agregar o eliminar entidades de la escena
*/

#include <vector>


class CEntity2;
class TEvent;
class TMessage;

class CGameBaseScene2
{
public:

	enum TScene
	{
		EMainMenuScene,
		EPlayGameScene,
		ELostGameScene,
		EInvalid,
	};

	CGameBaseScene2(TScene type);
	~CGameBaseScene2();
	virtual void  Update(float fDelta);
	virtual int Init();
	virtual void  ManageMessage(TMessage *pMessageInfo) {};
	TScene GetType();

protected:
	void AddEntity(CEntity2 *p);
	void RemoveEntity(CEntity2 *p);

private:
	std::vector<CEntity2*> m_entities;
	TScene m_myScene;
};

#endif
