#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glext.h>
#pragma comment(lib, "glew32.lib")

#define STB_IMAGE_IMPLEMENTATION
#include <GL/stb_image.h>

// Classe responsavel por criar os planetas com suas respectivas caracteristicas
class Planeta{
public:
	float raio, distancia, orbita, velocidade, inclinacao, animacao;
	Planeta(float _raio, float _distance, float _orbit, float _orbitSpeed, float _axisTilt, float _axisAni){
		raio = _raio;
		distancia = _distance;
		orbita = _orbit;
		velocidade = _orbitSpeed;
		inclinacao = _axisTilt;
		animacao = _axisAni;
	}
};

float lightPos[] = { 0.0, 0.0, -75.0, 1.0 };
static float spotAngle = 40;
float spotDirection[] = { 1.0, 0.0, 0.0 };
static float spotExponent = 1.0;

// Funcao que carrega as texturas usando a biblioteca stb_image.h
unsigned int carregarTextura(char const* path)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}

// Cria a variavel que ira conter a textura de cada planeta
GLuint texturaSol, texturaMercurio, texturaVenus, texturaTerra, texturaMarte, texturaJupiter, texturaSaturno, texturaUrano, texturaNetuno, texturaFundo, paginaInicialTextura;

// Funcao para colocar o nome dos planetas
void nomePlaneta(void *font, char *string)
{
	char *c;
	for (c = string; *c != '\0'; c++) glutBitmapCharacter(font, *c);
}

// Funcao que configura as texturas dos planetas
void configuracaoTextura(void){

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

	// Carrega as texturas de todos os Planetas e do Sol para compor o Sistema Solar
	texturaFundo = carregarTextura("texturas/fundo.bmp");

	texturaSol = carregarTextura("texturas/sol.bmp");

	texturaMercurio = carregarTextura("texturas/mercurio.bmp");

	texturaVenus = carregarTextura("texturas/venus.bmp");

	texturaTerra = carregarTextura("texturas/terra.bmp");

	texturaMarte = carregarTextura("texturas/marte.bmp");

	texturaJupiter = carregarTextura("texturas/jupiter.bmp");

	texturaSaturno = carregarTextura("texturas/saturno.bmp");

	texturaUrano = carregarTextura("texturas/urano.bmp");

	texturaNetuno = carregarTextura("texturas/netuno.bmp");
}

// Cria o Sol
Planeta sol(5.0, 0, 0, 0, 0, 0);
// Cria o planeta Mercurio
Planeta mercurio(1.0, 7, 0, 4.74, 02.11, 0);
// Cria o planeta Venus
Planeta venus(1.5, 11, 0, 3.50, 177.0, 0);
// Cria o planeta Terra
Planeta terra(2.0, 16, 0, 2.98, 23.44, 0);
// Cria o planeta Marte
Planeta marte(1.2, 21, 0, 2.41, 25.00, 0);
// Cria o planeta Jupiter
Planeta jupiter(3.5, 28, 0, 1.31, 03.13, 0);
// Cria o planeta Saturno
Planeta saturno(3.0, 37, 0, 0.97, 26.70, 0);
// Cria o planeta Urano
Planeta urano(2.5, 45.5, 0, 0.68, 97.77, 0);
// Cria o planeta Netuno
Planeta netuno(2.3, 53.6, 0, 0.54, 28.32, 0);

// Inicia a animação "desligada"
int comecarAnimacao = 0;
// Inicia a zoom nos planetas com "80"
int zoom = 80;

