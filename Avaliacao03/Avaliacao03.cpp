
#include <GL/glut.h>


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <vector>

GLfloat angleY = 0, taxa_Y=0.5, taxa_X=0.5;
GLfloat rotY = 0, rotX = 0;
GLfloat angleX = 0;
GLuint cam = 1;
GLuint camX = 0;
GLuint camZ = 5;
GLfloat fAspect = 1;

int idBind = 0;

typedef struct vertex {
  float x;
  float y;
  float z;
} vertex;

typedef struct face {
  int v1, v2, v3;
  int n1, n2, n3;
  int t1, t2, t3;
} face;

typedef struct model {
  std::vector<face> faces;
  std::vector<vertex> vertices;
  std::vector<vertex> normals;
  std::vector<vertex> textures;
  GLuint textureId;
} model;

model table, ball;

void loadObj(const char *filename, model &model) {
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    printf("Erro ao abrir o arquivo!\n");
    return;
  }

  while (1) {
    char lineHeader[128];
    int res = fscanf(file, "%s", lineHeader);
    if (res == EOF) break;  // EOF = End Of File. Quit the loop.

    if (strcmp(lineHeader, "v") == 0) {
      vertex v;
      fscanf(file, "%f %f %f\n", &v.x, &v.y, &v.z);
      model.vertices.push_back(v);
    } else if (strcmp(lineHeader, "vn") == 0) {
      vertex n;
      fscanf(file, "%f %f %f\n", &n.x, &n.y, &n.z);
      model.normals.push_back(n);
    } else if (strcmp(lineHeader, "vt") == 0) {
      vertex vt;
      fscanf(file, "%f %f\n", &vt.x, &vt.y);
      model.textures.push_back(vt);
    } else if (strcmp(lineHeader, "f") == 0) {
      face f;
      fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &f.v1, &f.t1, &f.n1, &f.v2,
             &f.t2, &f.n2, &f.v3, &f.t3, &f.n3);
      model.faces.push_back(f);
    }
  }
}

// Recebe o arquivo de imagem e retorna o id da textura
GLuint loadTGA(const char *filename) {
  static GLubyte TGA_TYPE_HEADER[8] = {0, 0, 2, 0, 0, 0, 0, 0};
  GLuint width, height, format;

  GLubyte *data;

  FILE *file;
  file = fopen(filename, "rb");

  if (file == NULL) {
    printf("Arquivo de textura não encontrado!\n");
    return 0;
  }

  GLubyte type_header[8];
  if (fread(type_header, 1, sizeof(type_header), file) != sizeof(type_header)) {
    printf("Problema ao ler cabeçalho do arquivo!\n");
    fclose(file);
    return 0;
  }

  if (memcmp(TGA_TYPE_HEADER, type_header, sizeof(type_header)) != 0) {
    printf("Tipo de arquivo TGA inválido!\n");
    fclose(file);
    return 0;
  }

  GLubyte image_header[10];
  if (fread(image_header, 1, sizeof(image_header), file) !=
      sizeof(image_header)) {
    printf("Problema ao ler formato da imagem!\n");
    fclose(file);
    return 0;
  }

  width = image_header[5] * 256u + image_header[4];
  height = image_header[7] * 256u + image_header[6];

  if ((width <= 0) || (height <= 0)) {
    printf("Tamanho de arquivo inválido!\n");
    fclose(file);
    return 0;
  }

  GLubyte depth = image_header[8];
  switch (depth) {
    case 24:
      format = GL_RGB;
      break;
    case 32:
      format = GL_RGBA;
      break;
    default:
      printf("Canal de cor inválido!\n");
      fclose(file);
      return 0;
  }

  size_t pixel_size = depth / 8u;
  size_t data_size = width * height * pixel_size;
  data = (GLubyte *)malloc(data_size);
  if (!data) {
    printf("Erro ao alocar memória!\n");
    fclose(file);
    return 0;
  }

  if (fread(data, 1, data_size, file) != data_size) {
    printf("Erro ao ler dados da imagem!\n");
    free(data);
    fclose(file);
    return 0;
  }

  // TGA stores image data as BGR(A).
  for (size_t i = 0; i < data_size; i += pixel_size) {
    GLubyte temp = data[i];
    data[i] = data[i + 2];
    data[i + 2] = temp;
  }

  fclose(file);

  GLuint idTextura;
  glGenTextures(1, &idTextura);
  glBindTexture(GL_TEXTURE_2D, idTextura);
  glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format,
               GL_UNSIGNED_BYTE, data);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glEnable(GL_TEXTURE_2D);

  return idTextura;
}

void renderModel(const model &model) {
  glBindTexture(GL_TEXTURE_2D, model.textureId);
  glBegin(GL_TRIANGLES);
  for (int i = 0; i < model.faces.size(); ++i) {
    const vertex &v1 = model.vertices[model.faces[i].v1 - 1];
    const vertex &v2 = model.vertices[model.faces[i].v2 - 1];
    const vertex &v3 = model.vertices[model.faces[i].v3 - 1];

    const vertex &n1 = model.normals[model.faces[i].n1 - 1];
    const vertex &n2 = model.normals[model.faces[i].n2 - 1];
    const vertex &n3 = model.normals[model.faces[i].n3 - 1];

    const vertex &t1 = model.textures[model.faces[i].t1 - 1];
    const vertex &t2 = model.textures[model.faces[i].t2 - 1];
    const vertex &t3 = model.textures[model.faces[i].t3 - 1];

    glNormal3f(n1.x, n1.y, n1.z);
    glTexCoord2f(t1.x, t1.y);
    glVertex3f(v1.x, v1.y, v1.z);

    glNormal3f(n2.x, n2.y, n2.z);
    glTexCoord2f(t2.x, t2.y);
    glVertex3f(v2.x, v2.y, v2.z);

    glNormal3f(n3.x, n3.y, n3.z);
    glTexCoord2f(t3.x, t3.y);
    glVertex3f(v3.x, v3.y, v3.z);
  }
  glEnd();
}

