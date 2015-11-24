#include <stdlib.h>
#include "Image.h"
#include <algorithm>
#include "Tile.h"
#include <string>
#include <iostream>
#include "Texture.h"
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
	Tilemap(int gameWidth, int gameHeight) {
		this->gameWidth = gameWidth;
		this->gameHeight = gameHeight;
		characterTexture = 3;
	}

	void drawRect(float x, float y, float w, float h){
		glTexCoord2f(0, 0);
		glVertex2d(x, y);
		glTexCoord2f(0, 1);
		glVertex2d(x, y + h);
		glTexCoord2f(1, 1);
		glVertex2d(x + w, y + h);
		glTexCoord2f(1, 0);
		glVertex2d(x + w, y);
	}

	void drawTile(float x, float y, float w, float h) {

		glTexCoord2f(0, 0);
		glVertex2d(x, y);
		glTexCoord2f(0, 1);
		glVertex2d(x + w / 2, y - h / 2);
		glTexCoord2f(1, 1);
		glVertex2d(x, y - h);
		glTexCoord2f(1, 0);
		glVertex2d(x - w / 2, y - h / 2);

	}
	void drawMap() {
		int x = gameWidth / 2 - (getTile(0).getWidth() / 2);
		int y = gameHeight;
		setStartCoords(x, y);
		int screenx = 0;
		int screeny = 0;
		int cont = 0;
		int multiplier = 1;
		int n = sqrt(getSize());
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				screenx = x + (j - i) * (getTile(0).getWidth() / 2);
				screeny = y - (j + i) * (getTile(0).getHeight() / 2);
				int tilew = getTile(cont).getWidth();
				int tileh = getTile(cont).getHeight();
				glBindTexture(GL_TEXTURE_2D, getTile(cont).getTextura());
				glBegin(GL_QUADS);
				drawTile(screenx + tilew / 2, screeny, tilew, tileh);
				glEnd();
				cont++;
			}
		}
		drawCharacter();
	}
	void setTextures(Texture textures) {
		this->textures = textures;
	}
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

	void setTiles(float w, float h) {
		for (int i = 0; i < size; i++) {
			GLuint *a = textures.get_ids_tex_tiles();
			Tile tile(w, h, textures.get_ids_tex_tiles()[0]);
			tiles[i] = tile;
		}
	}
	void setCenterTile() {
		//tiles[size / 2].setTexture(textures.get_ids_tex_tiles()[1]);
		//tileSelected = size / 2;
		tileSelectedX = tiles[0].getWidth() * (sqrt(size)/2);
		tileSelectedY = tiles[0].getHeight() * (sqrt(size) / 2);
		tileSelected = size / 2;
		setTileGreen(tileSelectedX, tileSelectedY);
	}

	void drawCharacter(){
		glBindTexture(GL_TEXTURE_2D, textures.get_ids_tex_tiles()[characterTexture]);
		glBegin(GL_QUADS);
		drawRect(tileSelectedX - 40, starty - tileSelectedY - tiles[0].getHeight()/2, 80, 160);
		glEnd();
	}
	void tilewalk(const int DIRECTION) {
		int w = tiles[0].getWidth();
		int h = tiles[0].getHeight();
		int newTileX = 0;
		int newTileY = 0;
		switch (DIRECTION) {
		case NORTH:
			newTileY = tileSelectedY - h;
			newTileX = tileSelectedX;
			characterTexture = 2;
			break;
		case SOUTH:
			newTileX = tileSelectedX;
			newTileY = tileSelectedY + h;
			characterTexture = 3;
			break;
		case EAST:
			newTileX = tileSelectedX + w;
			newTileY = tileSelectedY;
			characterTexture = 4;
			break;
		case WEST:
			newTileX = tileSelectedX - w;
			newTileY = tileSelectedY;
			characterTexture = 5;
			break;
		case NORTHEAST:
			newTileX = tileSelectedX + w / 2;
			newTileY = tileSelectedY - h / 2;
			characterTexture = 6;
			break;
		case SOUTHEAST:
			newTileX = tileSelectedX + w / 2;
			newTileY = tileSelectedY + h / 2;
			characterTexture = 7;
			break;
		case NORTHWEST:
			newTileX = tileSelectedX - w / 2;
			newTileY = tileSelectedY - h / 2;
			characterTexture = 8;
			break;
		case SOUTHWEST:
			newTileX = tileSelectedX - w / 2;
			newTileY = tileSelectedY + h / 2;
			characterTexture = 9;
			break;
		}
		setTileGreen(newTileX, newTileY);
	}
	int getSize() {
		return size;
	}
	
	void setTileGreen(int x, int y) {
		int tilenumber = whatTileIs(x, y);
		if (tilenumber != -1) {
			tiles[tileSelected].setTexture(textures.get_ids_tex_tiles()[0]);
			tileSelectedX = x;
			tileSelectedY = y;
			tileSelected = tilenumber;
			tiles[tilenumber].setTexture(textures.get_ids_tex_tiles()[1]);
		}
	}

	void mouseMap(int x, int y){
		setTileGreen(x, y);
	}
	int whatTileIs(int x, int y) {
		double halfwidth = tiles[0].getWidth() / 2;
		double halfheight = tiles[0].getHeight() / 2;
		double realx = (double)x;
		double realy = (double)y;
		double mapx = ((((startx + halfwidth) - x) / halfwidth) + ((y / halfheight))) / 2;
		double mapy = ((y / halfheight) - (((startx + halfwidth) - x) / halfwidth)) / 2;
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
	Texture textures;
	int size;
	int tileSelectedX;
	int tileSelectedY;
	int tileSelected;
	double startx;
	double starty;
	int gameWidth;
	int gameHeight;
	int characterTexture;
};

#endif