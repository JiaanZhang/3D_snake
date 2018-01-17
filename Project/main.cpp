#define _CRT_SECURE_NO_WARNINGS

#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif

//#include <GL/glut.h>
#include "scene.h"
#include <array>
#include <cmath>
#include <time.h>
#include <iostream>



//---------General information --------------------------------
float cubeSize = 12;
int size = 12;
float width = 600;
float height = 600;
int width1, height1, max1;
float origin[3] = { 6,6,6 };
//-------------------------------------------------------------
//--------camera parameter ------------------------------------
float camPos[] = { 30,30,30 };
float camPos1[] = { 30,30,30 };
float camPos2[] = { -20,-20,-20 };
//float camPos3[] = { -30,-30,-30 };
//float camPos4[] = { -30,30,-30 };
float camTarget[] = { 6, 6, 6 };
//--------------------------------------------------------------

//--------playground parameter ---------------------------------
float cols[6][3] = { { 1,1,1 },{ 1,1,1 },{ 1,1,1 },{ 1,1,1 },{ 1,1,1 },{ 1,1,1 } };
GLubyte* f1_tex;
GLubyte* f2_tex;
GLubyte* f3_tex;
GLubyte* f4_tex;
GLubyte* f5_tex;
GLubyte* f6_tex;
GLubyte* f7_tex;
GLubyte* f8_tex;
GLubyte* f9_tex;
GLuint textures[9];
//--------------------------------------------------------------

//--------Game logic--------------------------------------------
string str1 = "Current Diffculty: Easy";
string str2 = "Current Background: 1";
string str3 = "Background Follow: OFF";
int diffculty = 1;
int background = 1;
bool option = false;
bool istitle = true;
bool ishelp = false;
int mode = 2;
int plane = 1;
Snake snk;
std::array<float, 3> headpos;
std::vector<body> food_list;
body food;
std::array<float, 3> cood;
float coo[3];
bool game_end = true;
bool pause = false;
bool back_follow = false;
bool moved = true;
//float* headpos;
//----------------------------------------------------------

//-------Light setup -----------
float light0_pos[] = { 15,15,15,0 };
float light1_pos[] = { -15, -15, -15, 0 };
float light2_pos[] = { 15, -15, 15, 0 };
float light3_pos[] = { 15, 15, -15, 0 };
float light4_pos[] = { -15, 15, 15, 0 };
//Lighting values for light0
float amb0[4] = { 1, 1, 1, 1 };
float diff0[4] = { 1, 1, 1, 1 };
float spec0[4] = { 1, 1, 1, 1 };

//-------------------------------

void changeCamera(int c)
{
	switch (c) {
	case 1:
		camPos[0] = camPos1[0];
		camPos[1] = camPos1[1];
		camPos[2] = camPos1[2];

		break;
	case 2:
		camPos[0] = camPos2[0];
		camPos[1] = camPos2[1];
		camPos[2] = camPos2[2];

		break;

	}
}

void printstart(int x, int y, string String)
{
	//(x,y) is from the bottom left of the window
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glPushAttrib(GL_DEPTH_TEST);
	glDisable(GL_DEPTH_TEST);
	glRasterPos2i(x, y);
	for (int i = 0; i<String.size(); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, String[i]);
	}
	glPopAttrib();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void hint(string str)
{
	char string[64];
	printstart(140, 170, str);
}


void hint2(string str)
{
	char string[64];
	printstart(140, 130, str);
}
void hint3(string str)
{
	char string[64];
	printstart(140, 90, str);
}

void help()
{
	char string[64];

	sprintf(string, "Help");
	printstart(250, 240, string);
}

