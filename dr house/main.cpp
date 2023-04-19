

#include <GL/glut.h>

#include <stdlib.h>
#include <stdio.h>

void display(void) {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); //Define a cor de fundo da cena (cor usada para limpar o buffer de cor)
	glClear(GL_COLOR_BUFFER_BIT);//Inicializa o buffer de cores antes de ele ser alterado

	glMatrixMode(GL_MODELVIEW); //Informa que as operações seguintes serão executadas na matrix modelview
	glLoadIdentity(); //Carrega a matriz identidade

	glPointSize(25); //Define quantos pixels representarão um vértice na tela
	glLineWidth(2);

	float j = 0.05;
	float g = 0.05;

	for (int i = 0; i < 25; i++) {
		for (int k = 0; k < 25; k++) {
			glBegin(GL_LINES);
			glColor3f(0.0, 0.0, 0.9);
			glVertex2f(-1.0 + j, 1.0 - g);
			glVertex2f(-0.95 + j, 0.95 - g);
			glEnd();
			g = g + 0.08;
		}
		g = 0.5;
		j = j + 0.08;
	}


	glPointSize(25); //Define quantos pixels representarão um vértice na tela
	glLineWidth(3);

	glBegin(GL_QUADS);
	glColor3f(0.7, 0.0, 0.0); // frente
	glVertex2f(0.0, 0.0);
	glVertex2f(-0.5, 0.0);
	glVertex2f(-0.5, -0.5); 
	glVertex2f(0.0, -0.5);	
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0, 0.75, 0.8); // porta
	glVertex2f(-0.35, -0.5);
	glVertex2f(-0.15, -0.5);
	glVertex2f(-0.15, -0.2);
	glVertex2f(-0.35, -0.2);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.0, 0.0, 0.0); // macaneta
	glVertex2f(-0.32, -0.37);
	glVertex2f(-0.32, -0.36);
	glVertex2f(-0.29, -0.36);
	glVertex2f(-0.29, -0.37);
	glEnd();

	

	glBegin(GL_QUADS);
	glColor3f(0.5, 0.5, 0.5); // caminhho
	glVertex2f(-0.35, -0.5);
	glVertex2f(-0.15, -0.5);
	glVertex2f(-0.15, -1);
	glVertex2f(-1, -1);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.0, 0.0, 0.3); // lado direito
	glVertex2f(0.0, 0.0);
	glVertex2f(0.0, -0.5);
	glVertex2f(0.8, -0.5);
	glVertex2f(0.8, 0.0);
	glEnd();


	glBegin(GL_QUADS);
	glColor3f(0.3, 0.6, 0.3); // janela1
	glVertex2f(0.13, -0.13);
	glVertex2f(0.13, -0.25);
	glVertex2f(0.35, -0.25);
	glVertex2f(0.35, -0.13);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.24, -0.13);
	glVertex2f(0.24, -0.25);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.13, -0.19);
	glVertex2f(0.35, -0.19);
	glEnd();


	glBegin(GL_QUADS);
	glColor3f(0.3, 0.6, 0.3); // janela2
	glVertex2f(0.67, -0.13);
	glVertex2f(0.67, -0.25);
	glVertex2f(0.45, -0.25);
	glVertex2f(0.45, -0.13);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.56, -0.13);
	glVertex2f(0.56, -0.25);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.67, -0.19);
	glVertex2f(0.45, -0.19);
	glEnd();


	glBegin(GL_TRIANGLES);
	glColor3f(0.0, 0.7, 0.0); // telhado
	glVertex2f(0.0, 0.0);
	glVertex2f(-0.5, 0.0);
	glVertex2f(-0.25, 0.25);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.0, 0.0, 0.95); // telhado lateral
	glVertex2f(0.0, 0.0);
	glVertex2f(-0.25, 0.25);
	glVertex2f(0.55, 0.25);
	glVertex2f(0.8, 0.0);
	glEnd();

	glFlush(); //Informa que as operações devem ser processadas imediatamente e exibidas na tela
}


/*Recebe um o comprimento (width) e altura (height) da janela em pixels.*/
void resize(GLsizei w, GLsizei h) {
	if (h == 0)
		h = 1;

	printf("Tam. janela: (%i,%i)\n", w, h);
}

/*Recebe um código para cada tecla (ASCII) e as coordenadas do mouse.*/
void keyboard(unsigned char key, int x, int y) {

	switch (key) {
	case 27:
		exit(0);
		break;
	case 32:
		glClearColor(0.0f, 1.0f, 1.0f, 1.0f); //Define a cor de fundo da cena (cor usada para limpar o buffer de cor)
		break;
	default:
		printf("Código tecla: %i. Mouse em (%i,%i)\n", key, x, y);
		break;
	}
	glutPostRedisplay(); //Informa que a janela atual deve ser redesenhada
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv); //Inicializa a OpenGL
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); //Configura os modos de exibição (mais detalhes no futuro)
	glutInitWindowSize(600, 600); //Define o tamanho da janela em pixels
	glutInitWindowPosition(0, 0); //Define a posição inicial da janela
	glutCreateWindow("Primeiro Exemplo"); //Cria a janela especificando seu título
	glutDisplayFunc(display); //Especifica a função de rendering (exibe a cena no loop)
	glutReshapeFunc(resize); //Especifica função a ser executada quando a janela é redimensionada
	glutKeyboardFunc(keyboard); //Especifica função a ser executada quando uma tecla é pressionada

	glutMainLoop(); //Executa o loop de renderização
	return 0;
}