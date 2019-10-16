#include "../stdafx.h"
#include "../include/collisionmanager.h"
#include "../include/collisionpixeldata.h"
#include "../include/math.h"

CollisionManager* CollisionManager::manager = NULL;

bool CollisionManager::CircleToCircle(double x1, double y1, double r1, double x2, double y2, double r2) const {
	if ( Distance(x1, y1, x2, y2) < r1+r2 )
		return true;
	else
		return false;
}

bool CollisionManager::CircleToPixels(double cx, double cy, double cr, const CollisionPixelData* pixels, double px, double py) const {
	for ( int x = 0; x < pixels->GetWidth(); x++ )
		for ( int y = 0; y < pixels->GetHeight(); y++ )
			if ( pixels->GetData(x, y)  && Distance(cx, cy, x+px, y+py) < cr )
				return true;
	return false;
}

bool CollisionManager::CircleToRect(double cx, double cy, double cr, double rx, double ry, double rw, double rh) const {
	if ( PointInRect(cx, cy, rx, ry, rw, rh) ) {
		return true;
	} else {
		double closestx, closesty;
		ClosestPointToRect(cx, cy, rx, ry, rw, rh, &closestx, &closesty);
		if ( Distance(cx, cy, closestx, closesty) < cr )
			return true;
		else
			return false;
	}
}

bool CollisionManager::PixelsToPixels(const CollisionPixelData* p1, double x1, double y1, const CollisionPixelData* p2, double x2, double y2) const {
	if ( RectsOverlap(x1, y1, p1->GetWidth(), p1->GetHeight(), x2, y2, p2->GetWidth(), p2->GetHeight()) ) {
		double rectx, recty, rectwidth, rectheight;
		OverlappingRect(x1, y1, p1->GetWidth(), p1->GetHeight(), x2, y2, p2->GetWidth(), p2->GetHeight(), &rectx, &recty, &rectwidth, &rectheight);
		uint16 fromx1 = uint16(rectx - x1);
		uint16 fromy1 = uint16(recty - y1);
		uint16 fromx2 = uint16(rectx - x2);
		uint16 fromy2 = uint16(recty - y2);
		for ( int px = 0; px < rectwidth; px++ )
			for ( int py = 0; py < rectheight; py++ )
				if ( p1->GetData(fromx1+px, fromy1+py)  &&  p2->GetData(fromx2+px, fromy2+py) )
					return true;
	}
	return false;
}

bool CollisionManager::PixelsToRect(const CollisionPixelData* pixels, double px, double py, double rx, double ry, double rw, double rh) const {
	if ( RectsOverlap(px, py, pixels->GetWidth(), pixels->GetHeight(), rx, ry, rw, rh) ) {
		double rectx, recty, rectwidth, rectheight;
		OverlappingRect(px, py, pixels->GetWidth(), pixels->GetHeight(), rx, ry, rw, rh, &rectx, &recty, &rectwidth, &rectheight);
		uint16 fromx = uint16(rectx - px);
		uint16 fromy = uint16(recty - py);
		for ( int x = 0; x < rectwidth; x++ )
			for ( int y = 0; y < rectheight; y++ )
				if ( pixels->GetData(fromx+x, fromy+y) )
					return true;
	}
	return false;
}

bool CollisionManager::RectToRect(double x1, double y1, double w1, double h1, double x2, double y2, double w2, double h2) const {
	return RectsOverlap(x1, y1, w1, h1, x2, y2, w2, h2);
}
