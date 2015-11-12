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
#define gameWidth 800
#define gameHeight 600

Image lastScreen(gameWidth, gameHeight);

void drawTilemap();

void display(void)
{
	
	//x = c * Tw + L * tw / 2
	//    y = L * Th / 2

	//c = coluna
	//L = linha
	//Tw = tile width
	//Th = tile height

	glClear(GL_COLOR_BUFFER_BIT);
	glDrawPixels(gameWidth, gameHeight, GL_BGRA_EXT, GL_UNSIGNED_BYTE,
		lastScreen.getPixels());
	glFlush();

}

void init(void)
{
	for (int i = 0; i < gameWidth; i++) {
		for (int j = 0; j < gameHeight; j++) {
			lastScreen.setPixelOpaco(0, 0, 0, i, j);
		}
	}
	tilemap.setSize(100);
	tilemap.setTiles(tile);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, gameWidth, gameHeight);
	gluOrtho2D(0, gameWidth, 0, gameHeight);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
}

void drawTileMap() {
	double x = 380;
	double y = 500;
	int numberOfTiles = 0;
	//Tile *tiles = tilemap.getTiles();
	int cont = 0;
	int multiplier = 1;
	int n = sqrt(tilemap.getSize())*2;
	for (int i = 1; i < n; i++) {
		if (i <= n / 2)
			numberOfTiles = i % (n / 2);
		else
			numberOfTiles--;
		if (i == n / 2) {
			numberOfTiles = n / 2;
		}
		for (int j = 0; j < numberOfTiles; j++) {
			lastScreen.plot(tilemap.getTile(cont).getImagePixels(), x, y, tile.getWidth(), tile.getHeight());
			cont++;
			x = x + tile.getWidth();
		}
		if (i < n / 2) {
			x = x - tile.getWidth() * numberOfTiles;
			x = x - tile.getWidth() / 2;
		}
		else if (i == n / 2) {
			x = x - tile.getWidth()*(numberOfTiles - 1);
			x = x - tile.getWidth() / 2;
		}
		else {
			x = x - tile.getWidth() * (numberOfTiles - 1);
			x = x - tile.getWidth() / 2;
		}
		y = y - (tile.getHeight() / 2);
	}
	glutPostRedisplay();
}
void timer(int value)
{


}

void keyboard(unsigned char key, int x, int y) {

}
void mousemap(int x, int y, int &c, int &l) {
	int a = 0;
	l = y / (tile.getHeight() / 2);

	//x = c * Tw + L * tw / 2
	//    y = L * Th / 2
}

void mouse(int button, int state, int x, int y) {
	drawTileMap();

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

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h);
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
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}


