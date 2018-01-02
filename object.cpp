#include "object.h"

using namespace std;

void Static::draw_object() {
    glColor3f(1,0,0);
    glBegin(GL_QUADS);
        glVertex3f(this->position_x*0.2, this->position_y*0.2, 0);
        glVertex3f((this->position_x+this->size_width)*0.2 , this->position_y*0.2, 0 );
        glVertex3f((this->position_x+this->size_width)*0.2 , (this->position_y+this->size_height)*0.2, 0 );
        glVertex3f(this->position_x*0.2 , (this->position_y+this->size_height)*0.2, 0 );
    glEnd();
}

void Dynamic::draw_object() {
    if(position_x == 0)
        this->move_x = 0;
    if(position_y == 0)
        this->move_y = 0;
    this->position_x += this->move_x;
    this->position_y += this->move_y;
    glColor3f(0,1,0);
    glBegin(GL_QUADS);
        glVertex3f(this->position_x*0.2, this->position_y*0.2, 0);
        glVertex3f((this->position_x+this->size_width)*0.2 , this->position_y*0.2, 0 );
        glVertex3f((this->position_x+this->size_width)*0.2 , (this->position_y+this->size_height)*0.2, 0 );
        glVertex3f(this->position_x*0.2 , (this->position_y+this->size_height)*0.2, 0 );
    glEnd();
}

void Static_Interactable::draw_object() {
    glColor3f(0,0,1);
    glBegin(GL_QUADS);
        glVertex3f(this->position_x*0.2, this->position_y*0.2, 0);
        glVertex3f((this->position_x+this->size_width)*0.2 , this->position_y*0.2, 0 );
        glVertex3f((this->position_x+this->size_width)*0.2 , (this->position_y+this->size_height)*0.2, 0 );
        glVertex3f(this->position_x*0.2 , (this->position_y+this->size_height)*0.2, 0 );
    glEnd();
}
