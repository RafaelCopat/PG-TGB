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
	Tile(int width, int height, int r, int g, int b, GLuint textura) {
		this->width = width;
		this->height = height;
		this->r = r;
		this->g = g;
		this->b = b;
		this->textura = textura;
	}
	Tile(Image image) {
		this->image = image;
	}
	
	int* getImagePixels() {
		return image.getPixels();
	}
	int getHeight() {
		//return image.getHeight();
		return height;
	}
	int getWidth() {
		//return image.getWidth();
		return width;
	}
	void setImage(Image image) {
		this->image = image;
	}
	int getR() {
		return r;
	}
	int getG() {
		return g;
	}
	int getB() {
		return b;
	}
	void setRgb(int r,int g, int b) {
		this->r = r;
		this->g = g;
		this->b = b;
	}

private:
	GLuint textura;
	int r;
	int g;
	int b;
	int width;
	int height;
	Image image;
};

#endif