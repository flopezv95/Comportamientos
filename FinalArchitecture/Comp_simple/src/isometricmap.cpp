#include "../stdafx.h"
#include "../include/isometricmap.h"
#include "../include/image.h"
#include "../include/isometricscene.h"
#include "../include/isometricsprite.h"
#include "../include/math.h"
#include "../include/renderer.h"
#include "../include/string.h"
#include "../lib/rapidxml.hpp"

using namespace rapidxml;

IsometricMap::IsometricMap(const String &filename, uint16 firstColId) : Map(filename, firstColId) {
	// Analizamos el XML
    String buffer = String::Read(filename);
	xml_document<> doc;
    doc.parse<0>((char*)buffer.ToCString());

	// Obtenemos informacion del tileset
	int firstGid = atoi(doc.first_node("map")->first_node("tileset")->first_attribute("firstgid")->value());

	// Cargamos el segundo layer
	xml_node<>* dataNode = doc.first_node("map")->first_node("layer")->next_sibling()->first_node("data");
	if ( dataNode->first_attribute("encoding") || dataNode->first_attribute("compression") ) return;
	xml_node<>* tileNode = dataNode->first_node("tile");
	while ( tileNode ) {
        topLayerIds.Add(atoi(tileNode->first_attribute("gid")->value()) - firstGid);
		tileNode = tileNode->next_sibling("tile");
	}
	
	// Ajustamos handle de la imagen (en un mapa isometrico el offset se cuenta desde la parte de abajo de la imagen)
	GetImage()->SetHandle(GetImage()->GetHandleX() + GetTileWidth(), GetImage()->GetHeight() - GetImage()->GetHandleY() - GetTileHeight());
}

void IsometricMap::GenerateLayerSprites(IsometricScene* scene) {
	// Generamos sprites para todos los tiles no vacios del segundo layer,
	// de forma que sean ordenados a la hora de pintarlos
	for ( uint16 y = 0; y < GetRows(); y++ ) {
		for ( uint16 x = 0; x < GetColumns(); x++ ) {
			if ( topLayerIds[y*GetColumns() + x] >= 0 ) {
				IsometricSprite* spr = scene->CreateSprite(GetImage());
				if ( topLayerIds[y*GetColumns() + x] >= GetFirstColId() )
					spr->SetCollision(Sprite::COLLISION_RECT);
				spr->SetCurrentFrame(static_cast<uint16>(topLayerIds[y*GetColumns() + x]));
				spr->SetPosition(x*GetTileWidth(), y*GetTileHeight());
			}
		}
	}
}

void IsometricMap::Render() const {
	// Dibujamos los tiles del suelo
	for ( uint16 y = 0; y < GetRows(); y++ ) {
		for ( uint16 x = 0; x < GetColumns(); x++ ) {
			if ( GetTileId(x, y) >= 0 ) {
				double screenX, screenY;
				TransformIsoCoords(x*GetTileWidth(), y*GetTileHeight(), 0, &screenX, &screenY);
				Renderer::Instance().DrawImage(GetImage(), screenX, screenY, GetTileId(x, y));
			}
		}
	}
}
