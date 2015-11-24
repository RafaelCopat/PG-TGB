#include <Windows.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <cmath>
#include <fstream>
#include "Image.h"
#include "Tile.h"
#include "Tilemap.h"
#include "Texture.h"


#define gameWidth 900
#define gameHeight 450
#define NUMBER_OF_TILES 81
#define NORTH 1
#define EAST 2
#define WEST 3
#define SOUTH 4
#define NORTHEAST 5
#define SOUTHEAST 6
#define NORTHWEST 7
#define SOUTHWEST 8
#define GAME_WIN 2
#define GAME_LOSS 1
#define GAME_RUNNING 0

int GAME_STATE = 0;

Image lastScreen(gameWidth, gameHeight);
Tilemap tilemap[1];
Texture textures;

void drawTileMap();

void restart() {
	
	Tilemap map(gameWidth, gameHeight);
	tilemap[0] = map;
	GAME_STATE = 0;
	tilemap[0].setTextures(textures);
	tilemap[0].setSize(NUMBER_OF_TILES);
	tilemap[0].setTiles(100, 50);
	tilemap[0].drawMap();
	drawTileMap();
}

void display(void)
{
		glClear(GL_COLOR_BUFFER_BIT);
		GAME_STATE = tilemap[0].drawMap();
		glFlush();

}

void init(void)
{
	Tilemap map(gameWidth, gameHeight);
	tilemap[0] = map;
	GAME_STATE = 0;
	textures.init_textures();
	tilemap[0].setTextures(textures);
	tilemap[0].setSize(NUMBER_OF_TILES);
	tilemap[0].setTiles(100, 50);
	tilemap[0].drawMap();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, gameWidth, gameHeight);
	gluOrtho2D(0, gameWidth, 0, gameHeight);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	drawTileMap();
}

void drawTileMap() {

	glutPostRedisplay();

}
void timer(int value)
{


}

void keyboard(unsigned char key, int x, int y) {
	if (GAME_STATE == 0) {
		switch (key) {
		case '8':
			tilemap[0].tilewalk(NORTH);
			break;
		case '2':
			tilemap[0].tilewalk(SOUTH);
			break;
		case '6':
			tilemap[0].tilewalk(EAST);
			break;
		case '4':
			tilemap[0].tilewalk(WEST);
			break;
		case '9':
			tilemap[0].tilewalk(NORTHEAST);
			break;
		case '3':
			tilemap[0].tilewalk(SOUTHEAST);
			break;
		case '7':
			tilemap[0].tilewalk(NORTHWEST);
			break;
		case '1':
			tilemap[0].tilewalk(SOUTHWEST);
			break;
		default:
			break;
		}
		drawTileMap();
	}
	if (key == '0') {
		restart();
	}
}

void mouse(int button, int state, int x, int y) {
	if (GAME_STATE == 0) {
		if (GLUT_LEFT_BUTTON == button && state == GLUT_DOWN) {
			tilemap[0].mouseMap(x, y);
			drawTileMap();
		}
	}
}


int main(int argc, char** argv) {
	srand(time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(gameWidth, gameHeight);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Tiles");
	init();
	glutTimerFunc(100, timer, 0);
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}


