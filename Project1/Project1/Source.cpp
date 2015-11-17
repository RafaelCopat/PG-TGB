#include <Windows.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <sstream>
#include <string.h>
#include <cmath>
#include <math.h>  
#include <vector>
#include <fstream>
#include "Image.h"
#include "Layer.h"
#include "Element.h"
#include "Tile.h"
#include "Tilemap.h"
//Initialize Images

Tilemap tilemap;
Image tile("tile.ptm");
Image greentile("greentile.ptm");


//#define gameWidth 342
//#define gameHeight 200
//#define NUMBER_OF_TILES 49
#define gameWidth 360
#define gameHeight 180
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

void drawTileMap();

void drawTile(float x, float y, float w, float h, int r, int g, int b) {
	glColor3ub(r, g, b);
	glVertex2d(x, y);
	glVertex2d(x + w/2, y - h/2 );
	glVertex2d(x, y - h);
	glVertex2d(x - w/2, y - h/2);

}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	//glDrawPixels(gameWidth, gameHeight, GL_BGRA_EXT, GL_UNSIGNED_BYTE,
		//lastScreen.getPixels());
	int x = gameWidth / 2 - (tile.getWidth() / 2);
	int y = 180;
	tilemap.setStartCoords(x, y);
	int screenx = 0;
	int screeny = 0;
	int cont = 0;
	int multiplier = 1;
	int n = sqrt(tilemap.getSize());
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			
			screenx = x + (j - i) * (tile.getWidth()/2);
			screeny = y - (j + i) * (tile.getHeight()/2);
			int tilew = tilemap.getTile(cont).getWidth();
			int tileh = tilemap.getTile(cont).getHeight();
			int tiler = tilemap.getTile(cont).getR();
			int tileg = tilemap.getTile(cont).getG();
			int tileb = tilemap.getTile(cont).getB();
			cont++;
			glBegin(GL_QUADS);
			drawTile(screenx + tilew / 2, screeny, tilew, tileh, tiler, tileg, tileb);
			glEnd();
			glBegin(GL_LINE_LOOP);
			drawTile(screenx + tilew / 2, screeny, tilew, tileh, 255, 255, 255);
			glEnd();
		}
	}
	glFlush();

}

void init(void)
{
	for (int i = 0; i < gameWidth; i++) {
		for (int j = 0; j < gameHeight; j++) {
			lastScreen.setPixelOpaco(0, 0, 0, i, j);
		}
	}
	tilemap.setSize(NUMBER_OF_TILES);
	tilemap.setTiles(38,20,120,120,120);
	tilemap.setCenterTile();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, gameWidth, gameHeight);
	gluOrtho2D(0, gameWidth, 0, gameHeight );
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
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
void mousemap(int x, int y, int &c, int &l) {
	int a = 0;
	l = y / (tile.getHeight() / 2);

	//x = c * Tw + L * tw / 2
	//    y = L * Th / 2
}

void mouse(int button, int state, int x, int y) {
	if (GLUT_LEFT_BUTTON == button && state == GLUT_DOWN) {
	tilemap.setTileGreen(x, y);
	drawTileMap();
    }
	//tilemap.whatTileIs(x, y);
	//int c, l;
	//mousemap(x, y, c, l);
	//1 isoview->mousemap(mx, my, c, l)
	//    int x0, y0
	//    2 isoview->calcposdesenhatile(c, l, x0, y0)
	//    3 if (!pontPertenceTile(mx - x0, my - y0)){
	//    isoview->tileWalking(c, l, calc.DirecaoTW(mx - xo, m - yo, tw, th);
	//}
	//element->col = c;
	//element->lin = l;
}



int main(int argc, char** argv) {
	srand(time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(gameWidth, gameHeight);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("SuperMarioDodge");
	init();
	glutTimerFunc(100, timer, 0);
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}


