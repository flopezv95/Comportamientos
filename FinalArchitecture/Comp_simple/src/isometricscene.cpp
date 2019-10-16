#include "../stdafx.h"
#include "../include/isometricscene.h"
#include "../include/isometricmap.h"
#include "../include/isometricsprite.h"

IsometricScene::IsometricScene(IsometricMap* map, Image* imageBack, Image* imageFront) : MapScene((Map*)map, imageBack, imageFront) {
	map->GenerateLayerSprites(this);
}

IsometricSprite* IsometricScene::CreateSprite(Image* image, Layer layer) {
    IsometricSprite* spr = new IsometricSprite(image);
	AddSprite(spr, layer);
	return spr;
}

void IsometricScene::Update(double elapsed, Map* map) {
	// Llamamos al metodo padre
	Scene::Update(elapsed, map);

	// Ordenamos los sprites
    for ( int i = 0; i < LAYER_COUNT; i++ ) GetSprites((Layer)i).Sort(CompareSprites);
}

bool IsometricScene::CompareSprites(Sprite*& first, Sprite*& second) {
    if ( first->GetScreenY() <= second->GetScreenY() )
		return true;
	else
        return false;
}
