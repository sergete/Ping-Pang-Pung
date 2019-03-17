

#include "solido.h"
#include "contorno.h"

Solido::Solido() {
	// TODO Auto-generated constructor stub
}
Solido::~Solido() {
	// TODO Auto-generated destructor stub
}
Contorno *Solido::getContorno(){
	return new Contorno(Vector3D(0,0,0),1);
}

void Solido::resuelveColision(Solido *s){
	Vector3D vn=s->getP()-this->getP();
	vn.normalize();
	Vector3D vv=s->getV();
	Vector3D vr=vv.reflect(vn);
	s->setV(vr);
}