// Cria a janela com o Sistema Solar
void janelaSistemaSolar(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	// Configura a perspectiva de visualização do Sistema Solar, no caso é frontal
	gluLookAt(0.0, 0.0, zoom, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	GLUquadric *quadric;
	quadric = gluNewQuadric();

	// SOL ---------------------------------------------------------------------------------------------

	// Configura a posição do Sol
	glPushMatrix();
	glRotatef(sol.orbita, 0.0, 1.0, 0.0);
	glTranslatef(sol.distancia, 0.0, 0.0);
	
	// Coloca o nome do Sol
	glRasterPos3f(-1.2, 7.0, 0.0);
	glColor3ub(255, 255, 255);
	nomePlaneta(GLUT_BITMAP_HELVETICA_12, "Sol");
	
	// Configura a inclinacao, animacao e textura do Sol
	glPushMatrix();
	glRotatef(sol.inclinacao, 1.0, 0.0, 0.0);
	glRotatef(sol.animacao, 0.0, 1.0, 0.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texturaSol);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	gluQuadricTexture(quadric, 1);
	gluSphere(quadric, sol.raio, 20.0, 20.0);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glPopMatrix();

	// MERCURIO ---------------------------------------------------------------------------------------------

	// Configura a posição do planeta
	glPushMatrix();
	glRotatef(mercurio.orbita, 0.0, 1.0, 0.0);
	glTranslatef(mercurio.distancia, 0.0, 0.0);

	// Coloca o nome do planeta
	glRasterPos3f(0.0, 3, 0.0);
	glColor3ub(255, 255, 255);
	nomePlaneta(GLUT_BITMAP_HELVETICA_12, "Mercurio");
	
	// Configura a inclinacao, animacao e textura do planeta
	glPushMatrix();
	glRotatef(mercurio.inclinacao, 1.0, 0.0, 0.0);
	glRotatef(mercurio.animacao, 0.0, 1.0, 0.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texturaMercurio);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	gluQuadricTexture(quadric, 1);
	gluSphere(quadric, mercurio.raio, 20.0, 20.0);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glPopMatrix();

	// VENUS ---------------------------------------------------------------------------------------------

	// Configura a posição do planeta
	glPushMatrix();
	glRotatef(venus.orbita, 0.0, 1.0, 0.0);
	glTranslatef(venus.distancia, 0.0, 0.0);

	// Coloca o nome do planeta
	glRasterPos3f(0.0, 3, 0.0);
	glColor3ub(255, 255, 255);
	nomePlaneta(GLUT_BITMAP_HELVETICA_12, "Venus");
	
	// Configura a inclinacao, animacao e textura do planeta
	glPushMatrix();
	glRotatef(venus.inclinacao, 1.0, 0.0, 0.0);
	glRotatef(venus.animacao, 0.0, 1.0, 0.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texturaVenus);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	gluQuadricTexture(quadric, 1);
	gluSphere(quadric, venus.raio, 20.0, 20.0);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glPopMatrix();

	// TERRA ---------------------------------------------------------------------------------------------

	// Configura a posição do planeta
	glPushMatrix();
	glRotatef(terra.orbita, 0.0, 1.0, 0.0);
	glTranslatef(terra.distancia, 0.0, 0.0);

	// Coloca o nome do planeta
	glRasterPos3f(0.0, 3, 0.0);
	glColor3ub(255, 255, 255);
	nomePlaneta(GLUT_BITMAP_HELVETICA_12, "Terra");

	// Configura a inclinacao, animacao e textura do planeta
	glPushMatrix();
	glRotatef(terra.inclinacao, 1.0, 0.0, 0.0);
	glRotatef(terra.animacao, 0.0, 1.0, 0.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texturaTerra);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	gluQuadricTexture(quadric, 1);
	gluSphere(quadric, terra.raio, 20.0, 20.0);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glPopMatrix();

	// MARTE ---------------------------------------------------------------------------------------------

	// Configura a posição do planeta
	glPushMatrix();
	glRotatef(marte.orbita, 0.0, 1.0, 0.0);
	glTranslatef(marte.distancia, 0.0, 0.0);

	// Coloca o nome do planeta
	glRasterPos3f(0.0, 3, 0.0);
	glColor3ub(255, 255, 255);
	nomePlaneta(GLUT_BITMAP_HELVETICA_12, "Marte");
	
	// Configura a inclinacao, animacao e textura do planeta
	glPushMatrix();
	glRotatef(marte.inclinacao, 1.0, 0.0, 0.0);
	glRotatef(marte.animacao, 0.0, 1.0, 0.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texturaMarte);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	gluQuadricTexture(quadric, 1);
	gluSphere(quadric, marte.raio, 20.0, 20.0);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glPopMatrix();

	// JUPITER ---------------------------------------------------------------------------------------------

	// Configura a posição do planeta
	glPushMatrix();
	glRotatef(jupiter.orbita, 0.0, 1.0, 0.0);
	glTranslatef(jupiter.distancia, 0.0, 0.0);

	// Coloca o nome do planeta
	glRasterPos3f(0.0, 4.4, 0.0);
	glColor3ub(255, 255, 255);
	nomePlaneta(GLUT_BITMAP_HELVETICA_12, "Jupiter");
	
	// Configura a inclinacao, animacao e textura do planeta
	glPushMatrix();
	glRotatef(jupiter.inclinacao, 1.0, 0.0, 0.0);
	glRotatef(jupiter.animacao, 0.0, 1.0, 0.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texturaJupiter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	gluQuadricTexture(quadric, 1);
	gluSphere(quadric, jupiter.raio, 20.0, 20.0);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glPopMatrix();

	// SATURNO ---------------------------------------------------------------------------------------------

	// Configura a posição do planeta
	glPushMatrix();
	glRotatef(saturno.orbita, 0.0, 1.0, 0.0);
	glTranslatef(saturno.distancia, 0.0, 0.0);

	// Coloca o nome do planeta
	glRasterPos3f(0.0, 4.4, 0.0);
	glColor3ub(255, 255, 255);
	nomePlaneta(GLUT_BITMAP_HELVETICA_12, "Saturno");
	
	// Configura a inclinacao, animacao e textura do planeta
	glPushMatrix();
	glRotatef(saturno.inclinacao, 1.0, 0.0, 0.0);
	glRotatef(saturno.animacao, 0.0, 1.0, 0.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texturaSaturno);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	gluQuadricTexture(quadric, 1);
	gluSphere(quadric, saturno.raio, 20.0, 20.0);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glPopMatrix();

	// URANO ---------------------------------------------------------------------------------------------

	// Configura a posição do planeta
	glPushMatrix();
	glRotatef(urano.orbita, 0.0, 1.0, 0.0);
	glTranslatef(urano.distancia, 0.0, 0.0);

	// Coloca o nome do planeta
	glRasterPos3f(0.0, 4.4, 0.0);
	glColor3ub(255, 255, 255);
	nomePlaneta(GLUT_BITMAP_HELVETICA_12, "Urano");
	
	// Configura a inclinacao, animacao e textura do planeta
	glPushMatrix();
	glRotatef(urano.inclinacao, 1.0, 0.0, 0.0);
	glRotatef(urano.animacao, 0.0, 1.0, 0.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texturaUrano);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	gluQuadricTexture(quadric, 1);
	gluSphere(quadric, urano.raio, 20.0, 20.0);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glPopMatrix();

	// NETUNO ---------------------------------------------------------------------------------------------

	// Configura a posição do planeta
	glPushMatrix();
	glRotatef(netuno.orbita, 0.0, 1.0, 0.0);
	glTranslatef(netuno.distancia, 0.0, 0.0);

	// Coloca o nome do planeta
	glRasterPos3f(0.0, 4.4, 0.0);
	glColor3ub(255, 255, 255);
	nomePlaneta(GLUT_BITMAP_HELVETICA_12, "Netuno");

	// Configura a inclinacao, animacao e textura do planeta
	glPushMatrix();
	glRotatef(netuno.inclinacao, 1.0, 0.0, 0.0);
	glRotatef(netuno.animacao, 0.0, 1.0, 0.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texturaNetuno);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	gluQuadricTexture(quadric, 1);
	gluSphere(quadric, netuno.raio, 20.0, 20.0);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glPopMatrix();

	// FUNDO ---------------------------------------------------------------------------------------------

	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texturaFundo);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBegin(GL_POLYGON);
	glTexCoord2f(-1.0, 0.0); glVertex3f(-200, -200, -100);
	glTexCoord2f(2.0, 0.0); glVertex3f(200, -200, -100);
	glTexCoord2f(2.0, 2.0); glVertex3f(200, 200, -100);
	glTexCoord2f(-1.0, 2.0); glVertex3f(-200, 200, -100);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texturaFundo);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 0.0); glVertex3f(-200, -83, 200);
	glTexCoord2f(8.0, 0.0); glVertex3f(200, -83, 200);
	glTexCoord2f(8.0, 8.0); glVertex3f(200, -83, -200);
	glTexCoord2f(0.0, 8.0); glVertex3f(-200, -83, -200);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glutSwapBuffers();
}


