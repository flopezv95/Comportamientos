#ifndef UGINE_CAMERA_H
#define UGINE_CAMERA_H

#include "../include/screen.h"

class Sprite;

class Camera {
public:
	Camera();

    virtual void SetPosition(double x, double y) { SetX(x); SetY(y); }
    virtual void SetX(double x);
    virtual void SetY(double y);
    virtual double GetX() const { return x; }
    virtual double GetY() const { return y; }

    virtual void SetBounds(double boundx0, double boundy0, double boundx1, double boundy1);
    virtual bool HasBounds() const { return boundx0 != -1; }
    virtual double GetMinX() const { return boundx0; }
    virtual double GetMinY() const { return boundy0; }
    virtual double GetMaxX() const { return boundx1 - Screen::Instance().GetWidth(); }
    virtual double GetMaxY() const { return boundy1 - Screen::Instance().GetHeight(); }

    virtual void FollowSprite(Sprite* sprite) { followingSprite = sprite; }

    virtual void Update();
private:
    double x, y;
    double boundx0, boundy0, boundx1, boundy1;
    Sprite* followingSprite;
};

#endif
