

#include "particula.h"
#include "contorno.h"

Particula::~Particula() {
	// TODO Auto-generated destructor stub
}

 Contorno *Particula::getContorno(){
	return new Contorno(this->getP(), this->getRadio());
}
 bool Particula::colision(Solido *s) {
	Contorno *c = s->getContorno();
	return c->colision(this);
}

void Particula::render() {
	this->limpiaFuerza();
	this->acumulaFuerza(gravedad);
	this->aplicaFuerza(true);
	Vector3D posicion = this->getP();
	Vector3D color = this->getColor();
	double tx, ty, tz;
	tx = posicion.getX();
	ty = posicion.getY();
	tz = posicion.getZ();
	glPushMatrix();
	glTranslatef(tx, ty, tz);
	glColor3f(color.getX(),color.getY(), color.getZ());
	//glutWireSphere(r, 8, 8);
	glutSolidSphere(r, 15, 15);
	glPopMatrix();
}

