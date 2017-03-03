#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glut.h>
#include <math.h>

#define pi 3.14159265358979323846

using namespace std;

int rot = 0;
float angle = 10;
//Array used for the points on the grid of the wave
float polygons[45][45][3];
//Count on how fast the wave is going
int wave_count = 0;

GLfloat hold;
bool isMoving = false;
float direction = 0;
float speed = 0;
float xPos, yPos;

void initRendering() 
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
}

void lightPosition(float x, float y, float z, float strength)
{
	GLfloat lightPosition[] = { x, y, z, strength };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
}

void initLight()
{
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	GLfloat ambientlight[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat diffuselight[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat Specularlight[] = { 1.0, 1.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientlight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuselight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, Specularlight);

	lightPosition(0, 0, -0.1, 0);
}

void update(int value)
{
	angle++;

	glutPostRedisplay();
	glutTimerFunc(10, update, 0);
}

void resize(int width, int height)
{
	//tells the screen from which point to start drawing, bottom left > till w and h (this prevents issues after resizing)
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (double)width/(double)height, 0.01, 200.0);
	glMatrixMode(GL_MODELVIEW);
	

	gluLookAt(-10.0, 0.0, 0.0, 
		0.0, 0.0, 0.0, 
		0.0, 1.0, 0.0);
}

//Reference to the NeHe Tutorial section
void initData()
{
	for (int x = 0; x < 45; x++)
	{
		for (int y = 0; y < 45; y++)
		{
			polygons[x][y][0] = float((x / 5.0f) - 4.5f);
			polygons[x][y][1] = float((y / 5.0f) - 4.5f);
			polygons[x][y][2] = float(sin((((x / 5.0f)*30.0f) / 360.0f)*3.141592654*2.0f));
		}
	}

}
//End Reference to the NeHe Tutorial section


void display()
{
	int x, y;
	xPos = speed * cos(direction);
	yPos = speed * sin(direction);

	//display gets called every second
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//clear viewmodel
	glLoadIdentity();	
	glRotatef(xPos, yPos, 0, 0);
	glTranslatef(0, -3, -6);
	glRotatef(rot, 0, 5, 0);

	//Drawing the cube(main body of the boat)							
	glBegin(GL_QUADS);		
							
	// Front
	glColor3f(0.7, 0.7, 0);
	glVertex3f(-0.5, 0, 0.5);
	glVertex3f(-0.5, 1, 0.5);
	glVertex3f(0.5, 1, 0.5);
	glVertex3f(0.5, 0, 0.5);

	// Back
	glColor3f(0.8, 0.8, 0);
	glVertex3f(-0.5, 0, -0.5);
	glVertex3f(0.5, 0, -0.5);
	glVertex3f(0.5, 1, -0.5);
	glVertex3f(-0.5, 1, -0.5);

	// Left side
	glColor3f(0.7, 0.7, 0);		
	glVertex3f(-0.5, 0, 0.5);
	glVertex3f(-0.5, 1, 0.5);
	glVertex3f(-0.5, 1, -0.5);
	glVertex3f(-0.5, 0, -0.5);

	// Right side
	glVertex3f(0.5, 0, 0.5);
	glVertex3f(0.5, 0, -0.5);
	glVertex3f(0.5, 1, -0.5);
	glVertex3f(0.5, 1, 0.5);

	/* ROOF IS BUGGED
	//Triangular roof for the point of the boat
	glBegin(GL_TRIANGLES);
	// Front
	glColor3f(1, 1, 0);
	glVertex3f(-0.5, 1, 0.5);
	glVertex3f(0, 2, 0);
	glVertex3f(0.5, 1, 0.5);
	// Right side
	glColor3f(0.9, 0.9, 0);
	glVertex3f(0.5, 1, 0.5);
	glVertex3f(0.5, 1, -0.5);
	glVertex3f(0, 2, 0);
	// Back
	glColor3f(0.8, 0.8, 0);
	glVertex3f(0.5, 1, -0.5);
	glVertex3f(-0.5, 1, -0.5);
	glVertex3f(0, 1, 0);
	// Left side
	glColor3f(0.7, 0.7, 0);	
	glVertex3f(-0.5, 1, 0.5);
	glVertex3f(0, 2, 0);
	glVertex3f(-0.5, 1, -0.5);
	glEnd();
	*/

	glEnd();
	glPopMatrix();
	glutSwapBuffers();

	// Clear The Screen And The Depth Buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);

	//Reset the view
	glLoadIdentity();
	glPushMatrix();
	glTranslatef(0.0, 0.0, -10.0);
	glRotatef(angle, 0, 1, 0);



	//Reference to the NeHe Tutorial section
	glBegin(GL_QUADS);

	glColor3f(0.0, 0.0, 1.0);

	for (int x = 0; x < 44; x++)
	{
		for (int y = 0; y < 44; y++)
		{
			glVertex3f(polygons[x][y][0], polygons[x][y][1], polygons[x][y][2]);
			glVertex3f(polygons[x][y + 1][0], polygons[x][y + 1][1], polygons[x][y + 1][2]);
			glVertex3f(polygons[x + 1][y + 1][0], polygons[x + 1][y + 1][1], polygons[x + 1][y + 1][2]);
			glVertex3f(polygons[x + 1][y][0], polygons[x + 1][y][1], polygons[x + 1][y][2]);
		}
	}

	glEnd();

	if (wave_count == 20)
	{
		for (y = 0; y < 45; y++)
		{
			hold = polygons[0][y][2];
			for (x = 0; x < 44; x++)
			{
				polygons[x][y][2] = polygons[x + 1][y][2];
			}
			polygons[44][y][2] = hold;
		}
		wave_count = 0;
	}

	wave_count++;

	glPopMatrix();
	glutSwapBuffers();
	
}
//End Reference to the NeHe Tutorial section


void keyboard_up(unsigned char key, int x, int y)
{

}

void keyboard_down(unsigned char key, int x, int y)
{
	if (key == 'w') 
	{
		speed += 1;
		
	}
	if (key == 'a')
	{
		direction -= 10;
		isMoving = true;
	}
	if (key == 's')
	{
		speed -= 1;
	}
	if (key == 'd')
	{
		direction += 10;
	}
	if (key == 'z')
	{
		rot += 5;
		rot %= 360;
	}

	//exit window
	switch (key)
	{
	case 27:
		exit(0);
		break;
	}
}


void initSettings()
{
	glClearColor(0.0, 1.0, 1.0, 0.80);
	
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
}

int main(int argc, char **argv) 
{
	//Display OpenGL stuff (init)
	glutInit(&argc, argv);
	//parameters = Double buffering, RGBA(alpha) colours, depth info
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(1280, 720);
	glutCreateWindow("OpenGL Boat Game");

	//Keyboard inputs
	glutKeyboardFunc(keyboard_down);
	glutKeyboardUpFunc(keyboard_up);

	//func call
	initSettings();
	initData();
	initRendering();
	initLight();
	
	//callback func
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutReshapeFunc(resize);

	//Continue looping the game and refreshing the frames
	glutMainLoop();
	glutTimerFunc(10, update, 0);

	return 0;
}