void mouse(int btn, int state, int x, int y) {
	//printf("mouseFunc coords: %i,%i\n", x, y);

	if (btn == GLUT_LEFT_BUTTON)
	{
		if (istitle)
		{
			if (x > 225 && x < 339)
			{
				if (y > 222 && y < 265)
				{
					printf("new game\n");
					snk = Snake();
					changeCamera(1);
					mode = 2;
					plane = 1;
					istitle = false;
				}
			}

			if (x > 225 && x < 339)
			{
				if (y > 327 && y < 377)
				{
					ishelp = true;
					istitle = false;
				}
			}

			if (x > 241 && x < 316)
			{
				if (y > 277 && y < 315)//option
				{
					option = true;
					istitle = false;
				}
			}

			if (x > 241 && x < 316)
			{
				if (y > 381 && y < 413)//option
				{
					exit(0);
				}
			}
		}
		else if (ishelp)
		{
			if (x > 0 && x < 80)
			{
				if (y > 0 && y < 45)
				{
					ishelp = false;
					istitle = true;
				}
			}
		}
		else if (option)
		{
			if (x > 210 && x < 252)
			{
				if (y > 135 && y < 159)
				{
					//easy
					diffculty = 1;
					str1 = "Current Diffculty: Easy";
				}
			}
			if (x > 276 && x < 337)
			{
				if (y > 135 && y < 159)
				{
					//medium
					diffculty = 2;
					str1 = "Current Diffculty: Medium";
				}
			}
			if (x > 363 && x < 395)
			{
				if (y > 135 && y < 159)
				{
					//hard
					diffculty = 3;
					str1 = "Current Diffculty: Hard";
				}
			}

			if (x > 217 && x < 231)
			{
				if (y > 238 && y < 254)
				{
					//1
					background = 1;
					str2 = "Current Background: 1";
				}
			}
			if (x > 247 && x < 263)
			{
				if (y > 238 && y < 254)
				{
					//2
					background = 2;
					str2 = "Current Background: 2";
				}
			}
			if (x > 277 && x < 291)
			{
				if (y > 238 && y < 254)
				{
					//3
					background = 3;
					str2 = "Current Background: 3";
				}
			}
			if (x > 307 && x < 322)
			{
				if (y > 238 && y < 254)
				{
					//4
					background = 4;
					str2 = "Current Background: 4";
				}
			}
			if (x > 339 && x < 350)
			{
				if (y > 238 && y < 254)
				{
					//5
					background = 5;
					str2 = "Current Background: 5";
				}
			}
			if (x > 367 && x < 381)
			{
				if (y > 238 && y < 254)
				{
					//6
					background = 6;
					str2 = "Current Background: 6";
				}
			}
			if (x > 367 && x < 381)
			{
				if (y > 238 && y < 254)
				{
					//6
					background = 6;
					str2 = "Current Background: 6";
				}
			}

			if (x > 210 && x < 260)
			{
				if (y > 340 && y < 360)
				{
					//6
					back_follow = true;
					str3 = "Background Follow: ON";
				}
			}
			if (x > 320 && x < 370)
			{
				if (y > 340 && y < 360)
				{
					//6
					back_follow = false;
					str3 = "Background Follow: OFF";
				}
			}


			if (x > 0 && x < 80)
			{
				if (y > 0 && y < 45)
				{
					option = false;
					istitle = true;
				}
			}
		}
		else
		{
			if (x > 0 && x < 80)
			{
				if (y > 0 && y < 45)
				{
					option = false;
					istitle = true;
				}
			}
		}
	}

}

void menuProc(int id)
{
	if (id == 1) { exit(0); }
	if (id == 2) { std::cout << "2" << endl; }

}

