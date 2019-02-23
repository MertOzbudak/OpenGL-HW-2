//#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 600
#define  TIMER_PERIOD  50 // Period for the timer.
#define  TIMER_ON     1    // 0:disable timer, 1:enable timer
#define D2R 0.0174532


bool check = false;
/* Global Variables for Template File */
bool up = false, down = false, right = false, left = false;
int  winWidth, winHeight; // current Window width and height
//STRUCTURES 
typedef struct {
	float x,
		y;
} point_t;
typedef struct {
	point_t start;
	float m;

} line_t;
typedef struct{
	point_t A, B, C, D;
}recang_t;
typedef struct
{
	point_t main;
	float rad;
}circle_t;

line_t  line[4];//array for 4 lines
circle_t circle = { { -200, 15 }, { 3 } };//lightsource
recang_t rec = { { 20, -40 }, { 20, 100 }, { 160, -40 }, { 160, 100 } };//square coordinats
//
// to draw circle, center at (x,y)
//  radius r
//
void circlel(int x, int y, int r)
{
#define PI 3.1415
	float angle;
	glBegin(GL_POLYGON);
	for (int i = 0; i < 100; i++)
	{
		angle = 2 * PI*i / 100;
		glVertex2f(x + r*cos(angle), y + r*sin(angle));
	}
	glEnd();
}
void circle_wire(int x, int y, int r)
{
#define PI 3.1415
	float angle;

	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 100; i++)
	{
		angle = 2 * PI*i / 100;
		glVertex2f(x + r*cos(angle), y + r*sin(angle));
	}
	glEnd();
}
void print(int x, int y, char *string, void *font)
{
	int len, i;

	glRasterPos2f(x, y);
	len = (int)strlen(string);
	for (i = 0; i<len; i++)
	{
		glutBitmapCharacter(font, string[i]);
	}
}
// display text with variables.
void vprint(int x, int y, void *font, char *string, ...)
{
	va_list ap;
	va_start(ap, string);
	char str[1024];
	vsprintf_s(str, string, ap);
	va_end(ap);

	int len, i;
	glRasterPos2f(x, y);
	len = (int)strlen(str);
	for (i = 0; i<len; i++)
	{
		glutBitmapCharacter(font, str[i]);
	}
}
void vprint2(int x, int y, float size, char *string, ...) {
	va_list ap;
	va_start(ap, string);
	char str[1024];
	vsprintf_s(str, string, ap);
	va_end(ap);
	glPushMatrix();
	glTranslatef(x, y, 0);
	glScalef(size, size, 1);

	int len, i;
	len = (int)strlen(str);
	for (i = 0; i<len; i++)
	{
		glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);
	}
	glPopMatrix();
}
//TO DRAW GREEN AND RED POÝNTS
void point(point_t max){

	glPointSize(12);
	glBegin(GL_POINTS);
	glVertex2f(max.x, max.y);
	glEnd();

}
//TO DRAW LÝGHT LÝNES
void drawLine(point_t s, point_t e, float size) {
	glColor3f(1, 0, 0);
	glLineWidth(size);
	glBegin(GL_LINES);
	glVertex2f(s.x, s.y);
	glVertex2f(e.x, e.y);
	glEnd();
	glLineWidth(1.0f);
}
float calcslope(point_t A, point_t B){

	return((A.y - B.y) / (A.x - B.x));
}
//FOR LIGHTSOURCE
point_t LinePoints(point_t B, float m){

	point_t rectn;

	rectn.x = 362;
	rectn.y = (m*(362 - B.x) + B.y);
	return rectn;

}
void DisplayLines(){




	line[0].m = calcslope(circle.main, rec.B);
	line[0].start = LinePoints(circle.main, line[0].m);
	drawLine(circle.main, line[0].start, 1);
	glColor3f(1, 0, 0);
	point(line[0].start);

	line[1].m = calcslope(circle.main, rec.D);
	line[1].start = LinePoints(circle.main, line[1].m);
	drawLine(circle.main, line[1].start, 1);
	glColor3f(1, 0, 0);
	point(line[1].start);

	line[2].m = calcslope(circle.main, rec.C);
	line[2].start = LinePoints(circle.main, line[2].m);
	drawLine(circle.main, line[2].start, 1);
	glColor3f(1, 0, 0);
	point(line[2].start);

	line[3].m = calcslope(circle.main, rec.A);
	line[3].start = LinePoints(circle.main, line[3].m);
	drawLine(circle.main, line[3].start, 1);
	glColor3f(1, 0, 0);
	point(line[3].start);

}
void DisplayLightSource(){

	//DRAW LÝGHT SOURCE
	glColor3f(1, 0.9, 0.2);
	circlel(circle.main.x, circle.main.y, circle.rad + 7);
	glColor3f(.6, .6, 1);
	circlel(circle.main.x, circle.main.y, circle.rad + 4);
	glColor3f(1, 0.9, 0.2);
	circlel(circle.main.x, circle.main.y, circle.rad + 1);
	glColor3f(.6, .6, 1);
	circlel(circle.main.x, circle.main.y, circle.rad);


	glLineWidth(3);
	glBegin(GL_LINES);
	glColor3f(1, 0.9, 0.2);
	glVertex2f(circle.main.x, circle.main.y - 22);
	glVertex2f(circle.main.x, circle.main.y - 13);
	glVertex2f(circle.main.x, circle.main.y + 13);
	glVertex2f(circle.main.x, circle.main.y + 22);
	glVertex2f(circle.main.x - 24, circle.main.y);
	glVertex2f(circle.main.x - 13, circle.main.y);
	glVertex2f(circle.main.x + 12, circle.main.y);
	glVertex2f(circle.main.x + 23, circle.main.y);

	glEnd();

}
//
// To display onto window using OpenGL commands
//
void display()
{
	//
	// clear window to black
	//
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	//DRAW TWO RECTANGLE FOR SCREEN
	glColor3f(0.6, 0.6, 0.9);
	glRectf(-600, 800, 20, -800);
	glColor3f(0.6, 0.6, 0.6);
	glRectf(600, 800, 20, -800);

	//WRITE INFO
	glColor3f(1, 1, 1);
	vprint(-370, 285, GLUT_BITMAP_8_BY_13, "HW2-Shadow Simulation");
	vprint(-370, 260, GLUT_BITMAP_8_BY_13, "Mert Ozbudak");

	//DRAW WALL
	glLineWidth(3);
	glBegin(GL_LINE_STRIP);
	glColor3f(1, 0.9, 0.2);
	glVertex2f(362, -600);
	glVertex2f(362, 600);
	glEnd();

	//WRITE WALL
	glColor3f(1, 1, 1);
	vprint(370, 148, GLUT_BITMAP_TIMES_ROMAN_24, "W");
	vprint(370, 80, GLUT_BITMAP_TIMES_ROMAN_24, "A");
	vprint(370, 2, GLUT_BITMAP_TIMES_ROMAN_24, "L");
	vprint(370, -76, GLUT_BITMAP_TIMES_ROMAN_24, "L");

	//DRAW QUADS FOR SHADOW
	
	glBegin(GL_QUADS);
	glColor3f(0, 0, 0);
	glVertex2f(rec.A.x, rec.A.y);//SOL ALT KÖÞE 
	glVertex2f(line[3].start.x, line[3].start.y);//SOL ÜST KÖÞE
	glVertex2f(line[0].start.x, line[0].start.y);//SAÐ ÜST KÖÞE
	glVertex2f(rec.B.x, rec.B.y);//SAÐ ALT KÖÞE - sol üst
	glEnd();

	//IF CHECKS FOR MOVÝNG	
	if (circle.main.y >= rec.B.y)
	{
		glBegin(GL_QUADS);
		glColor3f(0, 0, 0);
		glVertex2f(rec.A.x, rec.A.y);//SOL ALT KÖÞE 
		glVertex2f(line[3].start.x, line[3].start.y);//SOL ÜST KÖÞE
		glVertex2f(line[1].start.x, line[1].start.y);//SAÐ ÜST KÖÞE
		glVertex2f(rec.D.x, rec.D.y);//SAÐ ALT KÖÞE - sol üst
		glEnd();
		
	}
	else //or if (circle.main.y <= rec.A.y)
	{
		glBegin(GL_QUADS);
		glColor3f(0, 0, 0);
		glVertex2f(rec.C.x, rec.C.y);//SOL ALT KÖÞE A(20,-40)-
		glVertex2f(line[2].start.x, line[2].start.y);//SOL ÜST KÖÞE
		glVertex2f(line[0].start.x, line[0].start.y);//SAÐ ÜST KÖÞE
		glVertex2f(rec.B.x, rec.B.y);//SAÐ ALT KÖÞE 
		glEnd();
		
	}

	//DRAW SQUARE FOR BLOCKÝNG LÝGHT
	glLineWidth(1);
	glColor3f(0.4, 0.4, 0.4);
	glRectf(rec.A.x, rec.A.y, rec.D.x, rec.D.y);


	//DRAW SQUARE LÝNES
	glBegin(GL_LINE_STRIP);
	glColor3f(1, 1, 1);
	glVertex2f(rec.A.x, rec.A.y);
	glColor3f(1, 1, 1);
	glVertex2f(rec.D.x, rec.A.y);
	glVertex2f(rec.D.x, rec.D.y);
	glVertex2f(rec.A.x, rec.D.y);
	glVertex2f(rec.A.x, rec.A.y);

	//DRAW X FOR ÝNSÝDE OF SQUARE
	glVertex2f(rec.A.x, rec.D.y);
	glVertex2f(rec.D.x, rec.A.y);
	glVertex2f(rec.A.x, rec.A.y);
	glVertex2f(rec.D.x, rec.D.y);
	glEnd();
	//IF CHECKS FOR GREEN LIGHTS
	if (circle.main.y < rec.B.y && circle.main.y > rec.A.y)
	{
		glColor3f(0, 1, 0);
		point(rec.A);
		point(rec.B);
	}
	else if (circle.main.y <= rec.A.y)
	{
		glColor3f(0, 1, 0);
		point(rec.B);
		point(rec.C);
	}
	else if (circle.main.y >= rec.B.y)
	{
		glColor3f(0, 1, 0);
		point(rec.A);
		point(rec.D);
	}
	//DRAW DASHED LÝNES
	glLineWidth(1);
	glColor3f(0.2, 0.2, 1);
	glPushAttrib(GL_ENABLE_BIT);
	glLineStipple(10, 0xAAAA);
	glEnable(GL_LINE_STIPPLE);
	glBegin(GL_LINES);
	glVertex3f(20, 600, 0.5);
	glVertex3f(20, -600, 0.5);
	glColor3f(1, 1, 1);
	glVertex3f(20, 100, 0.5);
	glVertex3f(20, -40, 0.5);
	glEnd();
	glPopAttrib();


	DisplayLightSource();
	DisplayLines();

	glutSwapBuffers();


}
//
// key function for ASCII charachters like ESC, a,b,c..,A,B,..Z
//
void onKeyDown(unsigned char key, int x, int y)
{
	// exit when ESC is pressed.
	if (key == 27)
		exit(0);

	// to refresh the window it calls display() function
	glutPostRedisplay();
}
void onKeyUp(unsigned char key, int x, int y)
{
	// exit when ESC is pressed.
	if (key == 27)
		exit(0);

	// to refresh the window it calls display() function
	glutPostRedisplay();
}
//
// Special Key like GLUT_KEY_F1, F2, F3,...
// Arrow Keys, GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_RIGHT, GLUT_KEY_RIGHT
//
void onSpecialKeyDown(int key, int x, int y)
{
	// Write your codes here.
	switch (key) {
	case GLUT_KEY_UP: up = true; break;
	case GLUT_KEY_DOWN: down = true; break;
	case GLUT_KEY_LEFT: left = true; break;
	case GLUT_KEY_RIGHT: right = true; break;

	}
	// to refresh the window it calls display() function
	glutPostRedisplay();
}
//
// Special Key like GLUT_KEY_F1, F2, F3,...
// Arrow Keys, GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_RIGHT, GLUT_KEY_RIGHT
//
void onSpecialKeyUp(int key, int x, int y)
{
	// Write your codes here.
	switch (key) {
	case GLUT_KEY_UP: up = false; break;
	case GLUT_KEY_DOWN: down = false; break;
	case GLUT_KEY_LEFT: left = false; break;
	case GLUT_KEY_RIGHT: right = false; break;

	}
	// to refresh the window it calls display() function
	glutPostRedisplay();
}
//
// When a click occurs in the window,
// It provides which button
// buttons : GLUT_LEFT_BUTTON , GLUT_RIGHT_BUTTON
// states  : GLUT_UP , GLUT_DOWN
// x, y is the coordinate of the point that mouse clicked.
//
void onClick(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		check = true;
	else
		check = false;

	// to refresh the window it calls display() function
	glutPostRedisplay();
}
//
// This function is called when the window size changes.
// w : is the new width of the window in pixels.
// h : is the new height of the window in pixels.
//
void onResize(int w, int h)
{
	winWidth = w;
	winHeight = h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-w / 2, w / 2, -h / 2, h / 2, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	display(); // refresh window.
}
void onMoveDown(int x, int y) {
	x = x - winWidth / 2;
	y = winHeight / 2 - y;
	if (x <= +13 - (circle.rad))
	{
		if (check == true)
		{
			circle.main.x = x;
			circle.main.y = y;
		}
	}
	glutPostRedisplay();
}
void onMove(int x, int y) {

	int lx = x - winWidth / 2;
	int ly = winHeight / 2 - y;


	

	glutPostRedisplay();
}
#if TIMER_ON == 1
void onTimer(int v) {

	glutTimerFunc(TIMER_PERIOD, onTimer, 0);
	// Write your codes here.



	// to refresh the window it calls display() function
	glutPostRedisplay(); // display()

}
#endif
void Init() {

	// Smoothing shapes
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
}
void main(int argc, char *argv[])
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("CTIS164-Hw #2-SPR16");

	glutDisplayFunc(display);
	glutReshapeFunc(onResize);
	//
	// keyboard registration
	//
	glutKeyboardFunc(onKeyDown);
	glutSpecialFunc(onSpecialKeyDown);

	glutKeyboardUpFunc(onKeyUp);
	glutSpecialUpFunc(onSpecialKeyUp);

	//
	// mouse registration
	//
	glutMouseFunc(onClick);
	glutMotionFunc(onMoveDown);
	glutPassiveMotionFunc(onMove);

#if  TIMER_ON == 1
	// timer event
	glutTimerFunc(TIMER_PERIOD, onTimer, 0);
#endif

	Init();

	glutMainLoop();
}