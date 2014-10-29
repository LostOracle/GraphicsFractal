/******************************************************************************
 * File: main.cpp
 * Authors: Ian Carlson, Christopher Smith
 * Description: Entry point for the fractal program. Kicks off all three
 *  windows - initiator, generator, and display
 *****************************************************************************/

#include "../include/main.h"

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
