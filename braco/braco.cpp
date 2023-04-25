
#include <GL/glut.h>

#include <stdlib.h>

int ombro = 0, cotovelo = 0;

GLdouble rotX = 0, rotY = 0, rotZ = 0, rotArm = 0, rotForearm = 0;
GLdouble desl = 5;

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(5);

    glPushMatrix();

    glPushMatrix();

    glRotatef(rotX, 1, 0, 0);
    glRotatef(rotY, 0, 1, 0);
    glRotatef(rotZ, 0, 0, 1);

    //braço
    glPushMatrix();
    /*glBegin(GL_POINTS);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0, 0, 0);
    glEnd();*/
    glTranslatef(-1, 0, 0);
    /*glBegin(GL_POINTS);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0, 0, 0);
    glEnd();*/
    glRotatef(-rotArm, 0, 0, 1);

        glPushMatrix();
        glTranslatef(1, 0, 0);
        glColor3f(0.5, 0.0, 0.0);
        glScalef(2.0, 0.4, 1.0);
        
        glutWireCube(1.0);

        /*glBegin(GL_POINTS);
            glColor3f(1.0f, 0.0f, 0.0f);
            glVertex3f(0, 0, 0);
        glEnd();*/

        glVertex2d(0, 0);
        glPopMatrix();

        //antebraco
        glPushMatrix();
            glTranslatef(2.0, 0.0, 0.0);
            glRotatef(-rotForearm, 0, 0, 1);

            glTranslatef(1.0, 0.0, 0.0);
            glPushMatrix();
            glColor3f(0.0, 0.0, 0.5);
            glScalef(2.0, 0.4, 1.0);
            glutWireCube(1.0);
            glPopMatrix();
        glPopMatrix();


    glPopMatrix();
    glPopMatrix();
    glPopMatrix();
    glutSwapBuffers();
}

void reshape(int w, int h) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(75.0, w / (h * 1.0), 1.0, 20.0);
    gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'a':
        ombro = (ombro + 5) % 360;
        rotY += 10;
        glutPostRedisplay();
        break;
    case 'd':
        ombro = (ombro - 5) % 360;
        rotY -= 10;
        glutPostRedisplay();
        break;
    case 's':
        cotovelo = (cotovelo + 5) % 360;
        rotX -= 10;
        glutPostRedisplay();
        break;
    case 'w':
        cotovelo = (cotovelo - 5) % 360;
        rotX += 10;
        glutPostRedisplay();
        break;
    case 'z':
        rotArm += desl;
        break;
    case 'x':
        rotArm -= desl;
        break;
    case 'q':
        rotForearm += desl;
        break;
    case 'e':
        rotForearm -= desl;
        break;
    case 27:
        exit(0);
        break;
    case 32:
        rotX = 0;
        rotY = 0;
        rotZ = 0;
        rotArm = 0;
        rotForearm = 0;
        break;
    default:
        break;
    }

    //limitador e loop do braço
    if (rotArm <= -50) desl *= -1;
    if (rotArm >= 90) desl *= -1;

    //limitador e loop do antebraço
    if (rotForearm <= 0) desl *= -1;
    if (rotForearm >= -150) desl *= -1;

    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow(argv[0]);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glClearColor(1, 1, 1, 1);
    glutMainLoop();
    return 0;
}