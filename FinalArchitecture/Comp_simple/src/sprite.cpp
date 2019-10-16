#include "../stdafx.h"
#include "../include/sprite.h"
#include "../include/rectcollision.h"
#include "../include/image.h"
#include "../include/map.h"
#include "../include/math.h"
#include "../include/pixelcollision.h"
#include "../include/renderer.h"
#include "../include/circlecollision.h"
#include <math.h>

Sprite::Sprite(Image* image) {
	SetImage(image);
	SetPosition(0, 0);
	SetAngle(0);
	SetScale(1.0f, 1.0f);
	SetRadius(image->GetWidth()/4);
	SetFPS(0);
	SetFrameRange(0, (image != NULL) ? static_cast<uint16>(image->GetNumFrames()-1) : 0);
	SetCurrentFrame(0);
	SetBlendMode(Renderer::ALPHA);
	SetColor(255, 255, 255, 255);
	SetCollisionPixelData(NULL);
	collision = NULL;
	colSprite = NULL;
	collided = false;
	rotating = false;
	moving = false;
}

Sprite::~Sprite() {
    if ( collision ) delete collision;
}

void Sprite::SetCollision(CollisionMode mode) {
	if ( collision )
		delete collision;

	switch ( mode ) {
	case COLLISION_NONE:
		collision = NULL;
		break;
	case COLLISION_CIRCLE:
		collision = new CircleCollision(&x, &y, &radius);
		break;
	case COLLISION_PIXEL:
		collision = new PixelCollision(colPixelData, &colx, &coly);
		break;
	case COLLISION_RECT:
		collision = new RectCollision(&colx, &coly, &colwidth, &colheight);
		break;
	}
}

bool Sprite::CheckCollision(Sprite* sprite) {
	if ( collision != NULL  &&  sprite->collision != NULL ) {
		bool col = collision->DoesCollide(sprite->collision);
		if ( col ) {
			colSprite = sprite;
			collided = true;
			sprite->colSprite = this;
			sprite->collided = true;
		}
		return col;
	} else {
		return false;
	}
}

bool Sprite::CheckCollision(const Map* map) {
	if ( collision  &&  map->CheckCollision(collision) ) {
		collided = true;
		return true;
	} else {
		return false;
	}
}

void Sprite::RotateTo(int32 angle, double speed) {
	if ( WrapValue(angle, 360) == WrapValue(this->angle, 360)  ||  speed == 0 ) {
		rotating = false;
	} else {
		rotating = true;
		toAngle = (uint16)WrapValue(angle, 360);

		uint16 wrapAngle = (uint16)WrapValue(this->angle, 360);
		if ( min(WrapValue(toAngle-wrapAngle,360), WrapValue(wrapAngle-toAngle,360)) == WrapValue(toAngle-wrapAngle,360) ) {
			rotatingSpeed = fabs(speed);
			anglesToRotate = WrapValue(toAngle-wrapAngle,360);
		} else {
			rotatingSpeed = -fabs(speed);
			anglesToRotate = WrapValue(wrapAngle-toAngle,360);
		}
	}
}

void Sprite::MoveTo(double x, double y, double speedX, double speedY) {
	if ( this->x == x  &&  this->y == y ) {
		moving = false;
	} else {
		moving = true;
		toX = x;
		toY = y;
		if (speedY == 0 ) {
			double timeNeeded = Distance(this->x, this->y, x, y) / fabs(speedX);
			movingSpeedX = fabs(this->x - x) / timeNeeded;
			movingSpeedY = fabs(this->y - y) / timeNeeded;
		} else {
			movingSpeedX = speedX;
			movingSpeedY = speedY;
		}
	}
}

void Sprite::Update(double elapsed, const Map* map) {
	// Informacion inicial de colision
	colSprite = NULL;
	collided = false;

	// Actualizamos animacion
	currentFrame += animFPS * elapsed;
	if ( currentFrame >= lastFrame+1 )
		currentFrame = firstFrame;
	if ( currentFrame < firstFrame )
		currentFrame = lastFrame;

	// Actualizamos rotacion
	if ( rotating ) {
		angle += rotatingSpeed * elapsed;
		anglesToRotate -= fabs(rotatingSpeed * elapsed);

		if ( anglesToRotate <= 0 ) {
			angle = toAngle;
			rotating = false;
		}
	}

	// Actualizamos movimiento
	if ( moving ) {
		prevX = x;
		prevY = y;

		if ( x < toX ) {
			x += movingSpeedX * elapsed;
			UpdateCollisionBox();
			if ( map && CheckCollision(map) ) x = prevX;
			if ( x > toX ) x = toX;
		} else {
			x -= movingSpeedX * elapsed;
			UpdateCollisionBox();
			if ( map && CheckCollision(map) ) x = prevX;
			if ( x < toX ) x = toX;
		}
		if ( y < toY ) {
			y += movingSpeedY * elapsed;
			UpdateCollisionBox();
			if ( map && CheckCollision(map) ) y = prevY;
			if ( y > toY ) y = toY;
		} else {
			y -= movingSpeedY * elapsed;
			UpdateCollisionBox();
			if ( map && CheckCollision(map) ) y = prevY;
			if ( y < toY ) y = toY;
		}

		if ( (x == prevX && y == prevY) || (x == toX && y == toY) )
			moving = false;
	}

	// Informacion final de colision
	UpdateCollisionBox();
}

void Sprite::Render() const {
    Renderer::Instance().SetBlendMode(blendMode);
	Renderer::Instance().SetColor(r, g, b, a);
	Renderer::Instance().DrawImage(image, GetScreenX(), GetScreenY(), (uint32)currentFrame, image->GetWidth()*scalex, image->GetHeight()*scaley, angle);
}

void Sprite::UpdateCollisionBox() {
	double x = GetX()-image->GetHandleX()*fabs(GetScaleX());
	double y = GetY()-image->GetHandleY()*fabs(GetScaleY());
	double w = image->GetWidth()*fabs(GetScaleX());
	double h = image->GetHeight()*fabs(GetScaleY());
	UpdateCollisionBox(x, y, w, h);
}

void Sprite::UpdateCollisionBox(double x, double y, double w, double h) {
	colx = x;
	coly = y;
	colwidth = w;
	colheight = h;
}
