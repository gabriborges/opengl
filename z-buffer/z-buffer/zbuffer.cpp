#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <string.h>

bool depth = false;
bool cull = false;
bool cullface = false;
bool frontface = false;
bool backtri = true;

void displayText()
{

	glColor3f(0, 0, 0);

	const char* depth_txt = (depth) ? "Depth: On" : "Depth: Off";
	glRasterPos2f(-13, 9);
	for (const char* c = depth_txt; *c != 0; c++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
	}

	const char* cull_txt = (cull) ? "Culling: On" : "Culling: Off";
	glRasterPos2f(-13, 8);
	for (const char* c = cull_txt; *c != 0; c++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
	}

	const char* cullface_txt = (cullface) ? "Cullface: Front" : "Cullface: Back";
	glRasterPos2f(-13, 7);
	for (const char* c = cullface_txt; *c != 0; c++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
	}

	const char* frontface_txt = (frontface) ? "Front: CW" : "Front: CCW";
	glRasterPos2f(-13, 6);
	for (const char* c = frontface_txt; *c != 0; c++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
	}

	//Numeros triangulo superior
	glColor3f(1, 0, 0);
	glRasterPos2f(-0.5, 0.5);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '1');

	glColor3f(0, 1, 0);
	glRasterPos2f(10.5, -0.5);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '2');

	glColor3f(0, 0, 1);
	glRasterPos2f(10.5, 9.5);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '3');

	//Numeros triangulo inferior

	glColor3f(0, 1, 0);
	glRasterPos2f(-10.5, -9.5);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '2');

	glColor3f(0, 0, 1);
	glRasterPos2f(-10.5, 0.5);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '3');
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	glBegin(GL_TRIANGLES);

	//Triangulo superior
	glColor3f(1, 0, 0);
	glVertex3f(0, 0, 0);

	glColor3f(0, 1, 0);
	glVertex3f(10, 0, 0);

	glColor3f(0, 0, 1);
	glVertex3f(10, 10, 0);

	//Triangulo inferior
	glColor3f(1, 0, 0);
	glVertex3f(0, 0, 0);

	glColor3f(0, 1, 0);
	glVertex3f(-10, -10, 0);

	glColor3f(0, 0, 1);
	glVertex3f(-10, 0, 0);

	//Triangulo fundo
	if (backtri)
	{
		glColor3f(0, 0, 0);
		glVertex3f(1, 1, -1);

		glColor3f(0, 0, 0);
		glVertex3f(11, 1, -1);

		glColor3f(0, 0, 0);
		glVertex3f(11, 11, -1);
	}

	glEnd();
	glPopMatrix();

	displayText();

	glutSwapBuffers();
}

void resize(GLsizei w, GLsizei h)
{
	if (h == 0)
		h = 1;

	GLfloat aspect = (GLfloat)w / (GLfloat)h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45, aspect, 1, 100);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0, 0, 25, 0, 0, 0, 0, 1, 0);
}

void keyboard(unsigned char key, int x, int y)
{

	switch (key)
	{
	case 27:
		exit(0);
		break;
	case '1':
		depth = !depth;
		(depth) ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);
		break;
	case '2':
		cull = !cull;
		(cull) ? glEnable(GL_CULL_FACE) : glDisable(GL_CULL_FACE);
		break;
	case '3':
		cullface = !cullface;
		(cullface) ? glCullFace(GL_FRONT) : glCullFace(GL_BACK);
		break;
	case '4':
		frontface = !frontface;
		(frontface) ? glFrontFace(GL_CW) : glFrontFace(GL_CCW);
		break;

	case 32:
		backtri = !backtri;
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Visualizacao 3D");
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyboard);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glutMainLoop();
	return 0;
}
