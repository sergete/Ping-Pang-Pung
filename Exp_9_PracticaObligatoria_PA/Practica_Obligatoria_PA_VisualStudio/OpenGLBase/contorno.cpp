

#include "contorno.h"

Contorno::~Contorno() {
	// TODO Auto-generated destructor stub
}

bool Contorno::colision(Plano *pl){
	Vector3D vn(pl->getA(),pl->getB(),pl->getC());
	return fabs(vn*p-pl->getD())<r;
}
bool Contorno::colision(Esfera *e){
	Vector3D pe=e->getP();
	float re=e->getR();
	Vector3D vd=pe-p;
	float l=vd.length();
	return l<r+re;
}
bool Contorno::colision(Cubo *c){
	Vector3D pc=c->getP();
	float rc=c->getS();
	Vector3D vd=pc-p;
	float l=vd.length();
	return l<r+rc;
}
bool Contorno::colision(Particula *par) {
	Vector3D pp = par->getP();
	float rp = par->getRadio();
	Vector3D vd = pp - p;
	float l = vd.length();
	return l<r+rp;
}

