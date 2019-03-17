/*
*
*
*
*
*/

#ifndef ESCENA_H_
#define ESCENA_H_
#include <vector>
#include "solido.h"

class Escena: public Solido {
	vector<Solido*> solidos;
	vector<Solido*> moviles;
	vector<Solido*> colisionables;
	vector<Solido*> limites;
public:
	Escena();
	virtual ~Escena();
	inline vector<Solido*> getSolidos() { return solidos; }
	inline void limiarEscena() { solidos.clear(), moviles.clear(), colisionables.clear(), limites.clear(); }
	void add(Solido *s){
		solidos.push_back(s);
		moviles.push_back(s);
		colisionables.push_back(s);
	}
	// only render
	void addSolido(Solido *s){
		solidos.push_back(s);
	}
	// render and collision not move
	void addFijo(Solido *s){
		solidos.push_back(s);
		colisionables.push_back(s);
	}
	void addLimite(Solido *s){
		solidos.push_back(s);
		limites.push_back(s);
	}
	inline void render(){
		for(Solido *r:solidos)
			r->render();
	}
	inline void update(float dt){
		for(Solido *s:moviles)
			s->update(dt);
	}
	inline void resuelveColisiones(){
		for(Solido *l:limites){
			for(Solido *s:moviles){
				if(l->colision(s)){
					l->resuelveColision(s);
				}
			}
		}
		for(Solido *m:moviles){
			for(Solido *c:colisionables){
				if(c!=m){
					if(m->colision(c)){
						m->resuelveColision(c);
					}
				}
			}
		}
	}
};

#endif /* ESCENA_H_ */
