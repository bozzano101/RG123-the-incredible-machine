#ifndef LEVELS_GLOBAL_H
#define LEVELS_GLOBAL_H

using namespace std;

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <regex>
#include "object.h"

string matrix[31][25];
vector<Object *> objects_on_scene;
vector<Object *> available_objects;
bool setup = false;

void prepare_matrix() {
/* Funkcija inicijalno postavlja svaki kvadrat mreze na free */
    for(int i = 0; i < 31; i++)
        for(int j = 0; j < 25; j++)
            matrix[i][j] = "free";
}

void modify_matrix(Object *obj) {
/* Funkcija menja mrezu posle dodavanja, ili pomeranja objekta.U zavisnosti od objekta
 * menja free na neki od navedenih radi lakseg operisanja prilikom sudara elemenata */
    for(int i=obj->get_x(); i<(obj->get_x()+obj->get_weight()); i++)
            for(int j=obj->get_y(); j<(obj->get_y()+obj->get_height()); j++)
            {
                    if(obj->get_type().substr(0,3) == "sta")
                            matrix[i][j] = "osta";
                    if(obj->get_type().substr(0,3) == "dyn")
                            matrix[i][j] = "odyn";
                    if(obj->get_type().substr(0,3) == "sti")
                            matrix[i][j] = "osti";
            }
}

void print_matrix() {
/* Funkcija koja printa trenutne vrednosti u matrici, lepo poravnate kao i ekran */
    for(int j=24; j>=0; j--) {
         for(int i=0; i<31; i++)
                cout<<matrix[i][j]<<" ";
         cout<<endl;
    }
}

void add_initial_objects(string path) {
/* Otvaramo fajl za ucitavanje objekata koji su inijalno na sceni. Parsiramo ih pomocu regex-a */

    string free("free");
    regex expr(R"(([a-zA-Z_]+)_(\d+\.?\d*)_(\d+\.?\d*)_(\d+\.?\d*)_(\d+\.?\d*)_([tf]))");
    smatch results;
    string line;

    ifstream file;
    file.open(path);

    while(getline(file,line)) {
            if(regex_search(line, results, expr)) {
                    // Sacuvamo rezultate parsiranja
                    float width = stof(results[2]);
                    float height = stof(results[3]);
                    float x = stof(results[4]);
                    float y = stof(results[5]);
                    string name = results[1];
                    bool c = results[6] == "t" ? true : false;

                    // OVO ISPOD JE MOZDA NE POTREBAN KOD ?
                    bool available = true;
                        for (int i = y; i <= y+height; i++)
                            for(int j = x; j <= x+width; j++)
                                if (matrix[j][i] != free)
                                    available = false;

                    // Pravimo objekte iz rezultata
                    if(available) {
                        if (name.substr(0,3) == "dyn") {
                            Dynamic *new_object = new Dynamic(width,height,x,y,0,+1,c,name);
                            modify_matrix(new_object);
                            objects_on_scene.push_back(new_object);
                        }

                        if (name.substr(0,3) == "sta") {
                            Static *new_object = new Static(width, height, x, y, name);
                            modify_matrix(new_object);
                            objects_on_scene.push_back(new_object);
                        }

                        if (name.substr(0,3) == "sti") {
                            Static_Interactable *new_object = new Static_Interactable(width, height, x, y, c, name, false);
                            modify_matrix(new_object);
                            objects_on_scene.push_back(new_object);
                        }
                    }
            }
    }

    file.close();
}

void load_available_objects(string path) {
/* Slicno kao i gornja funkcija samo nema vrednosti pozicije X i Y koord */
    regex expr(R"(([a-zA-Z_]+)_(\d+\.?\d*)_(\d+\.?\d*)_([tf]))");
    smatch results;
    string line;

    ifstream file;
    file.open(path);

    while(getline(file,line)) {
            if(regex_search(line, results, expr)) {
                float width = stof(results[2]);
                float height = stof(results[3]);
                string name = results[1];
                bool c = results[4] == "t" ? true : false;

                if (name.substr(0,3) == "dyn") {
                    Dynamic *new_object = new Dynamic(width,height,0,0,0,0,c,name);
                    available_objects.push_back(new_object);
                }

                if (name.substr(0,3) == "sta") {
                    Static *new_object = new Static(width,height,0,0,name);
                    available_objects.push_back(new_object);
                }

                if (name.substr(0,3) == "sti") {
                    Static_Interactable *new_object = new Static_Interactable(width,height,0,0,0,name,false);
                    available_objects.push_back(new_object);
                }

            }
        }
    file.close();
}

#endif // LEVELS_GLOBAL_H
