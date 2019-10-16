#include "../stdafx.h"
#include "../include/collisionpixeldata.h"

// Funciones de stb_image.c:
extern "C" unsigned char *stbi_load(char const *filename, int *x, int *y, int *comp, int req_comp);
extern "C" void stbi_image_free(void *retval_from_stbi_load);

CollisionPixelData::CollisionPixelData(const String &filename) {
	this->filename = filename;
	data = NULL;
	width = 0;
	height = 0;

	// Cargamos la textura
	int w, h, comp;
    uint8* buffer = stbi_load(filename.ToCString(), &w, &h, &comp, 4);
	if ( buffer ) {
		width = (uint16)w;
		height = (uint16)h;

		data = new bool[width*height];
		for ( uint32 y = 0; y < height; y++ ) {
			for ( uint32 x = 0; x < width; x++ ) {
				buffer[(y*width + x)*4 + 3] == 0 ? data[y*width + x] = false : data[y*width + x] = true;
			}
		}

		stbi_image_free(buffer);
	}
}
