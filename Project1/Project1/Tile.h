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
	Tile(Image image) {
		this->image = image;
	}
	//Tilemap(Tile *tiles, int size){
	//this->tiles = tiles;
	//this->size = size;
	//}
	int* getImagePixels() {
		return image.getPixels();
	}

private:
	int textura;
	Image image;
};

#endif