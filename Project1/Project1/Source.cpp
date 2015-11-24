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

Image lastScreen(gameWidth, gameHeight);
Tilemap tilemap(gameWidth, gameHeight);
Texture textures;

void drawTileMap();



void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	tilemap.drawMap();
	glFlush();

}

void init(void)
{
	textures.init_textures();
	tilemap.setTextures(textures);
	for (int i = 0; i < gameWidth; i++) {
		for (int j = 0; j < gameHeight; j++) {
			lastScreen.setPixelOpaco(0, 0, 0, i, j);
		}
	}
	tilemap.setSize(NUMBER_OF_TILES);
	tilemap.setTiles(100, 50);
	tilemap.drawMap();
	tilemap.setCenterTile();
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
	switch (key) {
	case '8':
		tilemap.tilewalk(NORTH);
		break;
	case '2':
		tilemap.tilewalk(SOUTH);
		break;
	case '6':
		tilemap.tilewalk(EAST);
		break;
	case '4':
		tilemap.tilewalk(WEST);
		break;
	case '9':
		tilemap.tilewalk(NORTHEAST);
		break;
	case '3':
		tilemap.tilewalk(SOUTHEAST);
		break;
	case '7':
		tilemap.tilewalk(NORTHWEST);
		break;
	case '1':
		tilemap.tilewalk(SOUTHWEST);
		break;
	default:
		break;
	}
	drawTileMap();
}

void mouse(int button, int state, int x, int y) {
	if (GLUT_LEFT_BUTTON == button && state == GLUT_DOWN) {
		tilemap.mouseMap(x, y);
		drawTileMap();
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


