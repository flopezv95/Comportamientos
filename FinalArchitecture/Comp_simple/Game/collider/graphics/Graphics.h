#ifndef __CGRAPHICS__
#define __CGRAPHICS__

#include <vector>
#include "../../../include/string.h"
/*
En esta clase se manipula el render del juego, 
aqui llegan los componenetes de la entidad que se deben dibujar.
¡Se escogio tenerlo de esta gorma para tener separada la parte de logica de la parte de render!
*/
class Scene;
class CGameSprite;
class CGameText;
class Font;

typedef struct {
	Font* myFont;
	String textToWrite;
	double xPosition;
	double yPosition;
}Text;

class CGraphics
{
public:
	CGraphics();
	~CGraphics();

	void render();

	CGameSprite *AddSprite(const char *psz_file);
	void RemoveSprite(CGameSprite  *sprite);
	void AddText(Text* myFont);
	void RemoveText(Text* myFont);

	float GetWidth();
	float GetHeight();

private:
	Scene * m_pScene;
	std::vector<Text*> m_myFonts;
};

#endif