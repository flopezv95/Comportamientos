#ifndef __CSPRITE__
#define __CSPRITE__

/*Esta clase se creo para tener de forma separada e independiente
la manipulacion de los sprite de las entidades del juego
*/

class Sprite;
class Image;
class CGameSprite
{
public:
	CGameSprite(const char *psz_image_file);
	~CGameSprite();

	void SetPosition	(float x, float y, float z);
	void SetScale		(float sx, float sy);
	void SetRotation(float r);
	Sprite * GetEngineSprite() { return m_pSprite; }

private:


	Sprite *	m_pSprite;
	Image *		m_pImage;

	friend class CGraphics;
};

#endif
