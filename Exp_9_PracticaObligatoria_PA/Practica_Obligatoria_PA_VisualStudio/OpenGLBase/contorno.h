/*
*
*
*
*
*/

#ifndef CONTORNO_H_
#define CONTORNO_H_
#include <cmath>
#include "plano.h"
#include "planoX.h"
#include "planoY.h"
#include "planoZ.h"
#include "esfera.h"
#include "cubo.h"
#include "particula.h"


class Contorno{
	Vector3D p;
	float r;
public:
	Contorno(Vector3D p,float r):p(p),r(r){}
	virtual ~Contorno();
	bool colision(Plano *p);
	bool colision(Esfera *e);
	bool colision(Cubo *c);
	bool colision(Particula *par);
	const Vector3D& getP() const {return p;	}
	void setP(const Vector3D& p) {this->p = p;}
	float getR() const {return r;}
	void setR(float r) {this->r = r;}
};

#endif /* CONTORNO_H_ */
