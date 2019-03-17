

#include "planoZ.h"

PlanoZ::~PlanoZ() {
	// TODO Auto-generated destructor stub
}
void PlanoZ::render(){
	Vector3D c=this->getColor();
	glColor3f(c.getX(),c.getY(),c.getZ());
    glBegin(GL_POLYGON);
        glVertex3f(-s, -s,p);
        glVertex3f( s, -s,p);
        glVertex3f( s,  s,p);
        glVertex3f(-s,  s,p);
    glEnd();
}
