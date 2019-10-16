#include "../stdafx.h"
#include "../include/camera.h"
#include "../include/sprite.h"

Camera::Camera() {
	SetBounds(-1, -1, -1, -1);
	SetPosition(0, 0);
	followingSprite = NULL;
}

void Camera::SetX(double x) {
	if ( !HasBounds() ) {
		this->x = x;
	} else {
		if ( x < GetMinX() )
			this->x = GetMinX();
		else if ( x > GetMaxX() )
			this->x = GetMaxX();
		else
			this->x = x;
	}
}

void Camera::SetY(double y) {
	if ( !HasBounds() ) {
		this->y = y;
	} else {
		if ( y < GetMinY() )
			this->y = GetMinY();
		else if ( y > GetMaxY() )
			this->y = GetMaxY();
		else
			this->y = y;
	}
}

void Camera::SetBounds(double boundx0, double boundy0, double boundx1, double boundy1) {
	this->boundx0 = boundx0;
	this->boundy0 = boundy0;
	this->boundx1 = boundx1;
	this->boundy1 = boundy1;
	SetPosition(GetX(), GetY());
}

void Camera::Update() {
	if ( followingSprite )
		SetPosition(followingSprite->GetScreenX() - Screen::Instance().GetWidth()/2, followingSprite->GetScreenY() - Screen::Instance().GetHeight()/2);
}
