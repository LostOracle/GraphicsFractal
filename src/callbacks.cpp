#include "../include/callbacks.h"

static int Initiator_ScreenWidth =  500;
static int Initiator_ScreenHeight = 500;

static int Generator_ScreenWidth = 500;
static int Generator_ScreenHeight =  500;

static int Fractal_ScreenWidth = 500;
static int Fractal_ScreenHeight = 500;

 /************************************
 *
 * Initiator WINDOW CALLBACK FUNCTIONS
 *
 ************************************/
void initiator_display(void)
{
    glClear( GL_COLOR_BUFFER_BIT );
    glFlush();
}

void initiator_reshape( int w, int h )
{
    ScreenWidth = w;
    ScreenHeight = h;
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluOrtho2D( 0.0, w, 0.0, h );
    glViewport( 0, 0, w, h );
}

void initiator_mouseclick( int button, int state, int x, int y )
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
void initiator_mousedrag( int x, int y )
{


}


 /************************************
 *
 * GENERATOR WINDOW CALLBACK FUNCTIONS
 *
 ************************************/

void generator_display(void)
{
    glClear( GL_COLOR_BUFFER_BIT );
    glFlush();
}

void generator_reshape( int w, int h )
{
    ScreenWidth = w;
    ScreenHeight = h;
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluOrtho2D( 0.0, w, 0.0, h );
    glViewport( 0, 0, w, h );
}

void generator_mouseclick( int button, int state, int x, int y )
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
void generator_mousedrag( int x, int y )
{


}



 /************************************
 *
 * Fractal WINDOW CALLBACK FUNCTIONS
 *
 ************************************/


void fractal_display(void)
{
    glClear( GL_COLOR_BUFFER_BIT );
    glFlush();
}

void fractal_reshape( int w, int h )
{
    ScreenWidth = w;
    ScreenHeight = h;
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluOrtho2D( 0.0, w, 0.0, h );
    glViewport( 0, 0, w, h );
}

 /************************************
 *
 * MENU WINDOW CALLBACK FUNCTIONS
 *
 ************************************/

void menu_display(void)
{
    glClear( GL_COLOR_BUFFER_BIT );
    glFlush();
}

void menu_reshape( int w, int h )
{
    Menu_ScreenWidth = w;
    Menu_ScreenHeight = h;
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluOrtho2D( 0.0, w, 0.0, h);
    glViewport( 0, 0, w, h );
}


void menu_mouseclick( int button, int state, int x, int y )
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

/*
 *INITIALIZES WINDOWS AND CALLBACKS
 */
void initOpenGL( void )
{
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE ); // 32-bit graphics and single buffering

    //Creates Initiator Window and Registers CallBacks
    glutInitWindowSize( ScreenWidth, ScreenHeight );    // initial window size
    glutInitWindowPosition( 50, 50 );          // initial window position
    glutCreateWindow( "Initiator Shape" );          // window title

    glClearColor( 0.0, 0.0, 0.0, 1.0 );         // use black for glClear command

    // callback routines
    glutDisplayFunc( initiator_display );             // how to redisplay window
    glutReshapeFunc( initiator_reshape );             // how to resize window
    glutMouseFunc( initiator_mouseclick );
    glutMotionFunc( initiator_mousedrag);

    //Creates Generator Window and Registers CallBacks
     glutInitWindowSize( ScreenWidth, ScreenHeight );    // initial window size
    glutInitWindowPosition( 50, 50 );          // initial window position
    glutCreateWindow( "Generator" );          // window title

    glClearColor( 0.0, 0.0, 0.0, 1.0 );         // use black for glClear command

    // callback routines
    glutDisplayFunc( Generator_display );             // how to redisplay window
    glutReshapeFunc( Generator_reshape );             // how to resize window
    glutMouseFunc( Generator_mouseclick );
    glutMotionFunc( Generator_mousedrag);

   
    //Creates Fractal Window and Registers CallBacks
      glutInitWindowSize( ScreenWidth, ScreenHeight );    // initial window size
    glutInitWindowPosition( 50, 50 );          // initial window position
    glutCreateWindow( "Fractal Generated" );          // window title

    glClearColor( 0.0, 0.0, 0.0, 1.0 );         // use black for glClear command

    // callback routines
    glutDisplayFunc( fractal_display );             // how to redisplay window
    glutReshapeFunc( fractal_reshape );             // how to resize window

    //Creates Menu Window and Registers CallBacks
    glutInitWindowSize( ScreenWidth, ScreenHeight );    // initial window size
    glutInitWindowPosition( 50, 50 );          // initial window position
    glutCreateWindow( "Menu" );          // window title

    glClearColor( 0.0, 0.0, 0.0, 1.0 );         // use black for glClear command

    // callback routines
    glutDisplayFunc( Menu_display );             // how to redisplay window
    glutReshapeFunc( Menu_reshape );             // how to resize window
    glutMouseFunc( Menu_mouseclick );

}

