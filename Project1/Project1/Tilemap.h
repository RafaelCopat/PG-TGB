#pragma onca
#include <stdlib.h>
#include "Image.h"
#include <algorithm>
#include "Tile.h"
#include <string>
#include <iostream>
#ifndef Tilemap_H
#define Tilemap_H
#define NORTH 1
#define EAST 2
#define WEST 3
#define SOUTH 4
#define NORTHEAST 5
#define SOUTHEAST 6
#define NORTHWEST 7
#define SOUTHWEST 8

class Tilemap {
public:
	Tilemap() {

	}
	
	//Tilemap(Tile *tiles, int size){
	//this->tiles = tiles;
	//this->size = size;
	//}

	Tile getTile(int index) {
		return tiles[index];
	}
	void setStartCoords(double startx, double starty) {
		this->startx = startx;
		this->starty = starty;
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
	void setCenterTile(Image tile, int x, int y) {
			Tile a(tile);
			tiles[size/2] = a;
			tileSelected = size/2;
	}
	void tilewalk(const int DIRECTION, Image tile, Image greentile) {
		int w = tiles[0].getWidth();
		int h = tiles[0].getHeight();
		int newTileX = 0;
		int newTileY = 0;
		switch (DIRECTION) {
		case NORTH:
			newTileY = tileSelectedY - h;
			newTileX = tileSelectedX;
			break;
		case SOUTH:
			newTileX = tileSelectedX;
			newTileY = tileSelectedY + h;
			break;
		case EAST:
			newTileX = tileSelectedX + w;
			newTileY = tileSelectedY;
			break;
		case WEST:
			newTileX = tileSelectedX - w;
			newTileY = tileSelectedY;
			break;
		case NORTHEAST:
			newTileX = tileSelectedX + w / 2;
			newTileY = tileSelectedY - h / 2;
			break;
		case SOUTHEAST:
			newTileX = tileSelectedX + w / 2;
			newTileY = tileSelectedY + h / 2;
			break;
		case NORTHWEST:
			newTileX = tileSelectedX - w / 2;
			newTileY = tileSelectedY - h / 2;
			break;
		case SOUTHWEST:
			newTileX = tileSelectedX - w / 2;
			newTileY = tileSelectedY + h / 2;
			break;
		}
		setTileGreen(newTileX, newTileY, tile, greentile);
	}
	int getSize() {
		return size;
	}
	void setTileGreen(int x, int y, Image tile, Image greentile) {
		int tilenumber = whatTileIs(x, y);
		if (tilenumber != -1) {
			tiles[tileSelected].setImage(tile);
			tileSelectedX = x;
			tileSelectedY = y;
			tileSelected = tilenumber;
			tiles[tilenumber].setImage(greentile);
		}
	}
	int whatTileIs(int x, int y) {
		double halfwidth = tiles[0].getWidth() / 2;
		double halfheight = tiles[0].getHeight() / 2;
		double realx = (double)x;
		double realy = (double)y;
		double mapx = ((((startx + halfwidth) - x) / halfwidth) + ((y) / halfheight)) / 2;
		double mapy = ((y/ halfheight) - (((startx+halfwidth)-x)  / halfwidth)) / 2;
		int smapx = floor(mapx);
		int smapy = floor(mapy);
		int tilenumber = smapx * sqrt(size) + smapy;
		if (smapy >= sqrt(size) || smapx >= sqrt(size) || smapx < 0 || smapy < 0) {
			return -1;
		}
		else {
			return tilenumber;
		}
	}
private:
	Tile * tiles;
	int size;
	int tileSelectedX;
	int tileSelectedY;
	int tileSelected;
	double startx;
	double starty;
};

#endif