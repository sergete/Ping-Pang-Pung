

#include "plano.h"
#include "contorno.h"

Plano::Plano() {
	a=b=c=d=0;
}
Plano::~Plano() {
}
bool Plano::colision(Solido *s){
	Contorno *c=s->getContorno();
	return c->colision(this);
}
