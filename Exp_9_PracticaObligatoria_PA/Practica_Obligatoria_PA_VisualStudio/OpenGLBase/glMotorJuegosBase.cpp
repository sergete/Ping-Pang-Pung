/*
* Autores y expediente:
*
* Sergio Sánchez-Uran López 178
* Ana Maria Alcaide Recio 9
* Carlos Marques Gonzalez 100
*
*/

#include <stdio.h>
#include <string>
#include <GL/glew.h>
#include <GL/glut.h>
#include <vector>
#include <math.h>
#include "renderizable.h"
#include "cubo.h"
#include "escena.h"
#include "esfera.h"
#include "solido.h"
#include "planoY.h"
#include "planoX.h"
#include "planoZ.h"
#include "triangulo.h"
#include "modelo.h"
#include "contorno.h"
#include "plano.h"
#include "vector3d.h"
#include "particula.h"
#include <iostream>

GLint ancho = 400;

GLint alto = 400;
int hazPerspectiva = 1;
GLfloat angle = 0.0;
GLfloat yaw = 0.0;
GLfloat roll = 0.0;
GLfloat pitch = 0.0;
Particula p, *p2;
Particula *p1;
vector<Particula*> solidos;
Modelo *m;
Vector3D gravedad(0, -0.0008, 0);
float dt = 0;
float dt2 = 0;
float contador = 0;
float numbolas = 3;
bool partida = true;
int score = 0;
int totalscore = 0;
bool Acabado = false;
bool Loose = false;
bool colisionan = false;
int mejorPunt = 0;
bool menuopcion=false;
int espacio = 0;

char *GameOver = "GAME OVER";
char *Congratulations = "Congratulations!!";
char *texto = "ESQUIVA LAS BOLAS Y DISPARA";
char *ranking = "mejor puntuacion";

char *menu = "MENU PRINCIPAL";

Esfera *pf;
Escena e;

ofstream fichero("fichero.txt");

void drawString(char *s) {
	unsigned int i;
	for (i = 0; i < strlen(s); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, s[i]);

}
//para dibujar game over
void YouLose() {
	glColor3f(255.0, 0.0, 255.0);
	glRasterPos3f(-2.5, 3.0, 0.0);
	drawString(GameOver);
}

void YouWin() {
	glColor3f(0.0, 255.0, 0.0);
	glRasterPos3f(-3.5, 5.0, 0.0);

	drawString(Congratulations);
}

void init(void) {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glClearColor(0.0, 0.0, 0.0, 0.0);
}

void reshape(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0f, (GLfloat)width / (GLfloat)height, 1.0f, 200.0f);

	glMatrixMode(GL_MODELVIEW);
	ancho = width;
	alto = height;
}

