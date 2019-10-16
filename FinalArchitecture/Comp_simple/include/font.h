#ifndef UGINE_FONT_H
#define UGINE_FONT_H

#include "array.h"
#include "image.h"
#include "glyph.h"
#include "string.h"
#include "types.h"

class Glyph;

class Font : public Image {
public:
    Font(const String& filename);

    virtual uint16 GetSize() const { return GetHeight(); }
    virtual uint32 GetTextWidth(const String& text) const;
    virtual uint32 GetTextHeight(const String& text) const { (void)text; return GetSize(); }

    virtual void Render(const String& text, double x, double y) const;
protected:
    virtual void GetPixelColor(uint8* buffer, uint16 width, uint16 x, uint16 y, uint8* r, uint8* g, uint8* b, uint8* a) const;
    virtual void SetPixelColor(uint8* buffer, uint16 width, uint16 x, uint16 y, uint8 r, uint8 g, uint8 b, uint8 a) const;
private:
    Array<Glyph> glyphs;
};


#endif
