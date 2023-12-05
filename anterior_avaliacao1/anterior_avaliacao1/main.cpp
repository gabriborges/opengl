#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>

GLfloat fAspect;
GLdouble rotX = 0, rotY = 0, rotHead = 0, rotBlade = 0, controleRotacao = 4;

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glLineWidth(2);

	glPushMatrix();
	

		glRotatef(rotX, 1, 0, 0);
		glRotatef(rotY, 0, 1, 0);

		glColor3f(1.0f, 0.0f, 0.0f);

		// Base
		glPushMatrix();
		{	
			glTranslatef(0, -13, 0);
			glScalef(10, 2, 10);
			glutWireCube(1);
		}
		glPopMatrix();

		// Haste
		glPushMatrix();
		{
			glTranslatef(0, -7, 0);
			glScalef(2, 10, 2);
			glutWireCube(1);
		}
		glPopMatrix();

		glColor3f(0.0f, 0.0f, 1.0f);

		glPushMatrix();
		glRotatef(rotHead, 0, 1, 0);

		//head
			glPushMatrix();
			{

				glScalef(4, 4, 6);
				glutWireCube(1);
			}
			glPopMatrix();


			glPushMatrix();
			glRotatef(rotBlade,0,0,1);
				// Ponta
				glPushMatrix();
				{	
					glTranslatef(0, 0, 3);
					glutSolidSphere(0.5, 10, 8);
				}
				glPopMatrix();

				glColor3f(0.0f, 1.0f, 0.0f);

				// H�lice
				glPushMatrix();
				{
					glTranslatef(0, 0, 3);
					glScalef(16, 2, 1);
					glutWireCube(1);
					
					
				}
				glPopMatrix();

				//linhas
				glPushMatrix();
					glColor3f(0.0f, 0.0f, 0.0f);
					glBegin(GL_LINES);
					glVertex3f(7.5, 1.5, 2); // Replace x1 and y1 with the coordinates of the starting point
					glVertex3f(7.0, 4, 2); // Replace x2 and y2 with the coordinates of the ending point
					glEnd();
					glColor3f(0.0f, 1.0f, 0.0f);

				glPopMatrix();

				// H�lice
				glPushMatrix();
				{
					glTranslatef(0, 0, 3);
					glScalef(2, 16, 1);
					glutWireCube(1);
				}
				glPopMatrix();

			glPopMatrix();

		glPopMatrix();


	glPopMatrix();

	glutSwapBuffers();
}

void configProjection(void)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45, fAspect, 0.5, 500);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	gluLookAt(0, 0, 50, 0, 0, 0, 0, 1, 0);
}

void resize(GLsizei w, GLsizei h)
{
	if (h == 0)
		h = 1;

	fAspect = (GLfloat)w / (GLfloat)h;

	configProjection();
}

void keyboard(unsigned char key, int x, int y)
{

	switch (key)
	{
	case 27:
		exit(0);
		break;
	case 'a':
		rotY += 5;
		break;
	case 'd':
		rotY -= 5;
		break;
	case 'w':
		rotX += 5;
		break;
	case 's':
		rotX -= 5;
		break;
	case 'z':
		rotHead += controleRotacao;
		break;
	case 'x':
		rotHead -= controleRotacao;
		break;
	case 'q':
		rotBlade += 5;
		break;
	case 'e':
		rotBlade -= 5;
		break;
	case 'p':
		rotHead += controleRotacao;
		rotBlade -= 15;
		break;
	case 32:
		rotX = 0;
		rotY = 0;

		break;
	default:
		break;
	}

	if (rotHead > 85 || rotHead < -85) {
		controleRotacao *= -1;
	}

	glutPostRedisplay();
}

void specialkeys(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		rotX += 10;
		break;
	case GLUT_KEY_DOWN:
		rotX += 10;
		break;
	case GLUT_KEY_LEFT:
		rotY += 10;
		break;
	case GLUT_KEY_RIGHT:
		rotY -= 10;
		break;
	}
	glutPostRedisplay();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Avalia��o 02");
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialkeys);
	glutMainLoop();
	return 0;
}