void menuIncial() {

	char instrucciones4[200];
	sprintf_s(instrucciones4, "Utiliza las teclas 'W' 'A' 'S' 'D' para desplazarte y 'ESPACIO' para disparar");
	char *res5 = instrucciones4;
	glColor3f(1.0f, 1.0f, 0.0f);
	glRasterPos3f(-9.0f, 7.0f, 0.0f);
	drawString(res5);

	/*char instrucciones3[100];
	sprintf_s(instrucciones3, " ");
	char *res4 = instrucciones3;
	glColor3f(0.0f, 1.0f, 1.0f); //This is the problem, I dont have alpha but the brightness is low.
	glRasterPos3f(1.0f, 5.0f, 0.0f);
	drawString(res4);*/

	char instrucciones2[100];
	sprintf_s(instrucciones2, " PULSA 'H' PARA COMENZAR PARTIDA O PULSA 'ESC' SI QUIERES SALIR ");
	char *res3 = instrucciones2;
	glColor3f(0.0f, 1.0f, 1.0f);
	glRasterPos3f(-10.0f, 5.0f, 0.0f);
	drawString(res3);

	char instrucciones[30];
	sprintf_s(instrucciones, "INSTRUCCIONES");
	char *res2 = instrucciones;
	glColor3f(0.0f, 1.0f, 1.0f);
	glRasterPos3f(-3.5f, 8.0f, 0.0f);
	drawString(res2);

	
	glColor3f(0.0f, 1.0f, 0.0f);
	glRasterPos3f(-3.5f, 9.0f, 0.0f);
	drawString(menu);



}
//Calcula si la esfera del teclado choca o no con cada particula y la divide en dos más pequeñas
//en direcciones distintas y si choca con el modelo para la escena e indica que has muerto
void calculaColision() {

	for (Particula *s : solidos) {

		Vector3D pe = s->getP();
		float re = s->getRadio();
		Vector3D vd = pe - m->getP();
		float l = vd.length();

		if (l < m->getAncho() / 2 + re) {
			
			for (Particula *pk : solidos) {
				pk->setDireccion(Vector3D(0, 0, 0));
				pk->setGravedad(Vector3D(0, 0, 0));
				pk->setV(Vector3D(0, 0, 0));
				
			}
			partida = false;
		
		}
		if (pf != nullptr) {
			if (pf->colision(s))
			{
				pf = nullptr;
				if (s->getContador() < 2) {
					
					s->setDireccion(s->getDireccion()*-1);
					s->setV(s->getV() *0.80f);
					s->setGravedad(s->getGravedad() * 1.30f);
					s->setRadio(s->getRadio() *0.70f);
					s->setContador(s->getContador() + 1);
					
					Vector3D pos;
					Vector3D vel;
					Vector3D col;
					Vector3D dir;
					Particula *p3;
					p3 = new Particula();
					dir = s->getDireccion()*-1;
					p3->setDireccion(dir);
					p3->setV(s->getV());
					p3->setGravedad(s->getGravedad());
					p3->setP(s->getP());
					p3->setRadio(s->getRadio());
					p3->setContador(s->getContador());
					p3->setColor(Vector3D(1, 0, 0));
				
					e.add(p3);
					solidos.push_back(p3);
					totalscore++;
					score++;
				}
				else {
					s->setRadio(0);
					s->setDireccion(Vector3D(0, 0, 0));
					s->setGravedad(Vector3D(0, 0, 0));
					s->setV(Vector3D(0, 0, 0));
					s->setP(Vector3D(0, -10, 0));
					s = nullptr;
					contador++;
					totalscore++;
					score++;
				}
			}
		}
	}
}

void MejorPuntuacion (){

	if (totalscore> mejorPunt) {
		mejorPunt = totalscore;
	}
}
void Textos() {
	//Textos BIENVENIDO
	

	if (partida == true) {
		
		drawString(texto);
		glColor3f(0.0f, 1.0f, 1.0f);
		glRasterPos3f(-4.0f, 5.0f, 0.0f);
		

	}

	
	if (partida == false) {

		//REPRESENTACIÓN DE LA PUNTUACIÓN
		//creamos una variable char donde almacenaremos el texto
		char resultado[20];
		//función que permite representar de forma textual nuestra puntuacion.
		sprintf_s(resultado, "Puntuacion: %d", score);
		MejorPuntuacion();
		char ranking2[30];
		sprintf_s(ranking2, "mejor puntuacion:%d", mejorPunt);
		//cuando saquemos la puntuación llamamos a la funcion de GAMEOVER 
		YouLose();
		//creamos un char* que contendrá el texto generado en la función anterior
		char *res = resultado;
		//asignamos el color y la posicion en la escena y lo pintamos
		glColor3f(0.0, 255.0, 255.0);
		glRasterPos3f(-3.5, 7.0, 0.0);
		drawString(res);

		char *mejor = ranking2;
		glColor3f(1.0f, 0.5f, 0.5f);
		glRasterPos3f(-3.5f, 8.0f, 0.0f);
		drawString(mejor);

		//Esto solo para que aparezca por pantalla
		char continuar[50];
		sprintf_s(continuar, "Para reiniciar partida pulse 'E'");
		glColor3f(1.0f, 1.0f, 0.0f);
		glRasterPos3f(-3.5f, 6.0f, 0.0f);
		drawString(continuar);

		char resetear[150];
		sprintf_s(resetear, "pulsa 'b' para que se reseteen los puntos en la siguiente partida");
		glColor3f(1.0f, 1.0f, 0.0f);
		glRasterPos3f(-7.5f, 5.0f, 0.0f);
		
		drawString(resetear);
		
		
	}
}
void cargarModelo() {
	
	Vector3D rojo(1, 0, 0), amarillo(1, 1, 0), verde(0, 1, 0), azul(0, 0, 1);
	//creamos las caracteristicas del modelo y cargamos el modelo con una función de escalado para
	//adaptarlo a la escena
	m = new Modelo("../Debug/minion.obj",0.2);
	m->setColor(amarillo);
	m->setP(Vector3D(0, 0, 5));
	m->setV(Vector3D(2.5, 0, -2.5));
}


