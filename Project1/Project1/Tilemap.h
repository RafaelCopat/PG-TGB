#pragma onca
#include <stdlib.h>
#include "Image.h"
#include <algorithm>
#include "Tile.h"
#ifndef Tilemap_H
#define Tilemap_H


class Tilemap {
public:
	Tilemap() {

	}
	Tilemap(int size) {
		this->size = size;
	}
	//Tilemap(Tile *tiles, int size){
	//this->tiles = tiles;
	//this->size = size;
	//}

	Tile getTile(int index) {
		return tiles[index];
	}
	void setSize(int size) {
		this->size = size;
		tiles = new Tile[size];
	}
	void setTiles(Image tile) {
		for (int i = 0; i < size; i++) {
			Tile a(tile);
			tiles[i] = a;
		}
	}
	int getSize() {
		return size;
	}

private:
	Tile * tiles;
	int size;
};

#endif