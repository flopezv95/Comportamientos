#include "../stdafx.h"
#include "../include/camera.h"
#include "../include/sprite.h"

Camera::Camera() {
	SetBounds(-1, -1, -1, -1);
	SetPosition(0, 0);
	followingSprite = NULL;
}

void Camera::SetX(double xToSet) {
	if ( !HasBounds() ) {
		this->x = xToSet;
	} else {
		if (xToSet < GetMinX() )
			this->x = GetMinX();
		else if (xToSet > GetMaxX() )
			this->x = GetMaxX();
		else
			this->x = xToSet;
	}
}

void Camera::SetY(double yToSet) {
	if ( !HasBounds() ) {
		this->y = yToSet;
	} else {
		if (yToSet < GetMinY() )
			this->y = GetMinY();
		else if (yToSet > GetMaxY() )
			this->y = GetMaxY();
		else
			this->y = yToSet;
	}
}

void Camera::SetBounds(double boundx0ToSet, double boundy0ToSet, double boundx1ToSet, double boundy1ToSet) {
	this->boundx0 = boundx0ToSet;
	this->boundy0 = boundy0ToSet;
	this->boundx1 = boundx1ToSet;
	this->boundy1 = boundy1ToSet;
	SetPosition(GetX(), GetY());
}

void Camera::Update() {
	if ( followingSprite )
		SetPosition(followingSprite->GetScreenX() - Screen::Instance().GetWidth()/2, followingSprite->GetScreenY() - Screen::Instance().GetHeight()/2);
}
