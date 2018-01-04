#include "object.h"

using namespace std;

void Static::draw_object() {
    glColor3f(1,0,0);
    glBegin(GL_QUADS);
        glVertex3f(this->_position_x*0.2, this->_position_y*0.2, 0);
        glVertex3f((this->_position_x+this->_size_width)*0.2 , this->_position_y*0.2, 0 );
        glVertex3f((this->_position_x+this->_size_width)*0.2 , (this->_position_y+this->_size_height)*0.2, 0 );
        glVertex3f(this->_position_x*0.2 , (this->_position_y+this->_size_height)*0.2, 0 );
    glEnd();
}

void Dynamic::draw_object() {
    glColor3f(0,1,0);
    glBegin(GL_QUADS);
        glVertex3f(this->_position_x*0.2, this->_position_y*0.2, 0);
        glVertex3f((this->_position_x+this->_size_width)*0.2 , this->_position_y*0.2, 0 );
        glVertex3f((this->_position_x+this->_size_width)*0.2 , (this->_position_y+this->_size_height)*0.2, 0 );
        glVertex3f(this->_position_x*0.2 , (this->_position_y+this->_size_height)*0.2, 0 );
    glEnd();
}

void Static_Interactable::draw_object() {
    glColor3f(0,0,1);
    glBegin(GL_QUADS);
        glVertex3f(this->_position_x*0.2, this->_position_y*0.2, 0);
        glVertex3f((this->_position_x+this->_size_width)*0.2 , this->_position_y*0.2, 0 );
        glVertex3f((this->_position_x+this->_size_width)*0.2 , (this->_position_y+this->_size_height)*0.2, 0 );
        glVertex3f(this->_position_x*0.2 , (this->_position_y+this->_size_height)*0.2, 0 );
    glEnd();
}
