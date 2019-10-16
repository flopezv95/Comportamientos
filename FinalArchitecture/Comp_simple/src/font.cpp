#include "../stdafx.h"
#include "../include/font.h"
#include "../include/glinclude.h"
#include "../include/renderer.h"
#include <math.h>

extern "C" unsigned char *stbi_load(char const *filename, int *x, int *y, int *comp, int req_comp);
extern "C" void stbi_image_free(void *retval_from_stbi_load);

Font::Font(const String &filename) : Image(filename, 16, 16) {
	if ( IsValid() ) {
		// Cargamos el buffer de imagen
		int  w, h, comp;
        uint8* buffer = stbi_load(filename.ToCString(), &w, &h, &comp, 4);

		// Obtenemos informacion de los glifos
		for ( uint32 i = 0; i < 256; i++ ) {
            // Encontramos el glifo dentro del frame
            double xoffset = 0;
            double yoffset = 0;
            double width = GetWidth();
            double height = GetHeight();
            uint16 row = (uint16)floor(i*1.0 / GetHFrames());
            uint16 column = i % GetHFrames();
            for ( uint16 y = row*GetHeight(); y < (row + 1)*GetHeight(); y++ ) {
                for ( uint16 x = column*GetWidth(); x < (column + 1)*GetWidth(); x++ ) {
                    uint8 r, g, b, a;
                    GetPixelColor(buffer, static_cast<uint16>(w), x, y, &r, &g, &b, &a);
                    if ( r == 255  &&  g == 255  &&  b == 0 ) {
                        xoffset = (x - column*GetWidth())*-1.0;
                        yoffset = (y - row*GetHeight())*-1.0;
                        SetPixelColor(buffer, static_cast<uint16>(w), x, y, 0, 0, 0, 0);
                    } else if ( r == 255  &&  g == 0  &&  b == 0 ) {
                        width = (x - column*GetWidth()) + xoffset;
                        height = (y - row*GetHeight()) + yoffset;
                        SetPixelColor(buffer, static_cast<uint16>(w), x, y, 0, 0, 0, 0);
                    } else if ( r == 0  &&  g == 0  &&  b == 0 ) {
                        SetPixelColor(buffer, static_cast<uint16>(w), x, y, 0, 0, 0, 0);
                    }
                }
            }

            // Aniadimos el glifo a la lista
            glyphs.Add(Glyph(xoffset, yoffset, width, height));
		}

		// Modificamos la textura (hemos convertido en transparentes los pixeles del glifo)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);

		// Borramos el buffer
		stbi_image_free(buffer);
	}
}

uint32 Font::GetTextWidth(const String &text) const {
    uint32 width = 0;
    for ( int i = 0; i < text.Length(); i++ ) width += (int)glyphs[(unsigned char)text[i]].GetWidth();
    return width;
}

void Font::Render(const String &text, double x, double y) const {
    for ( int i = 0; i < text.Length(); i++ ) {
        const Glyph& glyph = glyphs[(unsigned char)text[i]];
        Renderer::Instance().DrawImage(this, x + glyph.GetOffsetX(), y + glyph.GetOffsetY(), (unsigned char)text[i]);
        x += glyph.GetWidth();
    }
}

void Font::GetPixelColor(uint8* buffer, uint16 width, uint16 x, uint16 y, uint8* r, uint8* g, uint8* b, uint8* a) const {
	*r = buffer[(y*width + x)*4 + 0];
	*g = buffer[(y*width + x)*4 + 1];
	*b = buffer[(y*width + x)*4 + 2];
	*a = buffer[(y*width + x)*4 + 3];
}

void Font::SetPixelColor(uint8* buffer, uint16 width, uint16 x, uint16 y, uint8 r, uint8 g, uint8 b, uint8 a) const {
	buffer[(y*width + x)*4 + 0] = r;
	buffer[(y*width + x)*4 + 1] = g;
	buffer[(y*width + x)*4 + 2] = b;
	buffer[(y*width + x)*4 + 3] = a;
}
