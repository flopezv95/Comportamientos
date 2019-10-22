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
	double newX = GetX() - GetImage()->GetHandleX()*fabs(GetScaleX());
	double newY = GetY() - GetImage()->GetHandleX()*fabs(GetScaleX());
	double newW = GetImage()->GetWidth()*fabs(GetScaleX());
	double newH = GetImage()->GetWidth()*fabs(GetScaleX());
	Sprite::UpdateCollisionBox(newX, newY, newW, newH);
}
