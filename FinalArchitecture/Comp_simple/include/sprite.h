#ifndef UGINE_SPRITE_H
#define UGINE_SPRITE_H
#include "renderer.h"
#include "types.h"

class Collision;
class CollisionPixelData;
class Image;
class Map;

class Sprite {
public:
	enum CollisionMode {
		COLLISION_NONE,
		COLLISION_CIRCLE,
		COLLISION_PIXEL,
		COLLISION_RECT
	};

	Sprite(Image* image);
	virtual ~Sprite();

    virtual void SetImage(Image* imageToAdd) { this->image = imageToAdd; }
    virtual const Image* GetImage() const { return image; }

    virtual void SetPosition(double xPosition, double yPosition, double zPosition = 0) { SetX(xPosition); SetY(yPosition); SetZ(zPosition); }
    virtual void SetX(double xPosition) { this->x = xPosition; }
    virtual void SetY(double yPosition) { this->y = yPosition; }
    virtual void SetZ(double zPosition) { this->z = zPosition; }
    virtual double GetX() const { return x; }
    virtual double GetY() const { return y; }
    virtual double GetZ() const { return z; }
    virtual double GetScreenX() const { return x; }
    virtual double GetScreenY() const { return y; }

    virtual void SetAngle(double angleToAdd) { this->angle = angleToAdd; }
    virtual double GetAngle() const { return angle; }

    virtual void SetScale(double sx, double sy) { SetScaleX(sx); SetScaleY(sy); }
    virtual void SetScaleX(double sx) { scalex = sx; }
    virtual void SetScaleY(double sy) { scaley = sy; }
    virtual double GetScaleX() const { return scalex; }
    virtual double GetScaleY() const { return scaley; }

    virtual void SetFPS(int16 fps) { animFPS = fps; }
    virtual int16 GetFPS() const { return animFPS; }
    virtual void SetFrameRange(uint16 firstFrametoAdd, uint16 lastFrameToAdd) { this->firstFrame = firstFrametoAdd; this->lastFrame = lastFrameToAdd; }
    virtual uint16 GetFirstFrame() const { return firstFrame; }
    virtual uint16 GetLastFrame() { return lastFrame; }
    virtual void SetCurrentFrame(uint16 frame) { currentFrame = frame; }
    virtual uint16 GetCurrentFrame() const { return (uint16)currentFrame; }

    virtual void SetBlendMode(Renderer::BlendMode blend) { blendMode = blend; }
    virtual Renderer::BlendMode GetBlendMode() const { return blendMode; }
    virtual void SetColor(uint8 rComponent, uint8 gComponent, uint8 bComponent, uint8 alphaComponent = 255) { this->r = rComponent; this->g = gComponent; this->b = bComponent; this->a = alphaComponent; }
    virtual uint8 GetRed() const { return r; }
    virtual uint8 GetGreen() const { return g; }
    virtual uint8 GetBlue() const { return b; }
    virtual uint8 GetAlpha() const { return a; }

    virtual void SetRadius(double radiusToAdd) { this->radius = radiusToAdd; }
    virtual double GetRadius() const { return this->radius; }

	virtual void SetCollision(CollisionMode mode);
    virtual void SetCollisionPixelData(const CollisionPixelData* colPixelDataToAdd) { this->colPixelData = colPixelDataToAdd; }
    virtual const Collision* GetCollision() const { return collision; }
    virtual bool CheckCollision(Sprite* sprite);
    virtual bool CheckCollision(const Map* map);
    virtual const Sprite* CollisionSprite() const { return colSprite; }
    virtual bool DidCollide() const { return collided; }

    virtual void RotateTo(int32 angle, double speed);
    virtual void MoveTo(double x, double y, double speedX, double speedY = 0.0);
    virtual bool IsRotating() const { return rotating; }
    virtual bool IsMoving() const { return moving; }

    virtual void Update(double elapsed, const Map* map = NULL);
    virtual void Render() const;
protected:
    virtual void UpdateCollisionBox();
    virtual void UpdateCollisionBox(double x, double y, double w, double h);
private:
    Image* image;
    double x, y, z;
    double colx, coly, colwidth, colheight;
    double angle;
    double scalex, scaley;
    double radius;
    int16 animFPS;
    uint16 firstFrame, lastFrame;
    double currentFrame;
    Renderer::BlendMode blendMode;
    uint8 r, g, b, a;
    Collision* collision;
    const CollisionPixelData* colPixelData;
    Sprite* colSprite;
    bool collided;

    bool rotating;
    uint16 toAngle;
    double rotatingSpeed;
    double anglesToRotate;

    bool moving;
    double toX, toY;
    double movingSpeedX, movingSpeedY;
    double prevX, prevY;
};

#endif
