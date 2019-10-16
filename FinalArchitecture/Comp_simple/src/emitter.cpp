#include "../stdafx.h"
#include "../include/emitter.h"
#include "../include/math.h"
#include <stdlib.h>

Emitter::Emitter(Image* image, bool autofade) {
    this->image = image;
	this->autofade = autofade;
    this->blendMode = Renderer::ADDITIVE;
	SetPosition(0, 0);
	SetRate(1, 10);
	SetVelocityX(0, 0);
	SetVelocityY(0, 0);
	SetAngularVelocity(0, 0);
	SetLifetime(1, 5);
	SetMinColor(0, 0, 0);
	SetMaxColor(255, 255, 255);
    Stop();
}

void Emitter::Update(double elapsed) {
	// Calculamos rangos
	double ratedist = maxrate - minrate;
	double xveldist = maxvelx - minvelx;
	double yveldist = maxvely - minvely;
	double angveldist = maxangvel - minangvel;
	double lifetimedist = maxlifetime - minlifetime;
	int32 rdist = maxr - minr;
	int32 gdist = maxg - ming;
	int32 bdist = maxb - minb;

	// Generamos nuevas particulas
	if ( emitting ) {
		uint32 numparticles = uint32((minrate + WrapValue(rand(), ratedist)) * elapsed);
        for ( uint32 i = 0; i < numparticles; i++ ) {
            particles.Add(Particle(image, minvelx + WrapValue(rand(), xveldist), minvely + WrapValue(rand(), yveldist), minangvel + WrapValue(rand(), angveldist), minlifetime + WrapValue(rand(), lifetimedist), autofade));
            particles.Last().SetBlendMode(blendMode);
            particles.Last().SetPosition(GetX(), GetY());
            particles.Last().SetColor(static_cast<uint8>(minr + rand()%rdist), static_cast<uint8>(ming + rand()%gdist), static_cast<uint8>(minb + rand()%bdist), 255);
        }
	}

	// Actualizamos particulas
    Array<uint32> clearArray;
    for ( uint32 i = 0; i < particles.Size(); i++ ) {
        particles[i].Update(elapsed);
        if ( particles[i].GetLifetime() <= 0 )
            clearArray.Add(i);
	}

	// Borramos las particulas que sea necesario
    for ( int i = (int)clearArray.Size()-1; i > 0; i-- ) {
        particles.RemoveAt(i);
    }
}

void Emitter::Render() const {
    for ( uint32 i = 0; i < particles.Size(); i++ ) {
        particles[i].Render();
    }
}
