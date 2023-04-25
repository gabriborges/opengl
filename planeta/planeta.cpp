
#include <GL/glut.h>

#include <stdlib.h>

static int ano = 0, dia = 0;
GLdouble rotX = 0, rotY = 0, rotZ = 0, rotMenor = 0, rotMaior = 0, translacao = 0;
GLdouble taxaMenor = 5;
GLdouble taxaMaior = 1;
GLdouble taxaTranslacao = 5;


void display(void)
{
   glClear(GL_COLOR_BUFFER_BIT);
   glPushMatrix();
   glRotatef(rotX, 1, 0, 0);
   glRotatef(rotY, 0, 1, 0);
   glRotatef(rotZ, 0, 0, 1);


   glPushMatrix();
       

       glPushMatrix();
           glRotatef(rotMaior, 0, 0, 1);
           glColor3f(0.5, 0.5, 0.0);
           glutWireSphere(1.0, 20, 16);
       glPopMatrix();

       glPushMatrix();
           glRotatef(translacao, 0, 0, 1);
           glPushMatrix();
           glTranslatef(2.5, 0.0, 0.0);
               glRotatef(rotMenor, 0, 0, 1);
               glColor3f(0.0, 0.0, 0.5);
               glutWireSphere(0.2, 10, 8);
           glPopMatrix();
       glPopMatrix();

   glPopMatrix();

   glPopMatrix();
   glutSwapBuffers();
}

void reshape (int w, int h)
{
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(60.0, w/(h*1.0), 1.0, 20.0);
   gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

void keyboard (unsigned char key, int x, int y)
{
   switch (key) {
      case 'a':
         dia = (dia + 10) % 360;
         rotY += 10;
         glutPostRedisplay();
         break;
      case 'd':
         dia = (dia - 10) % 360;
         rotY -= 10;
         glutPostRedisplay();
         break;
      case 's':
         ano = (ano + 5) % 360;
         rotX += 10;
         glutPostRedisplay();
         break;
      case 'w':
         ano = (ano - 5) % 360;
         rotX -= 10;
         glutPostRedisplay();
         break;
      case 'q':
          translacao += taxaTranslacao;
          glutPostRedisplay();
          break;
      case 'e':
          translacao -= taxaTranslacao;
          glutPostRedisplay();
          break;
      case 'z':
          rotMaior += taxaMaior;
          rotMenor += taxaMenor;
          glutPostRedisplay();
          break;
      case 'x':
          rotMaior -= taxaMaior;
          rotMenor -= taxaMenor;
          glutPostRedisplay();
          break;
      //play
      case 'p':
          rotMaior += taxaMaior;
          rotMenor += taxaMenor;
          translacao += taxaTranslacao;
          glutPostRedisplay();
          break;
      case 32:
          rotX = 0;
          rotY = 0;
          rotZ = 0;
          rotMenor = 0;
          rotMaior = 0;
          translacao = 0;
          break;
      default:
         break;
   }
   glutPostRedisplay();
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize(500, 500);
   glutCreateWindow(argv[0]);
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glClearColor(1,1,1,1);
   glutMainLoop();
   return 0;
}