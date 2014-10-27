#include <GL/freeglut.h>
#include <vector>
#include "../include/shared_constants.h"
#include "../include/common_functions.h"
#include "../include/initiator_init.h"
#include "../include/generator_init.h"
#include "../include/fractal_init.h"
using namespace std;
void glInit();

extern vector<point> initiator_points;

int main( int argc, char *argv[] )
{
    glutInit( &argc, argv );
    glInit();

    // go into OpenGL/GLUT main loop, never to return
    glutMainLoop();

    // yeah I know, but it keeps compilers from bitching
    return 0;
}

void glInit()
{
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );
    initInitiator();
    initGenerator();
    initFractalDisplay();
}
