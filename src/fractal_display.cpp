#include "shared_constants.h"
#include "common_functions.h"
#include "fractal_display.h"

//all the static functions and variables are declared here to restrict scope to this file

static int ScreenWidth = TOTAL_WIDTH;
static int ScreenHeight = TOTAL_HEIGHT;

static void display( void );
static void click( int button, int state, int x, int y);
static void drag( int x, int y );
static void reshape( int w, int h );
static void draw_fractal_display();
static void screen_to_gl(float & x, float & y);

vector<point> fractal_points;
static int acquired_point = -1;


void initFractalDisplay( void )
{
    glutCreateWindow( "Fractal Display" );          // window title
    glutInitWindowSize( ScreenWidth, ScreenHeight );    // initial window size
    glutInitWindowPosition( 0, ScreenHeight );          // initial window position

    glClearColor( 0.0, 0.0, 0.0, 1.0 );         // use black for glClear command

    // callback routines
    glutDisplayFunc( display );             // how to redisplay window
    glutReshapeFunc( reshape );             // how to resize window
    glutMouseFunc( click );

    //set up default fractal initiator
}

static void display( void )
{
    glClear( GL_COLOR_BUFFER_BIT );
    draw_menu();
    draw_border();
    draw_fractal_display();
    glFlush();
    glutSwapBuffers();
}

static void draw_fractal_display()
{

}


static void reshape( int w, int h )
{
    // store new window dimensions globally
    ScreenWidth = w;
    ScreenHeight = h;

    // how to project 3-D scene onto 2-D
    glMatrixMode( GL_PROJECTION );      // use an orthographic projection
    glLoadIdentity();                   // initialize transformation matrix
    if ( w > h )                        // use width:height aspect ratio to specify view extents
        gluOrtho2D( 0, TOTAL_WIDTH * w / h, 0 , TOTAL_HEIGHT );
    else
        gluOrtho2D( 0, TOTAL_WIDTH, 0, TOTAL_HEIGHT * h / w );
    glViewport( 0, 0, w, h );           // adjust viewport to new window
}

// callback function for mouse button click events
static void click( int button, int state, int x, int y )
{
    float float_y = ScreenHeight - y;
    float float_x = x;
    screen_to_gl(float_x,float_y);
    if(button == MouseLeftButton)
    {
        if(state == MouseButtonPress)
        {
        }
        else if(state == MouseButtonRelease)
        {
        }
    }
}

static void screen_to_gl(float & x, float & y)
{
    if(ScreenWidth == ScreenHeight)
    {
        x = (float)x / ScreenWidth * TOTAL_WIDTH;
        y = (float)y / ScreenHeight * TOTAL_HEIGHT;
    }
    else if(ScreenWidth > ScreenHeight)
    {
        x = (float)x / ScreenHeight * TOTAL_WIDTH;
        y = (float)y / ScreenHeight * TOTAL_HEIGHT;
    }
    else
    {
        x = (float)x / ScreenWidth * TOTAL_WIDTH;
        y = (float)y / ScreenWidth * TOTAL_HEIGHT;
    }
}
