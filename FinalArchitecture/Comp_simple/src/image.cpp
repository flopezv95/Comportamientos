#include "../stdafx.h"
#include "../include/image.h"
#include "../include/glinclude.h"
#include "../include/math.h"
#include <math.h>
#include <stdlib.h>

// Funciones de stb_image.c:
extern "C" unsigned char *stbi_load(char const *filename, int *x, int *y, int *comp, int req_comp);
extern "C" void stbi_image_free(void *retval_from_stbi_load);


Image::Image(const String &filename, uint16 hframes, uint16 vframes) {
	this->filename = filename;
	this->hframes = hframes;
	this->vframes = vframes;
	width = 0;
	height = 0;
	handlex = 0;
	handley = 0;
	gltex = 0;
	lastU = 1.0;
	lastV = 1.0;

	// Cargamos la imagen
	int w, h, comp;
    uint8* buffer = stbi_load(filename.ToCString(), &w, &h, &comp, 4);

	// Generamos la textura
	if ( buffer ) {
		// Si no es potencia de 2, generamos un nuevo buffer que lo sea
		uint8* newBuffer = NULL;
		int newWidth = (int)pow(2, ceil(Log2(w)));
		int newHeight = (int)pow(2, ceil(Log2(h)));
		if ( newWidth != w  ||  newHeight != h ) {
			lastU = w*1.0 / newWidth;
			lastV = h*1.0 / newHeight;
			
			newBuffer = (uint8*)malloc(4*newWidth*newHeight);
			memset(newBuffer, 0, 4*newWidth*newHeight);

			for ( int y = 0; y < h; y++ ) {
				for ( int x = 0; x < w; x++ ) {
					newBuffer[4*(y*newWidth + x) + 0] = buffer[4*(y*w + x) + 0];
					newBuffer[4*(y*newWidth + x) + 1] = buffer[4*(y*w + x) + 1];
					newBuffer[4*(y*newWidth + x) + 2] = buffer[4*(y*w + x) + 2];
					newBuffer[4*(y*newWidth + x) + 3] = buffer[4*(y*w + x) + 3];
				}
			}
		}

		GLuint handle;
		glGenTextures(1, &handle);
		glBindTexture(GL_TEXTURE_2D, handle);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		if ( newBuffer )
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, newWidth, newHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, newBuffer);
		else
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
		stbi_image_free(buffer);
		if ( newBuffer)
			free(newBuffer);

		width = static_cast<uint16>(w);
		height = static_cast<uint16>(h);
		gltex = handle;
	}
}

Image::~Image() {
	glDeleteTextures(1, &gltex);
}

void Image::Bind() const {
	glBindTexture(GL_TEXTURE_2D, gltex);
}
