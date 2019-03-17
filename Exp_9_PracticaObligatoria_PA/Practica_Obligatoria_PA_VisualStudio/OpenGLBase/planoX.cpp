


#include "planoX.h"
#include "contorno.h"
PlanoX::~PlanoX() {
	// TODO Auto-generated destructor stub
}

void PlanoX::render(){
	Vector3D c=this->getColor();
	glColor3f(c.getX(),c.getY(),c.getZ());
    glBegin(GL_POLYGON);
        glVertex3f(p,-s, -s);
        glVertex3f(p, s, -s);
        glVertex3f(p, s,  s);
        glVertex3f(p,-s,  s);
    glEnd();
}