void CreateOurMenu(void)
{
	int MainMenu = glutCreateMenu(menuProc);

	glutAddMenuEntry("Quit", 1);
	glutAddMenuEntry("Clear", 2);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void drawPolygon(int a, int b, int c, int d, float v[8][3]) {
	glBegin(GL_POLYGON);

	glTexCoord2f(0, 0);
	glVertex3fv(v[a]);

	glTexCoord2f(0, 1);
	glVertex3fv(v[b]);

	glTexCoord2f(1, 1);
	glVertex3fv(v[c]);

	glTexCoord2f(1, 0);
	glVertex3fv(v[d]);
	glEnd();
}


void drawSPolygon(int a, int b, int c, int d, float v[8][3], int i, int n, int s) {


	float i1 = (float)i;
	float b1 = (float)s;
	float n1 = (float)n;
	glBegin(GL_POLYGON);

	glTexCoord2f(i1 / n1 *b1, i1 / n1 *b1);
	glVertex3fv(v[a]);

	glTexCoord2f(i1 / n1 *b1, (i1 + 1) / n1 *b1);
	glVertex3fv(v[b]);

	glTexCoord2f((i1 + 1) / n1 *b1, (i1 + 1) / n1 *b1);
	glVertex3fv(v[c]);

	glTexCoord2f((i1 + 1) / n1 *b1, i1 / n1 *b1);
	glVertex3fv(v[d]);
	glEnd();
}

void drawcube(float v[8][3], int in)
{
	glBindTexture(GL_TEXTURE_2D, textures[in]);
	glColor3fv(cols[1]);
	drawPolygon(0, 3, 2, 1, v);

	glBindTexture(GL_TEXTURE_2D, textures[in]);
	glColor3fv(cols[2]);
	drawPolygon(1, 0, 4, 5, v);

	glBindTexture(GL_TEXTURE_2D, textures[in]);
	glColor3fv(cols[3]);
	drawPolygon(5, 1, 2, 6, v);

	glBindTexture(GL_TEXTURE_2D, textures[in]);
	glColor3fv(cols[4]);
	drawPolygon(2, 3, 7, 6, v);

	glBindTexture(GL_TEXTURE_2D, textures[in]);
	glColor3fv(cols[5]);
	drawPolygon(6, 5, 4, 7, v);

	glBindTexture(GL_TEXTURE_2D, textures[in]);
	glColor3fv(cols[0]);
	drawPolygon(4, 0, 3, 7, v);
}



void drawcube_follow(float v[8][3], int plane)
{
	if (plane == 2) {
		glBindTexture(GL_TEXTURE_2D, textures[0]);
	}
	else {
		glBindTexture(GL_TEXTURE_2D, textures[8]);
	}

	glColor3fv(cols[1]);
	drawPolygon(0, 3, 2, 1, v);

	if (plane == 4) {
		glBindTexture(GL_TEXTURE_2D, textures[1]);
	}
	else {
		glBindTexture(GL_TEXTURE_2D, textures[8]);
	}
	glColor3fv(cols[2]);
	drawPolygon(1, 0, 4, 5, v);

	if (plane == 1) {
		glBindTexture(GL_TEXTURE_2D, textures[2]);
	}
	else {
		glBindTexture(GL_TEXTURE_2D, textures[8]);
	}
	glColor3fv(cols[3]);
	drawPolygon(5, 1, 2, 6, v);

	if (plane == 3) {
		glBindTexture(GL_TEXTURE_2D, textures[3]);
	}
	else {
		glBindTexture(GL_TEXTURE_2D, textures[8]);
	}
	glColor3fv(cols[4]);
	drawPolygon(2, 3, 7, 6, v);

	if (plane == 5) {
		glBindTexture(GL_TEXTURE_2D, textures[4]);
	}
	else {
		glBindTexture(GL_TEXTURE_2D, textures[8]);
	}
	glColor3fv(cols[5]);
	drawPolygon(6, 5, 4, 7, v);

	if (plane == 6) {
		glBindTexture(GL_TEXTURE_2D, textures[5]);
	}
	else {
		glBindTexture(GL_TEXTURE_2D, textures[8]);
	}
	glColor3fv(cols[0]);
	drawPolygon(4, 0, 3, 7, v);
}


void drawsnake(float v[8][3], int i, int n)
{
	glBindTexture(GL_TEXTURE_2D, textures[7]);
	glColor3fv(cols[1]);
	drawSPolygon(0, 3, 2, 1, v, i, n, 3);

	// glBindTexture(GL_TEXTURE_2D, textures[7]);
	glColor3fv(cols[2]);
	drawSPolygon(1, 0, 4, 5, v, i, n, 3);

	// glBindTexture(GL_TEXTURE_2D, textures[7]);
	glColor3fv(cols[3]);
	drawSPolygon(5, 1, 2, 6, v, i, n, 2);

	//   glBindTexture(GL_TEXTURE_2D, textures[7]);
	glColor3fv(cols[4]);
	drawSPolygon(2, 3, 7, 6, v, i, n, 3);
	//  glBindTexture(GL_TEXTURE_2D, textures[7]);
	glColor3fv(cols[5]);
	drawSPolygon(6, 5, 4, 7, v, i, n, 1);

	//glBindTexture(GL_TEXTURE_2D, textures[7]);
	glColor3fv(cols[0]);
	drawSPolygon(4, 0, 3, 7, v, i, n, 3);
}

void drawBox(float* c, float w, float h, float d, int in, bool follow, int plane)
{
	float vertices[8][3] = { { c[0] - w / 2, c[1] - h / 2, c[2] + d / 2 },
	{ c[0] - w / 2, c[1] + h / 2, c[2] + d / 2 },
	{ c[0] + w / 2, c[1] + h / 2, c[2] + d / 2 },
	{ c[0] + w / 2, c[1] - h / 2, c[2] + d / 2 },
	{ c[0] - w / 2, c[1] - h / 2, c[2] - d / 2 },
	{ c[0] - w / 2, c[1] + h / 2, c[2] - d / 2 },
	{ c[0] + w / 2, c[1] + h / 2, c[2] - d / 2 },
	{ c[0] + w / 2, c[1] - h / 2, c[2] - d / 2 } };

	if (follow) {
		drawcube_follow(vertices, plane);

	}
	else {
		drawcube(vertices, in);
	}

}

void drawbsnake(float* c, float w, float h, float d, int i, int n)
{
	float vertices[8][3] = { { c[0] - w / 2, c[1] - h / 2, c[2] + d / 2 },
	{ c[0] - w / 2, c[1] + h / 2, c[2] + d / 2 },
	{ c[0] + w / 2, c[1] + h / 2, c[2] + d / 2 },
	{ c[0] + w / 2, c[1] - h / 2, c[2] + d / 2 },
	{ c[0] - w / 2, c[1] - h / 2, c[2] - d / 2 },
	{ c[0] - w / 2, c[1] + h / 2, c[2] - d / 2 },
	{ c[0] + w / 2, c[1] + h / 2, c[2] - d / 2 },
	{ c[0] + w / 2, c[1] - h / 2, c[2] - d / 2 } };

	drawsnake(vertices, i, n + 10);
}

void special(int key, int xIn, int yIn) {
	switch (key) {
	case GLUT_KEY_DOWN:
	{
		if (!pause && moved)
		{
			switch (plane) {
			case 1:
				if (mode == 1 || mode == 2) {
					mode = 5;
				}
				break;
			case 2:
				if (mode == 1 || mode == 2) {
					mode = 4;
				}
				break;
			case 3:
				if (mode == 5 || mode == 6) {
					mode = 4;
				}
				break;
			case 4:
				if (mode == 5 || mode == 6) {
					mode = 4;
				}
				break;
			case 5:
				if (mode == 1 || mode == 2) {
					mode = 4;
				}
				break;
			case 6:
				if (mode == 5 || mode == 6) {
					mode = 1;
				}
				break;
			}
            moved = false;
		}
        
    }
	break;
	case GLUT_KEY_UP:
	{
		if (!pause && moved)
		{
			switch (plane) {
			case 1:
				if (mode == 1 || mode == 2) {
					mode = 6;
				}
				break;
			case 2:
				if (mode == 1 || mode == 2) {
					mode = 3;
				}
				break;
			case 3:
				if (mode == 5 || mode == 6) {
					mode = 3;
				}
				break;
			case 4:
				if (mode == 5 || mode == 6) {
					mode = 3;
				}
				break;
			case 5:
				if (mode == 1 || mode == 2) {
					mode = 3;
				}
				break;
			case 6:
				if (mode == 5 || mode == 6) {
					mode = 2;
				}
				break;
			}
            moved = false;
		}}

	break;
	case GLUT_KEY_LEFT:

	{
		if (!pause && moved)
		{
			switch (plane ) {
			case 1:
				if (mode == 5 || mode == 6) {
					mode = 2;
				}
				break;
			case 2:
				if (mode == 3 || mode == 4) {
					mode = 2;
				}
				break;
			case 3:
				if (mode == 3 || mode == 4) {
					mode = 5;
				}
				break;
			case 4:
				if (mode == 3 || mode == 4) {
					mode = 6;
				}
				break;
			case 5:
				if (mode == 3 || mode == 4) {
					mode = 1;
				}
				break;
			case 6:
				if (mode == 1 || mode == 2) {
					mode = 6;
				}
				break;
			}
            moved = false;
		}}
	break;
	case GLUT_KEY_RIGHT:
	{
		if (!pause && moved)
		{
			switch (plane) {
			case 1:
				if (mode == 5 || mode == 6) {
					mode = 1;
				}
				break;
			case 2:
				if (mode == 3 || mode == 4) {
					mode = 1;
				}
				break;
			case 3:
				if (mode == 3 || mode == 4) {
					mode = 6;
				}
				break;
			case 4:
				if (mode == 3 || mode == 4) {
					mode = 5;
				}
				break;
			case 5:
				if (mode == 3 || mode == 4) {
					mode = 2;
				}
				break;
			case 6:
				if (mode == 1 || mode == 2) {
					mode = 5;
				}
				break;
			}
            moved = false;
		}}
	break;
	}
}

void helpmenu()
{
	char string[64];

	sprintf(string, "<-");
	printstart(50, 400, string);

	sprintf(string, "->");
	printstart(100, 400, string);

	sprintf(string, "^");
	printstart(82, 425, string);

	sprintf(string, "|");
	printstart(82, 420, string);

	sprintf(string, "|");
	printstart(82, 405, string);

	sprintf(string, "v");
	printstart(82, 400, string);

	sprintf(string, "Arrow key to control the direction of snake");
	printstart(150, 405, string);

	sprintf(string, "S");
	printstart(82, 350, string);

	sprintf(string, "'S' key to pause the game");
	printstart(150, 350, string);

	sprintf(string, "q");
	printstart(82, 300, string);

	sprintf(string, "'q' key or click 'Exit' in title page to exit");
	printstart(150, 300, string);

	sprintf(string, "r");
	printstart(82, 250, string);

	sprintf(string, "'r' key or click 'new game' to start a new game");
	printstart(150, 250, string);

	sprintf(string, "option");
	printstart(65, 200, string);

	sprintf(string, "Click 'option' in title page to");
	printstart(150, 200, string);
	sprintf(string, "switch background or change diffculty");
	printstart(150, 188, string);

	sprintf(string, "<- Back");
	printstart(65, 140, string);

	sprintf(string, "Click '<- Back' to title page");
	printstart(150, 140, string);
}

void food_generate() {
	int x = rand() % 6 + 1;
	float num1 = rand() % 12;//size------------------------
	float num2 = rand() % 12;//size------------------------

	switch (x) {
	case 1:
		food = body(num1, cubeSize, num2);
		food.get_food(x);
		food_list.push_back(food);
		break;
	case 2:
		food = body(num1, num2, cubeSize);
		food.get_food(x);
		food_list.push_back(food);
		break;
	case 3:
		food = body(cubeSize, num1, num2);
		food.get_food(x);
		food_list.push_back(food);
		break;
	case 4:
		food = body(0, num1, num2);
		food.get_food(x);
		food_list.push_back(food);
		break;
	case 5:
		food = body(num1, num2, 0);
		food.get_food(x);
		food_list.push_back(food);
		break;
	case 6:
		food = body(num1, 0, num2);
		food.get_food(x);
		food_list.push_back(food);
		break;

	}
}


GLubyte* LoadPPM(char* file, int* width, int* height, int* max)
{
	GLubyte* img;
	FILE *fd;
	int n, m;
	int  k, nm;
	char c;
	int i;
	char b[100];
	float s;
	int red, green, blue;

	fd = fopen(file, "r");
	fscanf(fd, "%[^\n] ", b);
	if (b[0] != 'P' || b[1] != '3')
	{
		printf("%s is not a PPM file!\n", file);
		exit(0);
	}
	printf("%s is a PPM file\n", file);
	fscanf(fd, "%c", &c);
	while (c == '#')
	{
		fscanf(fd, "%[^\n] ", b);
		printf("%s\n", b);
		fscanf(fd, "%c", &c);
	}
	ungetc(c, fd);
	fscanf(fd, "%d %d %d", &n, &m, &k);

	printf("%d rows  %d columns  max value= %d\n", n, m, k);

	nm = n*m;

	img = (GLubyte*)malloc(3 * sizeof(GLuint)*nm);


	s = 255.0 / k;


	for (i = 0; i<nm; i++)
	{
		fscanf(fd, "%d %d %d", &red, &green, &blue);
		img[3 * nm - 3 * i - 3] = red*s;
		img[3 * nm - 3 * i - 2] = green*s;
		img[3 * nm - 3 * i - 1] = blue*s;
	}

	*width = n;
	*height = m;
	*max = k;

	return img;
}



void picture() {

	glEnable(GL_TEXTURE_2D);

	//generate 2 texture IDs, store them in array "textures"
	glGenTextures(9, textures);

	//load the texture (snail)
	f1_tex = LoadPPM("1.ppm", &width1, &height1, &max1);

	//setup first texture (using snail image)
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	//set texture parameters
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	//create a texture using the "snail_tex" array data
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width1, height1, 0, GL_RGB, GL_UNSIGNED_BYTE, f1_tex);

	//load the texture (marble)
	f2_tex = LoadPPM("2.ppm", &width1, &height1, &max1);

	//setup second texture (using marble image)
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	//set texture parameters
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//create a texture using the "tex" array
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width1, height1, 0, GL_RGB, GL_UNSIGNED_BYTE, f2_tex);

	//load the texture (marble)
	f3_tex = LoadPPM("3.ppm", &width1, &height1, &max1);

	//setup second texture (using marble image)
	glBindTexture(GL_TEXTURE_2D, textures[2]);
	//set texture parameters
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//create a texture using the "tex" array
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width1, height1, 0, GL_RGB, GL_UNSIGNED_BYTE, f3_tex);


	//load the texture (marble)
	f4_tex = LoadPPM("4.ppm", &width1, &height1, &max1);

	//setup second texture (using marble image)
	glBindTexture(GL_TEXTURE_2D, textures[3]);
	//set texture parameters
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//create a texture using the "tex" array
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width1, height1, 0, GL_RGB, GL_UNSIGNED_BYTE, f4_tex);



	//load the texture (marble)
	f5_tex = LoadPPM("5.ppm", &width1, &height1, &max1);

	//setup second texture (using marble image)
	glBindTexture(GL_TEXTURE_2D, textures[4]);
	//set texture parameters
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//create a texture using the "tex" array
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width1, height1, 0, GL_RGB, GL_UNSIGNED_BYTE, f5_tex);



	//load the texture (marble)
	f6_tex = LoadPPM("6.ppm", &width1, &height1, &max1);

	//setup second texture (using marble image)
	glBindTexture(GL_TEXTURE_2D, textures[5]);
	//set texture parameters
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//create a texture using the "tex" array
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width1, height1, 0, GL_RGB, GL_UNSIGNED_BYTE, f6_tex);


	//load the texture (marble)
	f7_tex = LoadPPM("apple.ppm", &width1, &height1, &max1);

	//setup second texture (using marble image)
	glBindTexture(GL_TEXTURE_2D, textures[6]);
	//set texture parameters
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//create a texture using the "tex" array
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width1, height1, 0, GL_RGB, GL_UNSIGNED_BYTE, f7_tex);


	//load the texture (marble)
	f8_tex = LoadPPM("snake.ppm", &width1, &height1, &max1);

	//setup second texture (using marble image)
	glBindTexture(GL_TEXTURE_2D, textures[7]);
	//set texture parameters
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//create a texture using the "tex" array
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width1, height1, 0, GL_RGB, GL_UNSIGNED_BYTE, f8_tex);

	//load the texture (marble)
	f9_tex = LoadPPM("wall.ppm", &width1, &height1, &max1);

	//setup second texture (using marble image)
	glBindTexture(GL_TEXTURE_2D, textures[8]);
	//set texture parameters
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//create a texture using the "tex" array
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width1, height1, 0, GL_RGB, GL_UNSIGNED_BYTE, f9_tex);

}



