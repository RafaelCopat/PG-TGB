#include "Image.h"
#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#ifndef Tile_H
#define Tile_H


class Tile {
public:
	Tile() {

	}
	Tile(int width, int height, GLuint texture) {
		this->width = width;
		this->height = height;
		this->texture = texture;
		this->visible = false;
	}
	int getHeight() {
		return height;
	}
	int getWidth() {
		return width;
	}

	GLuint getTextura() {
		return texture;
	}
	void setTexture(GLuint texture) {
		this->texture = texture;
	}
	boolean isVisible() {
		return visible;
	}
	void setVisible() {
		visible = true;
	}

private:
	GLuint texture;
	int width;
	int height;
	boolean visible;
};

#endif