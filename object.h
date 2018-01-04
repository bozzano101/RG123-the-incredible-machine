#ifndef OBJECT_H
#define OBJECT_H

using namespace std;
#include <string>
#include <iostream>
#include <GL/glut.h>

class Object
{
protected:
    float _size_width;
    float _size_height;
    float _position_x;
    float _position_y;
    bool _connectable;
    string _type;
public:
    Object(float size_width, float size_height, float position_x, float position_y, bool connectable, string type)
        :_size_width(size_width), _size_height(size_height), _position_x(position_x), _position_y(position_y),
         _connectable(connectable), _type(type)
        {}

    virtual void draw_object() = 0;  
    bool is_connectable()                           { return _connectable; }

    void set_size_width(float width)                { _size_width = width; }
    void set_size_height(float height)              { _size_height = height; }
    void set_position_x(float x)                    { _position_x = x; }
    void set_position_y(float y)                    { _position_y = y; }

    float get_x()                                   { return _position_x; }
    float get_y()                                   { return _position_y; }
    float get_height()                              { return _size_height; }
    float get_weight()                              { return _size_width; }
    string get_type()                               { return _type; }
};

/*******************************************************************************************************************/

class Static : public Object
{
    /* Klasa Static opisuje elemente poput cevi, zidova, merdevina i sl. To su elementi koji se ne pomeraju
     * ne aktiviraju druge elemente, vec samo predstavlju prepreku za sve ostale elemente.
     * Povezivost je inicijalno postavljena na false, jer ne mogu ni da se povezuju
     */
public:
    Static(float size_width, float size_height, float position_x, float position_y, string type)
        :Object(size_width, size_height, position_x, position_y, false, type)
        {}
    void draw_object();
};

/********************************************************************************************************************/

class Dynamic : public Object
{
    /* Klasa Dynamic opisuje elemente koji se pomeraju poput lopti, balona i slicno. To su elementi koji imaju vektore pomeranja
     * move_x i move_y koji ce im u svakom ponovnom iscrtavanju slike reci gde se nalaze
     */
public:
    Dynamic(float size_width, float size_height, float position_x, float position_y, float move_x, float move_y, bool connectable, string type)
        :Object(size_width, size_height, position_x, position_y, connectable, type), _move_x(move_x), _move_y(move_y)
        {}
    void draw_object();
    void set_move_x(float x)                    { _move_x = x; }
    void set_move_y(float y)                    { _move_y = y; }

private:
    float _move_x;
    float _move_y;
};

/********************************************************************************************************************/

class Static_Interactable : public Object
{
    /*
     * Klasa Static_Interactable opisuje staticke elemente koji menjaju okolinu oko sebe. To su objekti poput motora,
     * zupcanika, trampolina, tredmill-a i slicnih. activated parametar odredjuje da li dati element interaguje sa okolinom
     * (motor upaljen, zupcanik se okrece itd) ili ne
     */
public:
    Static_Interactable(float size_width, float size_height, float position_x, float position_y, bool connectable, string type, bool activated)
        :Object(size_width, size_height, position_x, position_y, connectable, type), _activated(activated)
        {}
    void draw_object();

protected:
    bool _activated;
};

/*********************************************************************************************************************/

#endif // OBJECT_H
