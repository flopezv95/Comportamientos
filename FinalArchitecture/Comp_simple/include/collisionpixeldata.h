#ifndef UGINE_COLLISIONPIXELDATA_H
#define UGINE_COLLISIONPIXELDATA_H

#include "string.h"
#include "types.h"

class CollisionPixelData {
public:
    CollisionPixelData(const String& filename);
    virtual ~CollisionPixelData() { delete[] data; }

    virtual bool IsValid() const { return data != NULL; }
    virtual const String& GetFilename() const { return filename; }
    virtual uint16 GetWidth() const { return width; }
    virtual uint16 GetHeight() const { return height; }
    virtual bool GetData(uint32 x, uint32 y) const { return data[y*width + x]; }
private:
    String filename;
    uint16 width, height;
    bool* data;
};

#endif
