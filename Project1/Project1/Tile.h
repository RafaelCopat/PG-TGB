#pragma onca
#include "Image.h"
#ifndef Tile_H
#define Tile_H


class Tile {
public:
	Tile() {

	}
	Tile(int textura) {
		this->textura = textura;
	}
	Tile(int width, int height, int r, int g, int b) {
		this->width = width;
		this->height = height;
		this->r = r;
		this->g = g;
		this->b = b;
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
	int textura;
	int r;
	int g;
	int b;
	int width;
	int height;
	Image image;
};

#endif