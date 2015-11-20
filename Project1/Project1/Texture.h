#ifndef Texture_H
#define  Texture_H

#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "Image.h"


#define NUM_TEX_TILES 1
#define NUM_TEX_CHARARCTER 1
#define NUM_TEX_OBJECTS 1

class Texture {


public:
	 void init_textures() {
		 idsTiles = new GLuint[NUM_TEX_TILES];
		 idsCharacters = new GLuint[NUM_TEX_CHARARCTER];
		 idsObjects = new GLuint[NUM_TEX_OBJECTS];
		Texture::init_tile_tex();
		Texture::init_character_tex();
		Texture::init_objects_tex(); 
		
	}

	 GLuint *get_ids_tex_tiles() {
		return idsTiles;
	}

	 GLuint *get_ids_tex_character() {
		return idsCharacters;
	}

	 GLuint *get_ids_tex_objects() {
		return idsObjects;
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
		Image *textures[NUM_TEX_TILES];
		int i = 0;
		textures[i] = &Image("tile.ptm");
		bind_textures(idsTiles, textures, NUM_TEX_TILES);
	}

	 void init_character_tex() {
		Image *textures[NUM_TEX_CHARARCTER];
		int i = 0;
		
		//bind_textures(idsCharacters, textures, NUM_TEX_CHARARCTER);
	}

	 void init_objects_tex() {
		Image *textures[NUM_TEX_OBJECTS];
		int i = 0;

		//bind_textures(idsObjects, textures, NUM_TEX_OBJECTS);
	}

private:
	 GLuint *idsTiles;
	 GLuint *idsCharacters;
	 GLuint *idsObjects;

};

#endif
