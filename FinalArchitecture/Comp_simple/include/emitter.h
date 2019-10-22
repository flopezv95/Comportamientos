#ifndef UGINE_EMITTER_H
#define UGINE_EMITTER_H

#include "array.h"
#include "particle.h"
#include "renderer.h"
#include "types.h"

class Image;

class Emitter {
public:
	Emitter(Image* image, bool autofade);

    virtual void SetPosition(double xPosition, double yPosition) { SetX(xPosition); SetY(yPosition); }
    virtual void SetX(double xPosition) { this->x = xPosition; }
    virtual void SetY(double yPosition) { this->y = yPosition; }
    virtual double GetX() const { return x; }
    virtual double GetY() const { return y; }

    virtual void SetRate(double minrateToAdd, double maxrateToAdd) { this->minrate = minrateToAdd; this->maxrate = maxrateToAdd; }
    virtual void SetVelocityX(double minvelxToAdd, double maxvelxToAdd) { this->minvelx = minvelxToAdd; this->maxvelx = maxvelxToAdd; }
    virtual void SetVelocityY(double minvelyToAdd, double maxvelyToAdd) { this->minvely = minvelyToAdd; this->maxvely = maxvelyToAdd; }
    virtual void SetAngularVelocity(double minangvelToAdd, double maxangvelToAdd) { this->minangvel = minangvelToAdd; this->maxangvel = maxangvelToAdd; }
    virtual void SetLifetime(double minlifetimeToAdd, double maxlifetimeToAdd) { this->minlifetime = minlifetimeToAdd; this->maxlifetime = maxlifetimeToAdd; }
    virtual void SetMinColor(uint8 rComponent, uint8 gComponent, uint8 bComponent) { minr = rComponent; ming = gComponent; minb = bComponent; }
    virtual void SetMaxColor(uint8 rComponent, uint8 gComponent, uint8 bComponent) { maxr = rComponent; maxg = gComponent; maxb = bComponent; }
    virtual void SetBlendMode(Renderer::BlendMode modeToAdd) { blendMode = modeToAdd; }

    virtual void Start() { emitting = true; }
    virtual void Stop() { emitting = false; }
    virtual bool IsEmitting() const { return emitting; }

    virtual void Update(double elapsed);
    virtual void Render() const;
private:
    Image* image;
    bool autofade;
    double x, y;

    double minrate, maxrate;
    double minvelx, maxvelx;
    double minvely, maxvely;
    double minangvel, maxangvel;
    double minlifetime, maxlifetime;
    uint8 minr, ming, minb;
    uint8 maxr, maxg, maxb;
    Renderer::BlendMode blendMode;

    bool emitting;
    Array<Particle> particles;
};

#endif
