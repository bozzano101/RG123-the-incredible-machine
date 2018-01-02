#include <GL/glut.h>
#include "levels_draw.h"
#include "levels_animate.h"

extern void on_display();
extern void on_keyboard(unsigned char key, int x, int y);
extern void on_reshape(GLint width, GLint height);
extern void on_mousle_left_click(int button, int state,int x1, int y1);
extern void on_timer(int value);

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(1000, 600);
    glutInitWindowPosition(0,0);
    glutCreateWindow("NAZIV PROZORA");                              /* Promeniti naziv */

    glutDisplayFunc(on_display);
    glutKeyboardFunc(on_keyboard);
    glutReshapeFunc(on_reshape);
    glutMouseFunc(on_mousle_left_click);

    glColor3f(0,0,0);
    glEnable(GL_DEPTH_TEST);

    glutMainLoop();

    return 0;
}
