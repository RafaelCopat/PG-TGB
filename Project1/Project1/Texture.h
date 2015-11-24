#ifndef Texture_H
#define  Texture_H

#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "Image.h"


#define NUM_TEX 10

class Texture {


public:
	void init_textures() {
		idsTiles = new GLuint[NUM_TEX];
		Texture::init_tile_tex();

	}

	GLuint *get_ids_tex_tiles() {
		return idsTiles;
	}


private:

	void bind_textures(GLuint *ids, Image **textures, int num_textures) {
		glGenTextures(num_textures, ids);
		for (int i = 0; i < num_textures; i++) {
			glBindTexture(GL_TEXTURE_2D, ids[i]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textures[i]->getWidth(), textures[i]->getHeight(), 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, textures[i]->getPixels());
		}
	}

	void init_tile_tex() {
		Image *textures[NUM_TEX];
		int i = 0;

		textures[i++] = &Image("tile.ptm");
		textures[i++] = &Image("greentile.ptm");
		textures[i++] = &Image("parado_norte.ptm");
		textures[i++] = &Image("parado_sul.ptm");
		textures[i++] = &Image("parado_leste.ptm");
		textures[i++] = &Image("parado_oeste.ptm");
		textures[i++] = &Image("parado_nordeste.ptm");
		textures[i++] = &Image("parado_sudeste.ptm");
		textures[i++] = &Image("parado_noroeste.ptm");
		textures[i++] = &Image("parado_sudoeste.ptm");
		bind_textures(idsTiles, textures, NUM_TEX);
	}

private:
	GLuint *idsTiles;
	

};

#endif
