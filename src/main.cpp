/******************************************************************************
 * File: main.cpp
 * Authors: Ian Carlson, Christopher Smith
 * Description: Entry point for the fractal program. Kicks off all three
 *  windows - initiator, generator, and display
 *****************************************************************************/

#include <GL/freeglut.h>
#include <vector>
#include "../include/shared_constants.h"
#include "../include/common_functions.h"
#include "../include/initiator_init.h"
#include "../include/generator_init.h"
#include "../include/fractal_init.h"
using namespace std;

void glInit();
/******************************************************************************
 * Function: main
 * Paramteres:
 *  argc - used by glut(?)
 *  argv - used by glut(?)
 * Returns: 0
 * Description: Program entry point. Initializes the windows and starts the 
 *  glut main loop
 *****************************************************************************/
int main( int argc, char *argv[] )
{
    glutInit( &argc, argv );
    glInit();

    // go into OpenGL/GLUT main loop, never to return
    glutMainLoop();

    // yeah I know, but it keeps compilers from bitching
    return 0;
}

/******************************************************************************
 * Function: glInit
 * Paramters: none
 * Returns: none
 * Description: Initializes all three windows and sets the display mode for
 *  glut.
 *****************************************************************************/
void glInit()
{
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );
    initInitiator();
    initGenerator();
    initFractalDisplay();
}
