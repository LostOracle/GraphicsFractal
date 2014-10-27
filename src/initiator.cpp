// include files
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <math.h>
using namespace std;

// use OpenGL graphics and the GLUT graphical user interface
#include <GL/freeglut.h>
#include "../include/shared_constants.h"
#include "../include/common_functions.h"
#include "../include/initiator_init.h"

//all the static functions and variables are declared here to restrict scope to this file

static int ScreenWidth = 0.5*(TOTAL_WIDTH);
static int ScreenHeight = 0.5*(TOTAL_HEIGHT);

static void display( void );
static void click( int button, int state, int x, int y);
static void drag( int x, int y );
static void reshape( int w, int h );
static void draw_initiator();
static void init_default_fractal();
static void draw_initiator();
static void screen_to_gl(float & x, float & y);
static void release_point();
static void pickup_point(float x, float y);
static void move_point(float x, float y);
static void reset();
static void increment_vertices();
static void decrement_vertices();
static void new_initiator();

vector<point> initiator_points;
static int acquired_point = -1;
static int num_vertices = 4;

void initInitiator( void )
{
    glutInitWindowSize( ScreenWidth, ScreenHeight );    // initial window size
    glutInitWindowPosition( 0, 0 );          // initial window position
    glutCreateWindow( "Initiator" );          // window title

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
    num_vertices = 4;
    initiator_points.clear();
    point p(250,335);
    initiator_points.push_back(p);
    p.x = 250 + (175*(-sin(120*M_PI/180.0)));
    p.y = 235 + (175*(cos(120*M_PI/180.0)));
    initiator_points.push_back(p);
    p.x = 250 + (175*(-sin(-120*M_PI/180.0)));
    p.y = 235 + (175*(cos(-120*M_PI/180.0)));
    initiator_points.push_back(p);
    p.x = 250;
    p.y = 335;
    initiator_points.push_back(p);
}

static void draw_text()
{
    char temp_str[10];
    glColor3f(0,0,0);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(RIGHT_MENU_CENTER_X - VERTICES_HORIZONTAL_OFFSET ,RIGHT_MENU_CENTER_Y + VERTICES_VERTICAL_OFFSET,0);
    glScalef(0.15,0.15,1);
    glutStrokeString(GLUT_STROKE_ROMAN, (const unsigned char *)"Vertices");
    glPopMatrix();
 
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(RIGHT_MENU_CENTER_X - VERTICE_NUM_HORIZONTAL_OFFSET, RIGHT_MENU_CENTER_Y - VERTICE_NUM_VERTICAL_OFFSET,0);
    glScalef(0.15,0.15,1);
    sprintf(temp_str,"%02d",num_vertices);
    glutStrokeString(GLUT_STROKE_ROMAN, (const unsigned char *)temp_str);
    glPopMatrix();
}

static void display( void )
{
    glClear( GL_COLOR_BUFFER_BIT );
    draw_menu_backgrounds();
    draw_up_down_arrows();
    draw_reset_button();
    draw_text_area();
    draw_text();
    draw_border();
    draw_initiator();
    glFlush();
    glutSwapBuffers();
}

static void draw_initiator()
{
    glColor3f(1,1,1);
    glBegin(GL_LINE_STRIP);
    for(unsigned int i = 0; i < initiator_points.size(); i++)
        glVertex2f(initiator_points[i].x,initiator_points[i].y);
    glEnd();
    for(unsigned int i = 0; i < initiator_points.size(); i++)
        draw_big_point(initiator_points[i].x,initiator_points[i].y);
}


static void reshape( int w, int h )
{
    // store new window dimensions globally
    ScreenWidth = w;
    ScreenHeight = h;


    // how to project 3-D scene onto 2-D
    glMatrixMode( GL_PROJECTION );      // use an orthographic projection
    glLoadIdentity();                   // initialize transformation matrix
    if ( w > (h*ASPECT_RATIO) )                        // use width:height aspect ratio to specify view extents
        gluOrtho2D( 0, TOTAL_WIDTH * w / (h*ASPECT_RATIO), 0 , TOTAL_HEIGHT );
    else
        gluOrtho2D( 0, TOTAL_WIDTH, 0, TOTAL_HEIGHT * (h*ASPECT_RATIO)/w );
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
            if(reset_pressed(float_x,float_y))
            {
                reset();
            }
            else if(up_pressed(float_x,float_y))
            {
                increment_vertices();
            }
            else if(down_pressed(float_x,float_y))
            {
                decrement_vertices();
            }
            else
                pickup_point(float_x,float_y);
        }
        else if(state == MouseButtonRelease)
        {
            //release point
            release_point();
        }
    }
}

static void increment_vertices()
{
    if(num_vertices >= 10)
        return;
    num_vertices++;
    new_initiator(); 
    glutPostRedisplay();
}

static void decrement_vertices()
{
    if(num_vertices <= 2)
        return;
    num_vertices--;
    new_initiator();
    glutPostRedisplay();
}

static void new_initiator()
{
    point p(0,DRAW_WINDOW_HEIGHT/2.0);
    float delta = (DRAW_WINDOW_WIDTH - 2*BORDER_BUFFER)/(num_vertices-1);
    initiator_points.clear();
    for(float x = BORDER_BUFFER; x <= DRAW_WINDOW_WIDTH - BORDER_BUFFER; x += delta)
    {
        p.x = x;
        initiator_points.push_back(p);
    }
}

static void reset()
{
    init_default_fractal();
    glutPostRedisplay();
}

static void pickup_point(float x, float y)
{
    float min_d = -1;
    int min_index = -1;
    for(unsigned int i = 0; i < initiator_points.size(); i++)
    {   
        float dx2 = (initiator_points[i].x - x)*(initiator_points[i].x - x);
        float dy2 = (initiator_points[i].y - y)*(initiator_points[i].y - y);
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
}

static void move_point(float x, float y)
{
    if(x < BORDER_BUFFER)
        x = BORDER_BUFFER;
    else if(x > DRAW_WINDOW_WIDTH - BORDER_BUFFER)
        x = DRAW_WINDOW_WIDTH - BORDER_BUFFER;
    
    if(y < BORDER_BUFFER)
        y = BORDER_BUFFER;
    else if(y > DRAW_WINDOW_HEIGHT - BORDER_BUFFER)
        y = DRAW_WINDOW_HEIGHT - BORDER_BUFFER;
    
    initiator_points[acquired_point].x = x;
    initiator_points[acquired_point].y = y;
    glutPostRedisplay();
}

static void screen_to_gl(float & x, float & y)
{
    if(ScreenWidth == ScreenHeight*ASPECT_RATIO)
    {
        x = (float)x / ScreenWidth * TOTAL_WIDTH;
        y = (float)y / ScreenHeight * TOTAL_HEIGHT;
    }
    else if(ScreenWidth > ScreenHeight*ASPECT_RATIO)
    {
        x = (float)x / (ScreenHeight*ASPECT_RATIO) * TOTAL_WIDTH;
        y = (float)y / ScreenHeight * TOTAL_HEIGHT;
    }
    else
    {   
        x = (float)x / ScreenWidth * TOTAL_WIDTH;
        y = (float)y / (ScreenWidth/ASPECT_RATIO) * TOTAL_HEIGHT;
    }
}
