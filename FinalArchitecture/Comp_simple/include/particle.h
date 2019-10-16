#ifndef UGINE_PARTICLE_H
#define UGINE_PARTICLE_H

#include "sprite.h"

class Particle : public Sprite {
public:
    Particle();
	Particle(Image* image, double velocityx, double velocityy, double angularVelocity, double lifetime, bool autofade);

    virtual double GetLifetime() const { return lifetime; }

	virtual void Update(double elapsed);
private:
    double velocityx, velocityy;
    double angularVelocity;
    double lifetime;
    double initialLifetime;
    bool autofade;
};

#endif
