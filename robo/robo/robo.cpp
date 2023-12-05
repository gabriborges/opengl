
#include <GL/glut.h>

#include <stdlib.h>

GLfloat angle, fAspect;
GLdouble rotX = 0, rotY = 0, rotZ = 0, rotArm = 0;
GLdouble desl = 15;
void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    glLineWidth(2);
    glPointSize(5);

    glPushMatrix();
    //pulo para cima e para baixo
    glTranslatef(0, rotArm / 10.0, 0);
    glRotatef(rotX, 1, 0, 0);
    glRotatef(rotY, 0, 1, 0);
    glRotatef(rotZ, 0, 0, 1);



    //Referencia
     glColor3f(1.0f, 0.0f, 0.0f);
     glutSolidSphere(0.5, 10, 8);

    // Corpo
    glColor3f(0.0f, 0.0f, 1.0f);
    glutWireCube(30);

    // Cabeca
    glPushMatrix();
    glColor3f(1.0f, 0.0f, 0.0f);
    glTranslatef(0, 25, 0);
    glutWireCube(20);
    glPopMatrix();

    // Braco 1
    glPushMatrix();
    glBegin(GL_POINTS);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0, 0, 0);
    glEnd();
    glTranslatef(-20, 10, 0);
    glBegin(GL_POINTS);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0, 0, 0);
    glEnd();
    glRotatef(-rotArm, 0, 0, 1);
    glColor3f(0.0f, 1.0f, 1.0f);
    glutWireCube(10);
    glPushMatrix();

    glColor3f(0.0f, 1.0f, 0.0f);
    glTranslatef(0, -10, 0);
    glutWireCube(10);
    glPopMatrix();
    glPopMatrix();

    // Braco 2
    glPushMatrix();
    glTranslatef(20, 10, 0);
    glRotatef(rotArm, 0, 0, 1);
    glColor3f(0.0f, 1.0f, 1.0f);
    glutWireCube(10);
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslatef(0, -10, 0);
    glutWireCube(10);
    glPopMatrix();
    glPopMatrix();

    // Perna 1
    glPushMatrix();
    glTranslatef(10, -20, 0);
    glRotatef(rotArm / 4.0, 0, 0, 1);
    glColor3f(0.0f, 0.0f, 0.0f);
    glutWireCube(10);
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslatef(0, -10, 0);
    glutWireCube(10);
    glPopMatrix();
    glPopMatrix();

    // Perna 2
    glPushMatrix();
    glTranslatef(-10, -20, 0);
    glRotatef(-rotArm / 4.0, 0, 0, 1);
    glColor3f(0.0f, 0.0f, 0.0f);
    glutWireCube(10);
    glPushMatrix();
    glTranslatef(0, -10, 0);
    glutWireCube(10);
    glPopMatrix();
    glPopMatrix();

    glPopMatrix();

    glutSwapBuffers();
}

void init() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    angle = 45;
}

void configProjection(void) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(angle, fAspect, 0.5, 500);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(0, 0, 150, 0, 0, 0, 0, 1, 0);
}

void resize(GLsizei w, GLsizei h) {
    if (h == 0) h = 1;

    fAspect = (GLfloat)w / (GLfloat)h;

    configProjection();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON)
        if (state == GLUT_DOWN) {  // Zoom-in
            if (angle >= 10) angle -= 5;
        }
    if (button == GLUT_RIGHT_BUTTON)
        if (state == GLUT_DOWN) {  // Zoom-out
            if (angle <= 130) angle += 5;
        }
    configProjection();
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 27:
        exit(0);
        break;
    case 'a':
        rotY += 10;
        break;
    case 'd':
        rotY -= 10;
        break;
    case 'w':
        rotX += 10;
        break;
    case 's':
        rotX -= 10;
        break;
    case 'q':
        rotZ += 10;
        break;
    case 'e':
        rotZ -= 10;
        break;
    case 'z':
        rotArm += desl;
        break;
    case 'x':
        rotArm -= desl;
        break;
    case 32:
        rotX = 0;
        rotY = 0;
        rotZ = 0;
        break;
    default:
        break;
    }

    if (rotArm <= 0) desl *= -1;
    if (rotArm >= 180) desl *= -1;

    configProjection();
    glutPostRedisplay();
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Visualizacao 3D");
    glutDisplayFunc(display);
    glutReshapeFunc(resize);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    init();
    glutMainLoop();
    return 0;
}