void redimensionar(int w, int h){
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-5.0, 5.0, -5.0, 5.0, 5.0, 200.0);
	glMatrixMode(GL_MODELVIEW);
}

// Funcao responsavel por executar a animacao dos planetas
void animacao(int n){
	if (comecarAnimacao){
		mercurio.orbita += mercurio.velocidade;
		venus.orbita += venus.velocidade;
		terra.orbita += terra.velocidade;
		marte.orbita += marte.velocidade;
		jupiter.orbita += jupiter.velocidade;
		saturno.orbita += saturno.velocidade;
		urano.orbita += urano.velocidade;
		netuno.orbita += netuno.velocidade;
		if (mercurio, venus, terra, marte, jupiter, saturno, urano, netuno.orbita > 360.0){
			mercurio, venus, terra, marte, jupiter, saturno, urano, netuno.orbita -= 360.0;
		}
		mercurio.animacao += 10.0;
		venus.animacao += 10.0;
		terra.animacao += 10.0;
		marte.animacao += 10.0;
		jupiter.animacao += 10.0;
		saturno.animacao += 10.0;
		urano.animacao += 10.0;
		netuno.animacao += 10.0;
		if (mercurio, venus, terra, marte, jupiter, saturno, urano, netuno.animacao > 360.0){
			mercurio, venus, terra, marte, jupiter, saturno, urano, netuno.animacao -= 360.0;
		}
		glutPostRedisplay();
		glutTimerFunc(30, animacao, 1);
	}
}

// Funcao responsavel por controlar a animacao do sistema solar, atraves do clique do mouse
void controleAnimacao(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		if (comecarAnimacao) {
			comecarAnimacao = 0;
		}
		else {
			comecarAnimacao = 1;
			animacao(1);
		}

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) exit(0);
	glutPostRedisplay();
}

// Funcao responsavel por controlar o zoom no sistema solar, atraves do scroll do mouse
void controleZoom(int wheel, int direction, int x, int y)
{
	if (direction > 0 && zoom < 100) zoom--;
	if (direction < 0 && zoom > -100) zoom++;
	glutPostRedisplay();
}

// Funcao principal
int main(int argc, char **argv){
	glutInit(&argc, argv);

	glutInitContextVersion(4, 2);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(1000, 800);
	glutInitWindowPosition(250, 0);
	glutCreateWindow("Trabalho Final de Computação Gráfica - Sistema Solar");
	glutDisplayFunc(janelaSistemaSolar);
	glutReshapeFunc(redimensionar);
	glutMouseFunc(controleAnimacao);
	glutMouseWheelFunc(controleZoom);
	glewExperimental = GL_TRUE;
	glewInit();

	configuracaoTextura();
	glutMainLoop();
}