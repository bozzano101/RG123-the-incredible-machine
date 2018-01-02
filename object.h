#ifndef OBJECT_H
#define OBJECT_H

using namespace std;
#include <string>
#include <iostream>
#include <GL/glut.h>

class Object
{
    /* Klasa Object je osnovna klasa za svaki element koji mozemo da dodamo. Svaki element mora da ima:
     *
     *          Poziciju        - zadatu sa X i Y
     *          Velicinu        - zadatu sa width i height
     *          Tip             - zadat sa type radi identifikacije objekta prilikom crtanja
     *          Povezivost      - true ako jeste, false ako nije
     *          is_connectable()   - true ako se moze povezati, false ako ne moze
     *          draw_object()   - svaki objekat se mora iscrtati. Apstraktno jer zavisi od tipa
     */
protected:
    float size_width;
    float size_height;
    float position_x;
    float position_y;
    bool connectable;
    string type;
public:
    Object(float sw, float sh, float px, float py, bool c, string typ)
        :size_width(sw), size_height(sh), position_x(px), position_y(py), connectable(c), type(typ)
        {}
    virtual void draw_object() = 0;
    bool is_connectable() {
        return connectable;
    }
};

/*******************************************************************************************************************/

class Static : public Object
{
    /* Klasa Static opisuje elemente poput cevi, zidova, merdevina i sl. To su elementi koji se ne pomeraju
     * ne aktiviraju druge elemente, vec samo predstavlju prepreku za sve ostale elemente.
     * Povezivost je inicijalno postavljena na false, jer ne mogu ni da se povezuju
     */
public:
    Static(float sw, float sh, float px, float py, string typ)
        :Object(sw,sh,px,py,false,typ)
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
    Dynamic(float sw, float sh, float px, float py, float mvx, float mvy, bool c, string typ)
        :Object(sw,sh,px,py,c,typ), move_x(mvx), move_y(mvy)
        {}
    void draw_object();
protected:
    float move_x;
    float move_y;
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
    Static_Interactable(float sw, float sh, float px, float py, bool c, bool act, string typ)
        :Object(sw,sh,px,py,c,typ), activated(act)
        {}
    void draw_object();
protected:
    bool activated;
};

/*********************************************************************************************************************/

#endif // OBJECT_H