void draw_snake() {

	int si = snk.snake_size();
	for (int i = 0; i < si; i++) {
		cood = snk.vposition(i);
		coo[0] = cood[0];
		coo[1] = cood[1];
		coo[2] = cood[2];

		drawbsnake(coo, 1, 1, 1, i, si);
	}


}


void init(void)
{
	glClearColor(1, 1, 1, 0);
	picture();
	glColor3f(0, 0, 0);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHT3);
	glEnable(GL_LIGHT4);

	glShadeModel(GL_SMOOTH);
	//glFrontFace(GL_CW);
	// glCullFace(GL_BACK);
	// glEnable(GL_CULL_FACE);


	glMatrixMode(GL_PROJECTION);
	glEnable(GL_DEPTH_TEST);
	glLoadIdentity();
	gluPerspective(45, (float)((width + 0.0f) / height), 1, 500);
	Snake snk = Snake();
	headpos = snk.position();
	food_generate();

	glPushMatrix();


	glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, amb0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diff0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, spec0);
	glLightfv(GL_LIGHT1, GL_POSITION, light1_pos);
	glLightfv(GL_LIGHT1, GL_AMBIENT, amb0);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diff0);
	glLightfv(GL_LIGHT1, GL_SPECULAR, spec0);
	glLightfv(GL_LIGHT2, GL_POSITION, light2_pos);
	glLightfv(GL_LIGHT2, GL_AMBIENT, amb0);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, diff0);
	glLightfv(GL_LIGHT2, GL_SPECULAR, spec0);
	glLightfv(GL_LIGHT3, GL_POSITION, light3_pos);
	glLightfv(GL_LIGHT3, GL_AMBIENT, amb0);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, diff0);
	glLightfv(GL_LIGHT3, GL_SPECULAR, spec0);
	glLightfv(GL_LIGHT4, GL_POSITION, light4_pos);
	glLightfv(GL_LIGHT4, GL_AMBIENT, amb0);
	glLightfv(GL_LIGHT4, GL_DIFFUSE, diff0);
	glLightfv(GL_LIGHT4, GL_SPECULAR, spec0);


	glPopMatrix();

}

