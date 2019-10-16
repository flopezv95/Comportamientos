#ifndef UGINE_GLYPH_H
#define UGINE_GLYPH_H

class Glyph {
public:
    Glyph() : xoffset(0), yoffset(0), width(0), height(0) {}
    Glyph(double xoffset, double yoffset, double width, double height) : xoffset(xoffset), yoffset(yoffset), width(width), height(height) {}

    double GetOffsetX() const { return xoffset; }
    double GetOffsetY() const { return yoffset; }
    double GetWidth() const { return width; }
    double GetHeight() const { return height; }
private:
    double xoffset;
    double yoffset;
    double width;
    double height;
};

#endif