void displayMe(void)
{
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(0, 3, 15, 0, 0, 0, 0, 1, 0);
	
	glDisable(GL_LIGHTING);
	glRotatef(yaw, 0.0, 1.0, 0.0);
	glRotatef(pitch, 1.0, 0.0, 0.0);
	glRotatef(roll, 0.0, 0.0, 1.0);
	GLfloat lightpos[] = { 5.0, 15., 5., 0. };
	glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
	
	
	if (menuopcion == false) {
		menuIncial();
	}
	else {	
		Textos();
	}

		glEnable(GL_LIGHTING);	
		e.render();
		
		m->render();

		if (pf != nullptr)
			pf->render();

		glutSwapBuffers();
		angle++;
	
}

//función calcula un número al azar
float getRand(float max, float min = 0) {
	float n = max - min;
	int ir = rand() % 1000;
	return min + n*(float)ir / 1000;
}


void cargarPantalla(float tamaño) { 
		
	 dt = 0.01;
	 dt2 = 0.05;

	//creamos particulas con direcciones al azar y posiciones en el eje X al azar
	for (int i = 0; i < numbolas; i++) {
		float random = 0;
		p1 = new Particula();
		p1->setP(Vector3D(getRand(20, -20), 2, 5.0));
		p1->setV(Vector3D(0, 0.07, 0));
		while (random == 0)
			random = round(getRand(1, -1));
		p1->setDireccion(Vector3D(random, 0, 0));
		p1->setColor(Vector3D(1, 0, 0));
		e.add(p1);
		solidos.push_back(p1);
	}

	Vector3D rojo(1, 0, 0), amarillo(1, 1, 0), verde(0, 1, 0), azul(0, 0, 1);

	PlanoY *y;
	y = new PlanoY();

	e.addLimite(y);
	PlanoX *x;
	PlanoX *dx;
	x = new PlanoX(-20);
	e.addLimite(x);
	dx = new PlanoX(20);
	e.addLimite(dx);
	x->setColor(azul);
	dx->setColor(azul);
	Plano *z;
	Plano *dz;
	z = new PlanoZ(-20);
	e.addLimite(z);
	dz = new PlanoZ(20);
	e.addLimite(dz);
	z->setColor(verde);
	dz->setColor(verde);

	Sleep(3000);

	score = 0;
	if (numbolas < 4)
		totalscore = 0;


}



//Comprobamos si el tamaño del array es 0 lo que significa que podemos empezar con la segunda pantalla
void compruebaPartida() {
	
	
	if (contador >= 4 * numbolas) {
		if (numbolas < 6) {
			numbolas += 3;
			e.limiarEscena();
			solidos.clear();
			contador = 0;
			totalscore = score;
			MejorPuntuacion();
			cargarPantalla(numbolas);
		}
		else
		{
			score += totalscore;
			MejorPuntuacion();
			//partida = false;
			YouWin();
		}
	}
}


void idle()//star
{
	
	displayMe();
	if (partida == true) {
		
		e.update(dt);
		if (pf != nullptr) {
			pf->update(dt2);
		}
	}
	menuopcion = true;
	
	compruebaPartida();
	calculaColision();
	Sleep(5);
}
Vector3D pos;
Vector3D posobj;