void printtext(int x, int y, string String, float scale, float xpos, float ypos)
{
	//(x,y) is from the bottom left of the window
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glPushAttrib(GL_DEPTH_TEST);
	glDisable(GL_DEPTH_TEST);
	glRasterPos2i(x, y);
	glScalef(scale, scale, scale);
	glTranslatef(xpos, ypos, 0);

	for (int i = 0; i<String.size(); i++)
	{
		glutStrokeCharacter(GLUT_STROKE_ROMAN, String[i]);
	}
	glPopAttrib();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}




void gameover()
{
	char string[64];
	sprintf(string, "Game Over");
	printtext(400, 300, string, 0.3, 300, 300);
}

void title()
{
	char string[64];
	sprintf(string, "New Game");
	printstart(238, 340, string);

	sprintf(string, "Exit Game");
	printstart(231, 190, string);

	sprintf(string, "3D SNAKE");
	printtext(400, 300, string, 0.5, 250, 900);

	sprintf(string, "Option");
	printstart(245, 290, string);

	sprintf(string, "V 1.0.0");
	printstart(6, 6, string);
}

void restarttitle()
{
	char string[64];
	sprintf(string, "<- Back");
	printstart(10, 570, string);
}

void showoption()
{
	char string[64];

	sprintf(string, "Game Diffculty");
	printstart(237, 500, string);

	sprintf(string, "Easy");
	printstart(215, 450, string);

	sprintf(string, "Medium");
	printstart(280, 450, string);

	sprintf(string, "Hard");
	printstart(355, 450, string);

	sprintf(string, "Background");
	printstart(250, 400, string);

	sprintf(string, "1");
	printstart(215, 350, string);

	sprintf(string, "2");
	printstart(245, 350, string);

	sprintf(string, "3");
	printstart(275, 350, string);

	sprintf(string, "4");
	printstart(305, 350, string);

	sprintf(string, "5");
	printstart(335, 350, string);

	sprintf(string, "6");
	printstart(365, 350, string);

	sprintf(string, "Background Follow");
	printstart(220, 300, string);

	sprintf(string, "ON");
	printstart(230, 250, string);

	sprintf(string, "OFF");
	printstart(340, 250, string);


	sprintf(string, "<- Back");
	printstart(10, 570, string);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(camPos[0], camPos[1], camPos[2], camTarget[0], camTarget[1], camTarget[2], 0, 1, 0);

	if (istitle)
	{
		title();
		help();
	}
	else if (option)
	{
		showoption();
		hint(str1);
		hint2(str2);
		hint3(str3);
		//char string[64];
		//printstart(270, 270, str);
	}
	else if (ishelp)
	{
		restarttitle();
		helpmenu();
	}
	else
	{
		restarttitle();
		glColor3f(0, 1, 0);

		headpos = snk.position();

		glColor3f(1, 0, 0);
		for (int i = 0; i < food_list.size(); i++) {
			if (headpos[0] == food_list[i].getX() && headpos[1] == food_list[i].getY() && headpos[2] == food_list[i].getZ()) {
				snk.col_food();
				food.dele_food();
				food_list.erase(food_list.begin() + i);
				food_generate();

			}
		}
		glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, textures[6]);
		food.draw_food();
		glPopMatrix();

		glPushMatrix();
		drawBox(origin, 12, 12, 12, background - 1, back_follow, plane);
		glPopMatrix();
		switch (mode) {
		case 1:
			if (headpos[0] == 12 && headpos[1] == 12) {
				mode = 4;
				plane = 3;
				changeCamera(1);
			}
			if (headpos[0] == 12 && headpos[1] == 0) {
				mode = 3;
				plane = 3;
				changeCamera(1);
			}
			if (headpos[0] == 12 && headpos[2] == 12) {
				mode = 6;
				plane = 3;
				changeCamera(1);
			}
			if (headpos[0] == 12 && headpos[2] == 0) {
				mode = 5;
				plane = 3;
				changeCamera(1);
			}

			break;
		case 2:
			if (headpos[0] == 0 && headpos[1] == 12) {
				mode = 4;
				plane = 4;
				changeCamera(2);
			}
			if (headpos[0] == 0 && headpos[1] == 0) {
				mode = 3;
				plane = 4;
				changeCamera(2);
			}
			if (headpos[0] == 0 && headpos[2] == 12) {
				mode = 6;
				plane = 4;
				changeCamera(2);
			}
			if (headpos[0] == 0 && headpos[2] == 0) {
				mode = 5;
				plane = 4;
				changeCamera(2);
			}
			break;
		case 3:
			if (headpos[2] == 12 && headpos[1] == 12) {
				mode = 6;
				plane = 1;
				changeCamera(1);
			}
			if (headpos[2] == 0 && headpos[1] == 12) {
				mode = 5;
				plane = 1;
				changeCamera(1);
			}
			if (headpos[0] == 12 && headpos[1] == 12) {
				mode = 2;
				plane = 1;
				changeCamera(1);
			}
			if (headpos[0] == 0 && headpos[1] == 12) {
				mode = 1;
				plane = 1;
				changeCamera(1);
			}
			break;
		case 4:
			if (headpos[2] == 12 && headpos[1] == 0) {
				mode = 6;
				plane = 6;
				changeCamera(2);
			}
			if (headpos[2] == 0 && headpos[1] == 0) {
				mode = 5;
				plane = 6;
				changeCamera(2);
			}
			if (headpos[0] == 12 && headpos[1] == 0) {
				mode = 2;
				plane = 6;
				changeCamera(2);
			}
			if (headpos[0] == 0 && headpos[1] == 0) {
				mode = 1;
				plane = 6;
				changeCamera(2);
			}
			break;
		case 5:
			if (headpos[2] == 12 && headpos[0] == 12) {
				mode = 2;
				plane = 2;
				changeCamera(1);
			}
			if (headpos[2] == 12 && headpos[0] == 0) {
				mode = 1;
				plane = 2;
				changeCamera(1);
			}
			if (headpos[2] == 12 && headpos[1] == 12) {
				mode = 4;
				plane = 2;
				changeCamera(1);
			}
			if (headpos[2] == 12 && headpos[1] == 0) {
				mode = 3;
				plane = 2;
				changeCamera(1);
			}
			break;
		case 6:
			if (headpos[2] == 0 && headpos[0] == 12) {
				mode = 2;
				plane = 5;
				changeCamera(2);
			}
			if (headpos[2] == 0 && headpos[0] == 0) {
				mode = 1;
				plane = 5;
				changeCamera(2);
			}
			if (headpos[2] == 0 && headpos[1] == 12) {
				mode = 4;
				plane = 5;
				changeCamera(2);
			}

			if (headpos[2] == 0 && headpos[1] == 0) {
				mode = 3;
				plane = 5;
				changeCamera(2);
			}
			break;
		}



		glPushMatrix();
		glColor3f(0, 0, 1);
		if (!pause)
		{
            
			snk.move(mode);
                moved = true;
            

		}
		if (pause)
		{
			char string[64];

			sprintf(string, "Pausing");
			printstart(20, 20, string);

			snk.stop_move();
		}
		snk.stop_move();
		if (snk.get_move()) {
			if (!game_end) {
				printf("Game End press r for restart");

			}
			game_end = true;

			gameover();

		}
		else {

		}
		glPushMatrix();
		draw_snake();
		glPopMatrix();
		glPopMatrix();
	}



	glutSwapBuffers();
}

