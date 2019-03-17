/*
*
*
*
*
*/

#ifndef CUBO_H_
#define CUBO_H_
#include "solido.h"

class Cubo : public Solido {
	float s;
public:
	Cubo();
	Cubo(Vector3D p,float s=4):Solido(p),s(s){}
	virtual ~Cubo();
	void render();
	inline float getS(){return s;}
	inline void setS(float s){this->s=s;}
	inline Contorno *getContorno();
	inline bool colision(Solido *s);
};

#endif /* CUBO_H_ */
