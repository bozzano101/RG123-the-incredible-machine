#ifndef LEVELS_INITIAL_H
#define LEVELS_INITIAL_H

#include "levels_global.h"

using namespace std;

#include <GL/glut.h>
#include "object.h"
#include <iostream>
#include <cmath>
#include <string>

// Vezano za postavlje scene i prozor
GLint window_width, window_height;
GLfloat total_width = 8;
GLfloat total_height = 5;
GLfloat add_panel_width = 1.8;
GLfloat add_panel_height = total_height / 8.0;
GLfloat add_panel_start = total_width - add_panel_width;

// Sluzi za identifikaciju selektovanog elementa
bool selector = false;
GLint selector_id = -1;

//levels_global.h
extern void prepare_matrix();
extern void modify_matrix();
extern void print_matrix();
extern string matrix[31][25];
extern vector<Object *> objects_on_scene;
extern vector<Object *> available_objects;
extern bool setup;
extern void add_initial_objects(string path);
extern void load_available_objects(string path);


void draw_screen_table();
void draw_selector_rect();
void draw_initial_objects();
void draw_available_objects();
void set_scene();


void on_display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    set_scene();
    if(!setup) {
        setup = !setup;
        prepare_matrix();
        add_initial_objects("data/level_1_initial.txt");
        load_available_objects("data/level_1_available.txt");
    }
    //print_matrix();
    draw_available_objects();
    draw_selector_rect();
    draw_initial_objects();
    draw_screen_table();
    glutSwapBuffers();
}

void on_reshape(GLint width, GLint height) {
    /* POTREBNO MODIFIKOVATI !!! Iskljuciti svaki vid resize-a */
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
    /* Funkcija za setup scene */
    glViewport(0, 0, window_width, window_height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (float) window_width/window_height, 1, 50);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(total_width/2.0,total_height/2.0,4.5,total_width/2.0,total_height/2.0,0,0,1,0);
}

void on_mousle_left_click(int button, int state, int x1, int y1) {
    /* Funkcija treba da reaguje samo na levi klik misem, treba i da reaguje na pritisak
     * misa a ne na otpustanje */
    if ((button != GLUT_LEFT_BUTTON) || (state != GLUT_DOWN))
        return;

    /* X i Y su kordinate koje "konvertuju" pikselske kordinate u scenske. */
    y1 = 600-y1;
    float x = (x1-40)/115.0;
    float y = (y1-10)/115.0;

    if((x >= 6) && (x <= 8) && (y >= 0) && (y <= 5)) {
        /* Kliknuto je u panel za odabir elemenata */
        if (selector == false) {
            selector_id = floor(y/0.625);
            selector = true;
            glutPostRedisplay();
        }
    }

    if((x >= 0) && (x <= 6.2) && (y >= 0) && (y <= 5)) {
        /* Kliknuto je u ekran za igru */
        if (selector == true) {
            /* Crtanje elementa na ekran ako je ispravno kliknuto, ako je uspesno, popunjavamo
             * matricu zauzeca prostora. Brisemo taj element iz available_object, i dodajemo
             * ga na object_on_scene, posto mu je tu i mesto */
            if((unsigned)(7-selector_id) < available_objects.size()) {

                    // Pronalazenje objekta sa datim selector_id-om
                    vector<Object *>::iterator it = available_objects.begin();
                    for(int i = 0; i<(7-selector_id);i++)
                        it++;

                    // Objekti u panelu ne znaju svoju poziciju, koju smo odredili klikom, pa postavljamo
                    (*it)->set_position_x(floor(x/0.2));
                    (*it)->set_position_y(floor(y/0.2));

                    // Inicijalizacija promenljivih za dalju obradu
                    bool available = true;
                    std::string free("free");

                    // Provera da li element nece "iskociti" sa ekrana
                    if((((*it)->get_x() + (*it)->get_weight()) > 31) || ((*it)->get_y() + (*it)->get_height()) > 25) {
                            available = false;
                            //cout<<"PREKORACIO";
                     }

                    /* Provera da li je element u koliziji sa nekim drugim. Prvi if stoji da ako krajevi elementa
                     * nisu u okviru ekrana, pristup tim elementima matrix[i][j] pravi segfault */
                    if(available)
                        for(int i = (*it)->get_x(); i < (*it)->get_x()+(*it)->get_weight(); i++)
                            for (int j = (*it)->get_y(); j < (*it)->get_y()+(*it)->get_height(); j++)
                                if(matrix[i][j] != free) {
                                        available = false;
                                        //cout<<"BLOKIRAN";
                                }
                    // Prosao sve provere, dodajemo ga na scenu, modifikujemo matricu, brisemo sa liste
                    if(available) {
                            objects_on_scene.push_back((*it));
                            modify_matrix((*it));
                            available_objects.erase(it);
                    }
            }
            // Selektor se vraca na pocetno stanje
            selector = false;
            selector_id = -1;
            glutPostRedisplay();
        }
    }

}

void draw_selector_rect() {
/* Funkcija crta sive pravougaonike kada selektujemo neki element iz panela za izbor elemenata */
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

void draw_initial_objects() {
/* Ova funkcija iscrtava sve objekte koji se nalaze u object_on_scene vektoru. Tu se nalaze svi objekti
 * koji se nalaze trenutno na ekranu. Prvi se dodaju elementi iz datoteke koja sadrzi inicijalne
 * elementi*/
    for(auto it = objects_on_scene.begin(); it != objects_on_scene.end(); it++)
        (*it)->draw_object();
}

void draw_available_objects() {
/* Ova funkcija se poziva da iscrta sve objekte koji se trenutno nalaze u available_objects.
 * Iscrtava u panelu za izbor elemenata */
    for(uint i = 7; i > 7-available_objects.size(); i--) {
        glColor3f(1,1,1);
        glBegin(GL_LINE_LOOP);
            glVertex3f(add_panel_start+0.15,      i*add_panel_height+0.15,                      0);
            glVertex3f(total_width-0.15,          i*add_panel_height+0.15,                      0);
            glVertex3f(total_width-0.15,          i*add_panel_height+add_panel_height-0.15,     0);
            glVertex3f(add_panel_start+0.15,      i*add_panel_height+add_panel_height-0.15,     0);
        glEnd();
    }
}
#endif // LEVELS_INITIAL_H