void displayPersp(void) {
  glMatrixMode(GL_MODELVIEW);

  glLoadIdentity();

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glPushMatrix();
  {
    if ((cam % 3) != 1) {
      glRotatef(angleY, 0, 1, 0);
    }

    glRotatef(rotX, 1, 0, 0);
		glRotatef(rotY, 0, 1, 0);

    glRotatef(90, 0, 1, 0);
    renderModel(table);

    glPushMatrix();
		{ 
      glTranslatef(0, 0.33, 0);
			renderModel(ball);
		}
		glPopMatrix();
    
    glBindTexture(GL_TEXTURE_2D, idBind);
    glBegin(GL_QUADS);
    {
		glVertex3f(-1.13f, 0.3f, -0.6f);
		glVertex3f(1.13f, 0.3f, -0.6f);
		glVertex3f(1.13f, 0.3f, 0.6f);
		glVertex3f(-1.13f, 0.3f, 0.6f);
  }
  glEnd();
  }
  glPopMatrix();

  glutSwapBuffers();
}

void init() {

  GLfloat posicaoLuz[4] = {0.0, 5.0, 0.0, 1.0};
	GLfloat luzAmbiente[4] = {0.15, 0.15, 0.15, 1.0};
	GLfloat luzDifusa[4] = {0.9, 0.9, 0.9, 1.0};
	GLfloat luzEspecular[4] = {0.9, 0.9, 0.9, 1.0};
	GLfloat especularidade[4] = {1.0, 1.0, 1.0, 1.0};

	GLint especMaterial = 50;

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
  	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
  	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);
  	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);
	
	glEnable(GL_COLOR_MATERIAL);
  	glEnable(GL_LIGHTING);
  	glEnable(GL_LIGHT0);
  	glEnable(GL_DEPTH_TEST);

  int id = loadTGA("wood.tga");
  table.textureId = id;
  loadObj("table.obj", table);
  id = loadTGA("ball.tga");
  ball.textureId = id;
  loadObj("ball.obj", ball);

  idBind = loadTGA("table.tga");
}

void resize(GLsizei w, GLsizei h) {
  if (h == 0) h = 1;

  glViewport(0, 0, w, h);

  fAspect = (GLfloat)w / (GLfloat)h;

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45, fAspect, 0.1, 100);
  gluLookAt(0, 3, angleY, 0, 0, 0, 1, 0, 0);
}

void change_camera() {
  angleY = 0;
  angleX = 0;
  cam++;
  if ((cam % 3) == 0)
    gluLookAt(0, 3, 3, 0, 0, 0, 0, 1, 0);
  else {
    if ((cam % 3) == 1)
      gluLookAt(0, 5, 0, 0, 0, 0, 1, 0, 0);
    else
      gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);
  }
}

void specialKeys(int key, int x, int y) {

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45, fAspect, 1, 100);
  gluLookAt(angleX, 3, angleY, 0, 0, 0, 1, 0, 0);


  switch (key)
	{
	case GLUT_KEY_LEFT:
		angleY -= taxa_Y;
		break;
	case GLUT_KEY_RIGHT:
		angleY += taxa_Y;
		break;
	case GLUT_KEY_UP:
		angleX += taxa_X;
		break;
	case GLUT_KEY_DOWN:
		angleX -= taxa_X;
		break;
	case 32:
		angleX = 0;
		angleY = 0;
		cam++;
		break;
	case 27:
		exit(0);
		break;
	}

  if (angleY > 8)
        angleY = 5;
  if (angleY < -8)
        angleY = -8;
  
  if (angleX > 8)
        angleX = 5;
  if (angleX < -8)
        angleX = -8;

  glutPostRedisplay();
  
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 27:
        exit(0);
        break;
	case 'w':
		rotY-=5;
		break;
	case 's':
		rotY+=5;
		break;
	case 'a':
		rotX-=5;
		break;
  case 'd':
		rotX+=5;
		break;
  default:
    break;
    }

  if (key == 32) {
    change_camera();
    glutPostRedisplay();
  }
    glutPostRedisplay();
}

void loop() {
  if ((cam % 3) == 0) {
    angleY += 0.05;
    glutPostRedisplay();
  }
}

int main(int argc, char *argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowPosition(0, 0);
  glutInitWindowSize(800, 600);
  glutCreateWindow("Avaliacao 03");
  glutDisplayFunc(displayPersp);
  glutIdleFunc(loop);
  glutReshapeFunc(resize);

  glutSpecialFunc(specialKeys);
  glutKeyboardFunc(keyboard);

  init();

  glutMainLoop();
  return 0;
}
