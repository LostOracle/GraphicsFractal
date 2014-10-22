#include "../include/callbacks.h"

static int ScreenWidth =  500;
static int ScreenHeight = 500;

void display(void)
{
    glClear( GL_COLOR_BUFFER_BIT );
    glFlush();
}

void reshape( int w, int h )
{
    ScreenWidth = w;
    ScreenHeight = h;
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluOrtho2D( 0.0, w, 0.0, h );
    glViewport( 0, 0, w, h );
}

void mouseclick( int button, int state, int x, int y )
{
    switch ( button )
    {
        case MouseLeftButton:               // left button: create objects
            if ( state == MouseButtonPress )        // press - new start point
            {

            }

            else if ( state == MouseButtonRelease ) // release - new endpoint
            {
            }

            break;

        case MouseMiddleButton:             // middle button: not used
            break;

        case MouseRightButton:              // right button: not used
            break;
    }
}

// callback function for mouse dragging events
void mousedrag( int x, int y )
{


}
void initOpenGL( void )
{
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE ); // 32-bit graphics and single buffering

    glutInitWindowSize( ScreenWidth, ScreenHeight );    // initial window size
    glutInitWindowPosition( 50, 50 );          // initial window position
    glutCreateWindow( "Fractal Generator" );          // window title

    glClearColor( 0.0, 0.0, 0.0, 1.0 );         // use black for glClear command

    // callback routines
    glutDisplayFunc( display );             // how to redisplay window
    glutReshapeFunc( reshape );             // how to resize window
    glutMouseFunc( mouseclick );
    glutMotionFunc( mousedrag);
}

