#include "../stdafx.h"
#include "../include/isometricsprite.h"
#include "../include/image.h"
#include "../include/math.h"
#include <math.h>

void IsometricSprite::SetCollision(CollisionMode mode) {
	if ( mode == COLLISION_PIXEL )
		Sprite::SetCollision(COLLISION_RECT);
	else
		Sprite::SetCollision(mode);
}

void IsometricSprite::Update(double elapsed, const Map* map) {
	// Llamamos al metodo padre
	Sprite::Update(elapsed, map);

	// Convertimos las coordenadas
	TransformIsoCoords(GetX(), GetY(), GetZ(), &screenX, &screenY);
}

void IsometricSprite::UpdateCollisionBox() {
	double x = GetX() - GetImage()->GetHandleX()*fabs(GetScaleX());
	double y = GetY() - GetImage()->GetHandleX()*fabs(GetScaleX());
	double w = GetImage()->GetWidth()*fabs(GetScaleX());
	double h = GetImage()->GetWidth()*fabs(GetScaleX());
	Sprite::UpdateCollisionBox(x, y, w, h);
}
