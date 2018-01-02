#ifndef LEVELS_ANIMATE_H
#define LEVELS_ANIMATE_H

#define TIMER_ID 0
#define TIMER_INTERVAL 100
int animation_ongoing = 0;
void on_timer(int value);

void on_keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 27:
        exit(0);
        break;
    case 'S':
    case 's':
        if (!animation_ongoing) {
                   glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
                   animation_ongoing = 1;
               }
        break;
    case 'P':
    case 'p':
        animation_ongoing = 0;
        break;
    }
}

void on_timer(int value)
{
    if (value != TIMER_ID)
        return;



    glutPostRedisplay();
    if (animation_ongoing) {
        glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
    }
}
#endif // LEVELS_ANIMATE_H
