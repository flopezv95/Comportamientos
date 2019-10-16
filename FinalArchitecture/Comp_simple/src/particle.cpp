#include "../stdafx.h"
#include "../include/particle.h"

Particle::Particle()
    : Sprite(NULL),
      velocityx(0),
      velocityy(0),
      angularVelocity(0),
      lifetime(0),
      initialLifetime(0),
      autofade(false) {
    SetBlendMode(Renderer::ADDITIVE);
}

Particle::Particle(Image* image, double velocityx, double velocityy, double angularVelocity, double lifetime, bool autofade)
    : Sprite(image),
      velocityx(velocityx),
      velocityy(velocityy),
      angularVelocity(angularVelocity),
      lifetime(lifetime),
      initialLifetime(lifetime),
      autofade(autofade) {
    SetBlendMode(Renderer::ADDITIVE);
}

void Particle::Update(double elapsed) {
	Sprite::Update(elapsed);

	// Actualizamos tiempo de vida
	lifetime -= elapsed;
	if ( lifetime < 0 )
		lifetime = 0;

	// Actualizamos posicion y angulo
	SetX(GetX() + velocityx*elapsed);
	SetY(GetY() + velocityy*elapsed);
	SetAngle(GetAngle() + angularVelocity*elapsed);

	// Actualizamos alpha
	if ( autofade )
		SetColor(GetRed(), GetGreen(), GetBlue(), uint8(lifetime*255/initialLifetime));
}
