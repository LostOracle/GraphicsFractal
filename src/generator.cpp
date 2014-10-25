// include files
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <math.h>
using namespace std;

// use OpenGL graphics and the GLUT graphical user interface
#include <GL/freeglut.h>
#include "shared_constants.h"
#include "common_functions.h"
#include "generator.h"

//all the static functions and variables are declared here to restrict scope to this file

static int ScreenWidth = 0.5*(TOTAL_WIDTH);
static int ScreenHeight = 0.5*(TOTAL_HEIGHT);

static void display( void );
static void click( int button, int state, int x, int y);
static void drag( int x, int y );
static void reshape( int w, int h );
static void init_default_fractal();
static void draw_generator();
static void screen_to_gl(float & x, float & y);
static void release_point();
static void pickup_point(float x, float y);
static void move_point(float x, float y);

vector<point> generator_points;
static int acquired_point = -1;


void initGenerator( void )
{
    glutCreateWindow( "Generator" );          // window title
    glutInitWindowSize( ScreenWidth, ScreenHeight );    // initial window size
    glutInitWindowPosition( ScreenWidth, 0 );          // initial window position

    glClearColor( 0.0, 0.0, 0.0, 1.0 );         // use black for glClear command

    // callback routines
    glutDisplayFunc( display );             // how to redisplay window
    glutReshapeFunc( reshape );             // how to resize window
    glutMouseFunc( click );
    glutMotionFunc( drag );

    //set up default fractal initiator
    init_default_fractal();
}

static void init_default_fractal()
{
    //center at 250,250, equilateral triangle

    point p(BORDER_BUFFER,DRAW_WINDOW_HEIGHT/2.0);
    generator_points.push_back(p);
    p.x = BORDER_BUFFER + 1/3.0*(DRAW_WINDOW_WIDTH - 2*BORDER_BUFFER);
    generator_points.push_back(p);
    
    p.x = 0.5*DRAW_WINDOW_WIDTH;
    p.y = DRAW_WINDOW_HEIGHT/2.0 + 1/3.0*(DRAW_WINDOW_WIDTH - 2*BORDER_BUFFER)*sin(60*M_PI/180);
    generator_points.push_back(p);
    
    p.x = BORDER_BUFFER + 2/3.0*(DRAW_WINDOW_WIDTH - 2*BORDER_BUFFER);
    p.y = DRAW_WINDOW_HEIGHT/2.0;
    generator_points.push_back(p);

    p.x = DRAW_WINDOW_WIDTH - BORDER_BUFFER;
    generator_points.push_back(p);
}

static void display( void )
{
    glClear( GL_COLOR_BUFFER_BIT );
    draw_menu();
    draw_border();
    draw_generator();
    glFlush();
    glutSwapBuffers();
}

static void draw_generator()
{
    glColor3f(1,1,1);
    glBegin(GL_LINE_STRIP);
    for(unsigned int i = 0; i < generator_points.size(); i++)
        glVertex2f(generator_points[i].x,generator_points[i].y);
    glEnd();
    for(unsigned int i = 0; i < generator_points.size(); i++)
        draw_big_point(generator_points[i].x,generator_points[i].y);
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
            //pickup point
            pickup_point(float_x,float_y);
        }
        else if(state == MouseButtonRelease)
        {
            //release point
            release_point();
        }
    }
}

static void pickup_point(float x, float y)
{
    float min_d = -1;
    int min_index = -1;
    for(unsigned int i = 1; i < generator_points.size()-1; i++)
    {   
        float dx2 = (generator_points[i].x - x)*(generator_points[i].x - x);
        float dy2 = (generator_points[i].y - y)*(generator_points[i].y - y);
        float d = sqrt(dx2 + dy2);
        if(min_index == -1 || d < min_d)
        {
            min_index = i;
            min_d = d;
        }
    }
    if(min_d < 10)
        acquired_point = min_index;
}

static void release_point()
{
    acquired_point = -1;
}

// callback function for mouse dragging events
static void drag( int x, int y )
{
    float float_x = x;
    float float_y = ScreenHeight - y;
    screen_to_gl(float_x,float_y);
    if(acquired_point != -1)
        move_point(float_x, float_y);
    //convert screen coordinates into GL coordinates
    printf("Mouse dragged to (%f,%f)\n",float_x,float_y);
}

static void move_point(float x, float y)
{
    if(x < BORDER_BUFFER)
        x = BORDER_BUFFER;
    else if(x > DRAW_WINDOW_WIDTH - BORDER_BUFFER)
        x = DRAW_WINDOW_WIDTH - BORDER_BUFFER;
    
    if(y < BORDER_BUFFER)
        y = BORDER_BUFFER;
    else if(y > TOTAL_HEIGHT - BORDER_BUFFER)
        y = TOTAL_HEIGHT - BORDER_BUFFER;
    
    generator_points[acquired_point].x = x;
    generator_points[acquired_point].y = y;
    glutPostRedisplay();
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
