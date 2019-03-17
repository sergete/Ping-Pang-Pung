/*
*
*
*
*
*/

#ifndef ESFERA_H_
#define ESFERA_H_
#include "solido.h"

class Esfera: public Solido {
	float r;
public:
	Esfera();
	Esfera(Vector3D p,float r=0.5):Solido(p),r(r){}
	virtual ~Esfera();
	void render();
	inline float getR() const {return r;}
	inline void setR(float r) {this->r = r;}
	inline void update(float dt) { this->setP(this->getP()+(this->getV()*dt)); }
	 Contorno *getContorno();
	 bool colision(Solido *s);
};

#endif /* ESFERA_H_ */