void keyPressed(unsigned char key, int x, int y) {
	

	x++;
	y++;
	
	switch (key)
	{
	case 'p':
	case 'P':
		yaw++;
		break;
	case 'e': 
	case 'E':
		if (fichero.is_open()) {
			cout << "entra" << endl;
			fichero << "Mejor puntuacion: " << mejorPunt << endl;
			fichero << "Puntuacion total " << score << endl;
			fichero.close();
		}
		else if (!fichero.is_open()) {
			cout << "entra else" << endl;
			fichero.open("fichero.txt");
			fichero << "Mejor puntuacion: " << mejorPunt << endl;
			fichero << "Puntuacion total " << score << endl;
			fichero.close();
		}
		else {
			cout << "No se puede abrir" << endl;
		
		}
		partida = true;
		contador = 0;
		totalscore -= score;
		dt = 0;
		dt2 = 0;
		e.limiarEscena();
		solidos.clear();
		m->setP(Vector3D(0, 0, 5));
		cargarPantalla(numbolas);
		
	
		
		break;
	case 'b':
		partida = true;
		contador = 0;
		mejorPunt = 0;
		totalscore = 0;
		dt = 0;
		dt2 = 0;
		e.limiarEscena();
		solidos.clear();
		m->setP(Vector3D(0, 0, 5));
		cargarPantalla(numbolas);
		break;
	case 'o':
	case 'O':
		yaw--;
		break;
	case 'x':
	case 'X':
		pitch++;
		break;

	case 'z':
	case 'Z':
		pitch--;
		break;
	case 'w':
	case 'W':
		roll++;
		break;

	case 'q':
	case 'Q':
		roll--;
		break;
	case 'a':
	case 'A':
		
		//Si la partida está activa podremos mover el personaje
		if (partida == true)
			m->setP(m->getP() - Vector3D(0.40, 0, 0));
		posobj = m->getP();
		if (posobj.getX() <= -20)
			m->setP(Vector3D(-20.0f, 0.0f, 0.0f));
			
		break;
	case 'd':
	case 'D':
		
		//Si la partida está activa podremos mover el personaje
		if (partida == true)
			m->setP(m->getP() + Vector3D(0.40, 0, 0));
		posobj = m->getP();
		if (posobj.getX() >= 20)
			m->setP(Vector3D(20.0f, 0.0f, 0.0f));
		break;
	case ' ':
		
		//Pelota que choca contra los minions
		pf = new Esfera();
		pos = Vector3D(m->getP());
		pf->setP(Vector3D(pos.getX(), pos.getY() + m->getAlto(), pos.getZ()));
		pf->setV(Vector3D(0, 3, 0.0));
		pf->setColor(Vector3D(1, 0.5, 0));
		pf->setR(0.2);
		//e.add(pf);
		colisionan = true;

		break;
	case 'h':
		
		cargarPantalla(numbolas);
		glutIdleFunc(idle);
		
		break;

	case 27:   // escape
		exit(0);
		break;
	}
}

//FUNCION QUE FIJA EL WINDOW SIZE A TAMAÑO COMPLETO ESC PARA SALIR
void draw()
{
	// code for rendering here
	glutSwapBuffers();   // swapping image buffer for double buffering
	glutPostRedisplay(); // redrawing. Omit this line if you don't want constant redraw
}

int main(int argc, char** argv)
{
	
	cout << "pulsa enter para empezar" << endl;
	system("pause");
	cargarModelo();
	//Textos();
	

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(100, 50);
	glutCreateWindow("Pang");
	glutFullScreen();           // making the window full screen
	glutDisplayFunc(draw);
	init();

	glutDisplayFunc(displayMe);
	
	
	//glutIdleFunc(idle);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyPressed); // Tell GLUT to use the method "keyPressed" for key presses
	
	glutMainLoop();
	return 0;
}