void keyboard(unsigned char key, int xIn, int yIn)
{
	int mod = glutGetModifiers();
	switch (key)
	{
	case 'q':
	case 27:
	{
		exit(0);
		break;
	}
	case 'r':
	{
		snk = Snake();
		changeCamera(1);
		mode = 2;
		plane = 1;
		game_end = true;
        break;
        
	}
            
	case 's':
	case 'S':

		pause = !pause;
		break;
	}
}

void reshape(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, (float)((w + 0.0f) / h), 1, 50000);

	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, w, h);
}

void FPSTimer(int value) { //60fps

	switch (diffculty) {
	case 1:
		glutTimerFunc(250, FPSTimer, 0);
		break;

	case 2:
		glutTimerFunc(120, FPSTimer, 0);
		break;

	case 3:
		glutTimerFunc(60, FPSTimer, 0);
		break;
	}

	glutPostRedisplay();
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);		//starts up GLUT
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	glutInitWindowSize(width, height);
	glutInitWindowPosition(50, 50);

	glutCreateWindow("3D Snake");	//creates the window

									//display callback
	CreateOurMenu();
	srand((int)time(NULL));
	glEnable(GL_BLEND);
	glutDisplayFunc(display);
	//keyboard callback
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	glutMouseFunc(mouse);
	//resize callback
	glutReshapeFunc(reshape);

	//fps timer callback


	glutTimerFunc(17, FPSTimer, 0);

	init();

	glutMainLoop();				//starts the event glutMainLoop
	return(0);					//return may not be necessary on all compilers
}
