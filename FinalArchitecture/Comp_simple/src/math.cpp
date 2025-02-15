#include "../stdafx.h"
#include "math.h"
#include <math.h>

#define DEG2RAD 0.0174532925
#define RAD2DEG 57.2957795

double Log2(double x) {
	return log(x) / log(2.0);
}

double DegSin(double degrees) {
	return sin(DEG2RAD * degrees);
}

double DegCos(double degrees) {
	return cos(DEG2RAD * degrees);
}

double DegTan(double degrees) {
	return tan(DEG2RAD * degrees);
}

double DegASin(double sin) {
	return asin(sin) * RAD2DEG;
}

double DegACos(double cos) {
	return acos(cos) * RAD2DEG;
}

double DegATan(double tan) {
	return atan(tan) * RAD2DEG;
}

double DegATan2(double y, double x) {
	return atan2(y, x) * RAD2DEG;
}

double WrapValue(double val, double mod) {
    if (mod == 0) return val;
    return val - mod*floor(val/mod);
}


double Angle(double x1, double y1, double x2, double y2) {
	return WrapValue(DegATan2(y1-y2, x2-x1), 360);
}

double Distance(double x1, double y1, double x2, double y2) {
	double xoffs = x2 - x1;
	double yoffs = y2 - y1;
	return sqrt(xoffs*xoffs + yoffs*yoffs);
}

bool ValueInRange(double value, double min, double max) {
	return (value >= min) && (value <= max);
}

bool PointInRect(double x, double y, double rectx, double recty, double width, double height) {
	if ( ValueInRange(x, rectx, rectx+width) && ValueInRange(y, recty, recty+height) )
		return true;
	else
		return false;
}

void ClosestPointToRect(double x, double y, double rectx, double recty, double width, double height, double* outx, double* outy) {
	*outx = (x < rectx) ? rectx : (x > rectx+width) ? rectx+width : x;
	*outy = (y < recty) ? recty : (y > recty+height) ? recty+height : y;
}

bool RectsOverlap(double x1, double y1, double width1, double height1, double x2, double y2, double width2, double height2) {
	bool xoverlap = ValueInRange(x1, x2, x2+width2) || ValueInRange(x2, x1, x1+width1);
	bool yoverlap = ValueInRange(y1, y2, y2+height2) || ValueInRange(y2, y1, y1+height1);
	return xoverlap && yoverlap;
}

void OverlappingRect(double x1, double y1, double width1, double height1, double x2, double y2, double width2, double height2, double* outx, double* outy, double* outwidth, double* outheight) {
	if ( ValueInRange(x1, x2, x2+width2) ) *outx = x1; else *outx = x2;
	if ( ValueInRange(y1, y2, y2+height2) ) *outy = y1; else *outy = y2;
	if ( ValueInRange(x1+width1, x2, x2+width2) ) *outwidth = x1+width1-*outx; else *outwidth = x2+width2-*outx;
	if ( ValueInRange(y1+height1, y2, y2+height2) ) *outheight = y1+height1-*outy; else *outheight = y2+height2-*outy;
}

void TransformIsoCoords(double isoX, double isoY, double isoZ, double* screenX, double* screenY) {
	*screenX = (isoX - isoY) * 0.89442612730660787; //degcos(26.5651882);
	*screenY = isoZ + (isoX + isoY) * 0.44721572288024897; //degsin(26.5651882);
}
