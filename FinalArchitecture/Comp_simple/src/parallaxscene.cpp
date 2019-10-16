#include "../stdafx.h"
#include "../include/parallaxscene.h"
#include "../include/camera.h"
#include "../include/image.h"
#include "../include/renderer.h"
#include "../include/screen.h"

ParallaxScene::ParallaxScene(Image* imageBack, Image* imageFront) {
	backLayer = imageBack;
	frontLayer = imageFront;
	backX = 0.0f;
	backY = 0.0f;
	frontX = 0.0f;
	frontY = 0.0f;
	SetRelativeBackSpeed(1.0f, 1.0f);
	SetRelativeFrontSpeed(1.0f, 1.0f);
	SetAutoBackSpeed(0.0f, 0.0f);
	SetAutoFrontSpeed(0.0f, 0.0f);
}

void ParallaxScene::Update(double elapsed, Map* map) {
	// Metodo padre
    Scene::Update(elapsed, map);

	// Actualiza scroll
	if ( backLayer ) {
		backX += autoBackSpeedX * elapsed;
		backY += autoBackSpeedY * elapsed;
	}
	if ( frontLayer ) {
		frontX += autoFrontSpeedX * elapsed;
		frontY += autoFrontSpeedY * elapsed;
	}
}

void ParallaxScene::RenderBackground() const {
	// Metodo padre
	Scene::RenderBackground();

	// Establece propiedades de pintado
	Renderer::Instance().SetBlendMode(Renderer::ALPHA);
	Renderer::Instance().SetColor(255, 255, 255, 255);
	//Renderer::instance().setOrigin(0, 0);

	// Dibuja ambas capas de fondo
    if ( backLayer ) Renderer::Instance().DrawTiledImage(backLayer, 0, 0, Screen::Instance().GetWidth(), Screen::Instance().GetHeight(), -backX + relBackSpeedX*GetCamera().GetX(), -backY + relBackSpeedY*GetCamera().GetY());
    if ( frontLayer ) Renderer::Instance().DrawTiledImage(frontLayer, 0, 0, Screen::Instance().GetWidth(), Screen::Instance().GetHeight(), -frontX + relFrontSpeedX*GetCamera().GetX(), -frontY + relFrontSpeedY*GetCamera().GetY());
}
