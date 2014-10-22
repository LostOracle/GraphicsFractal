#ifndef _CALLBACKS_H_
#define _CALLBACKS_H_

#include <GL/glut.h>

static const int MouseRightButton = 1;
static const int MouseLeftButton = 0;
static const int MouseButtonPress = 0;
static const int MouseButtonRelease = 1;
static const int MouseMiddleButton = 2;




void display( void );
void reshape(int w, int h);
void mouseclick( int button, int state, int x, int y);
void mousedrag( int x, int y);
void initOpenGL( void );
#endif
