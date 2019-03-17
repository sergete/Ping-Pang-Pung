/*
 * 
 *
 *  
 *     
 */

#ifndef PARTICULA_H_
#define PARTICULA_H_

#include <iostream>
#include <GL/glut.h>
#include "solido.h"
#include <math.h>
#include "escena.h"

using namespace std;

class Particula: public Solido {
	double masa;
	float r;
	//Vector3D posicion;
	//Vector3D velocidad;
	Vector3D fuerza;
	//Vector3D color;
	Vector3D gravedad;
	float pos;
	Vector3D direccion;
	float contador;
public:
	inline Particula(double x = 0.0, double y = 0.0, double z = 0.0) :masa(1.0), r(0.6), Solido(Vector3D(x, y, z)), direccion(1, 0, 0), gravedad(0.0f, -0.0006f, 0.0f), contador (0) {}
	virtual ~Particula();
	inline Vector3D& getFuerza(){return fuerza;}
	inline float getRadio() { return r; }
	inline void setRadio(float r) { this->r = r; }
	inline Vector3D getDireccion() { return direccion; }
		inline void setDireccion(Vector3D dir) { this->direccion = dir; }
	inline Vector3D getGravedad() { return gravedad; }
	inline void setGravedad(Vector3D g) { this->gravedad = g; }
	inline float getContador() { return contador; }
	inline void setContador(float c) { this->contador = c; }
	inline Contorno *getContorno();
	inline bool colision(Solido * s);
	void render();
	inline void limpiaFuerza(){fuerza=Vector3D(0,0,0);}
	inline void acumulaFuerza(Vector3D f){fuerza+=f;}
	inline void aplicaFuerza(bool opcion){
		Vector3D aceleracion=fuerza/masa;
		this->setV(this->getV() + aceleracion);
		if (opcion == false)
			actualiza();
		else
			calculaParabola();
	}
	inline void actualiza(){
		float vx,vy,vz;
		Vector3D p = Vector3D(this->getP() + this->getV());
		Vector3D velocidad = this->getV();
		if (p.getY()<=0){
			vx=velocidad.getX();
			vy=velocidad.getY();
			vz=velocidad.getZ();
			this->setV(Vector3D(vx,-vy*0.8,vz));
		}
		else if (fabs(p.getX()) > 2) {
			this->setV(Vector3D(velocidad.getX()* (-0.98), velocidad.getY()* (-0.98), velocidad.getZ()*(-0.98)));
			//velocidad *= -0.98;
		}
		else {
			this->setP(p);
			 }
	}

	inline void calculaParabola() {
		float vx, vy, vz;
		Vector3D p = Vector3D(this->getP() + this->getV());
		Vector3D velocidad = this->getV();
		Vector3D dir = Vector3D(direccion);
		if (p.getY() <= 0) {
			vx = velocidad.getX();
			vy = velocidad.getY();
			vz = velocidad.getZ();
			this->setV(Vector3D(vx, -vy, vz));
			//t = true;
		}
		else {
			//if (t == true) {
				float angle = 45 * (3.1415926 / 180.0);
				angle = cos(angle)/10;
				float x = p.getX();
				float z = p.getZ();
				if (x <= -20 || z <= -20) {
					if (x <= -20) {
						dir.setX(1);
						x += angle*dir.getX();
						
					}
					else{
						dir.setZ(1);
						z += angle*dir.getZ();
					}
					
				}
				else if (x >= 20  || z >=20) {
					if (x >= 20) {
						dir.setX(-1);
						x += angle*dir.getX();
						
					}
					if (z >= 20) {
							dir.setZ(-1);
							z += angle*dir.getZ();
							
					}
				}
				else {
					x += angle*dir.getX();
					z += angle*dir.getZ();
					
				}
				
				p.setX(x);
				p.setZ(z);
				this->setDireccion(dir);
				this->setP(p);
				
			
		}
	}

};


#endif /* PARTICULA_H_ */
