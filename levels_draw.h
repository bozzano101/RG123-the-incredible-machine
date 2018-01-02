#ifndef LEVELS_INITIAL_H
#define LEVELS_INITIAL_H

using namespace std;

#include <GL/glut.h>
#include "object.h"
#include <iostream>
#include <cmath>
#include <string>

GLint window_width, window_height;
GLfloat total_width = 8;
GLfloat total_height = 5;
GLfloat add_panel_width = 1.8;
GLfloat add_panel_height = total_height / 8.0;
GLfloat add_panel_start = total_width - add_panel_width;
bool selector = false;
GLint selector_id = -1;
string matrix[31][25];

void draw_screen_table();                                                        /* Narandzasta mreza i plava pozadina */
void draw_selector_rect();                                                       /* Prilikom selektovanja menja boju */
void set_scene();
void prepare_matrix();

void on_display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    set_scene();
// DEBUG HERE

// DEBUG HERE
    draw_selector_rect();
    draw_screen_table();

    glutSwapBuffers();
}

void on_reshape(GLint width, GLint height) {
    window_height = height;
    window_width = width;
}

void draw_screen_table() {
        /* Crta narandzaste okvire */
    glColor3f(235/255.0, 77/255.0, 26/255.0);
    glLineWidth(2.5);
    glBegin(GL_LINE_LOOP);
        glVertex3f(0,0,0);
        glVertex3f(total_width-add_panel_width,0,0);
        glVertex3f(total_width - add_panel_width,total_height,0);
        glVertex3f(0,total_height,0);
    glEnd();
    for(int i = 0; i < 8; i++) {
        glBegin(GL_LINE_LOOP);
            glVertex3f(add_panel_start,i*add_panel_height,0);
            glVertex3f(total_width,i*add_panel_height,0);
            glVertex3f(total_width,i*add_panel_height+add_panel_height,0);
            glVertex3f(add_panel_start,i*add_panel_height+add_panel_height,0);
        glEnd();
    }
        /* Crta sivu mrezu */
    glColor3f(0.9,0.9,0.9);
    glLineWidth(1);
    glBegin(GL_LINES);
        for(float i = 0.2; i < 5; i=i+0.2) {
            glVertex3f(0, i, 0);
            glVertex3f(6.2, i, 0);
        }
        for(float i = 0.2; i < 6.2; i=i+0.2) {
            glVertex3f(i, 0, 0);
            glVertex3f(i, 5, 0);
        }
    glEnd();
        /* Crta plavu pozadinu */
    glColor3f(31/255.0, 184/255.0, 255/255.0);
    glBegin(GL_QUADS);
        glVertex3f(0,0,0);
        glVertex3f(total_width,0,0);
        glVertex3f(total_width,total_height,0);
        glVertex3f(0,total_height,0);
    glEnd();

}

void set_scene() {
    glViewport(0, 0, window_width, window_height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (float) window_width/window_height, 1, 50);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(total_width/2.0,total_height/2.0,4.5,total_width/2.0,total_height/2.0,0,0,1,0);
}

void on_mousle_left_click(int button, int state, int x1, int y1) {
    if ((button != GLUT_LEFT_BUTTON) || (state != GLUT_DOWN))
        return;
    // Proracun kordinata iz pikselskih u scenske
    y1 = 600-y1;
    float x = (x1-40)/115.0;
    float y = (y1-10)/115.0;
    if((x >= 6) && (x <= 8) && (y >= 0) && (y <= 5)) {
        // Kliknuto je u deo za dodavanje elemenata
        if (selector == false) {
            selector_id = floor(y/0.625);
            selector = true;
            glutPostRedisplay();
        }
    }

    if((x >= 0) && (x <= 6.2) && (y >= 0) && (y <= 5)) {
        // Kliknuto je u deo za igru
        std::cout<<"X: "<<floor(x/0.2)<<" Y: "<<floor(y/0.2)<<std::endl;
        if (selector == true) {
            selector = false;
            selector_id = -1;
            glutPostRedisplay();
        }
    }

}

void draw_selector_rect() {
    if(selector_id != -1) {
        glColor3f(181/225.0,231/255.0,235/255.0);
        glBegin(GL_QUADS);
            glVertex3f(add_panel_start+0.05,      selector_id*add_panel_height+0.05,                      0);
            glVertex3f(total_width-0.05,          selector_id*add_panel_height+0.05,                      0);
            glVertex3f(total_width-0.05,          selector_id*add_panel_height+add_panel_height-0.05,     0);
            glVertex3f(add_panel_start+0.05,      selector_id*add_panel_height+add_panel_height-0.05,     0);
        glEnd();
    }
}

void prepare_matrix(){
    for(int i = 0; i < 31; i++)
        for(int j = 0; j < 25; j++)
            matrix[i][j] = "";
}
#endif // LEVELS_INITIAL_H
