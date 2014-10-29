/******************************************************************************
 * File: generator.cpp
 * Authors: Ian Carlson, Christopher Smith
 * Description: The generator window allows the user to draw the generator
 *  pattern for generating the fractal.
 *****************************************************************************/

// include files
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <math.h>
#include <stdlib.h>
using namespace std;

// use OpenGL graphics and the GLUT graphical user interface
#include <GL/freeglut.h>
#include "../include/shared_constants.h"
#include "../include/common_functions.h"
#include "../include/generator_init.h"

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
static void draw_text();
static void release_point();
static void pickup_point(float x, float y);
static void move_point(float x, float y);
static void new_generator();
static void reset();
static void increment_vertices();
static void decrement_vertices();

//This is shared with fractal_display
vector<point> generator_points;

static int acquired_point = -1;
static int num_vertices = 5;

/******************************************************************************
 * Function: initGenerator
 * Paramters: none
 * Returns: none
 * Description: initialize the generator window and set up the default fractal
 *****************************************************************************/
void initGenerator( void )
{
    //set up the window
    glutInitWindowSize( ScreenWidth, ScreenHeight );
    glutInitWindowPosition( 0, ScreenHeight + TITLE_BAR_VERTICAL_SIZE );
    glutCreateWindow( "Generator" );

    glClearColor( 0.0, 0.0, 0.0, 1.0 );

    // callback routines
    glutDisplayFunc( display );
    glutReshapeFunc( reshape );
    glutMouseFunc( click );
    glutMotionFunc( drag );

    //set up default fractal initiator
    init_default_fractal();
}

/******************************************************************************
 * Function: init_default_fractal
 * Parameters: none
 * Returns: none
 * Description: Initializes the generator to produce the Koch Snowflake
 *****************************************************************************/
static void init_default_fractal()
{
    generator_points.clear();
    num_vertices = 5;
    
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

/******************************************************************************
 * Function: display
 * Paramters: none
 * Returns: none
 * Description: redraws the generator window
 *****************************************************************************/
static void display( void )
{
    glClear( GL_COLOR_BUFFER_BIT );
    draw_menu_backgrounds();
    draw_up_down_arrows();
    draw_reset_button();
    draw_text_area();
    draw_text();
    draw_border();
    draw_generator();
    glFlush();
    glutSwapBuffers();
}

/******************************************************************************
 * Function: draw_generator
 * Parameters: none
 * Returns: none
 * Description: Draw the generator pattern
 *****************************************************************************/
static void draw_generator()
{
    glColor3f(1,1,1);
    
    //Draw the line segments
    glBegin(GL_LINE_STRIP);
    for(unsigned int i = 0; i < generator_points.size(); i++)
        glVertex2f(generator_points[i].x,generator_points[i].y);
    glEnd();
 
    //Draw the vertices a little larger
    for(unsigned int i = 0; i < generator_points.size(); i++)
        draw_big_point(generator_points[i].x,generator_points[i].y);
}

/******************************************************************************
 * Function: new_generator
 * Paramters: none
 * Returns: none
 * Description: Resets the generator when the up or down arrow is pressed.
 *****************************************************************************/
static void new_generator()
{
    //get rid of the old generator
    generator_points.clear();
    
    //Evenly distribute the points along the center of the window
    point p(0,DRAW_WINDOW_HEIGHT/2.0);
    float delta = (DRAW_WINDOW_WIDTH - 2*BORDER_BUFFER)/(num_vertices-1);
    for(float x = BORDER_BUFFER; x <= DRAW_WINDOW_WIDTH - BORDER_BUFFER; x += delta)
    {
        p.x = x;
        generator_points.push_back(p);
    }
}

/******************************************************************************
 * Function: draw_text
 * Parameters: none
 * Returns: none
 * Description: Draw the "Vertices" text and the current number of vertices
 *****************************************************************************/
static void draw_text()
{
    char temp_str[10];
    //draw vertices text 
    glColor3f(0,0,0);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(RIGHT_MENU_CENTER_X - VERTICES_HORIZONTAL_OFFSET ,
                 RIGHT_MENU_CENTER_Y + VERTICES_VERTICAL_OFFSET,0);
    glScalef(0.15,0.15,1);
    glutStrokeString(GLUT_STROKE_ROMAN, (const unsigned char *)"Vertices");
    glPopMatrix();
    
    //show the number of vertices
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(RIGHT_MENU_CENTER_X - VERTICE_NUM_HORIZONTAL_OFFSET, 
                 RIGHT_MENU_CENTER_Y - VERTICE_NUM_VERTICAL_OFFSET,0);
    glScalef(0.15,0.15,1);
    sprintf(temp_str,"%02d",num_vertices);
    glutStrokeString(GLUT_STROKE_ROMAN, (const unsigned char *)temp_str);
    glPopMatrix();
}

/******************************************************************************
 * Function: reshape - Callback function
 * Paramters:
 *  w - new width of the screen in pixels
 *  h - new height of the screen in pixels
 * Returns: none
 * Description: Scale the window properly on user resize.
 *
 * Base on code from Dr. Weiss. Except the aspect ratio. We take credit for
 *  that part
 *****************************************************************************/
static void reshape( int w, int h )
{
    // store new window dimensions globally
    ScreenWidth = w;
    ScreenHeight = h;

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    if ( w > (h*ASPECT_RATIO) )
        gluOrtho2D( 0, TOTAL_WIDTH * w / (h*ASPECT_RATIO), 0 , TOTAL_HEIGHT );
    else
        gluOrtho2D( 0, TOTAL_WIDTH, 0, TOTAL_HEIGHT * (h*ASPECT_RATIO) / w );
    glViewport( 0, 0, w, h );
}

/******************************************************************************
 * Function: click - Callback function
 * Paramters:
 *  button - which button was clicked
 *  state - pressed or release
 *  x - x coordinate of the click in pixels
 *  y - y coordinate of the click in pixels
 * Returns: none
 * Description: Convert pixel coordinates to gl coordinates and check for
 *  button presses and allow dragging of points.
 *****************************************************************************/
static void click( int button, int state, int x, int y )
{
    //flip the y coordinate to up is +
    float float_y = ScreenHeight - y;
    float float_x = x;
    
    //convert to gl coordinates
    screen_to_gl(float_x,float_y);

    //handle left clicks
    if(button == MouseLeftButton)
    {
        if(state == MouseButtonPress)
        {
            if(reset_pressed(float_x,float_y))
                reset();
            else if(up_pressed(float_x,float_y))
                increment_vertices();
            else if(down_pressed(float_x,float_y))
                decrement_vertices();
            else
                pickup_point(float_x,float_y);
        }

        //let go of the dragged point
        else if(state == MouseButtonRelease)
            release_point();
    }
}

/******************************************************************************
 * Function: reset
 * Paramters: none
 * Returns: none
 * Description: Reset the generator to its default state.
 *****************************************************************************/
static void reset()
{
    init_default_fractal();
    glutPostRedisplay();
}

/******************************************************************************
 * Function: increment_vertices
 * Paramters: none
 * Returns: none
 * Description: Increase the number of  vertices to be drawn in the generator
 *  pattern. Then reset the pattern because it would be really hard to insert
 *  a new point without disrupting the old pattern.
 *
 *  Also make sure the user doesn't pick too high of a value. This thing
 *  can really eat up ram on highly iterated fractals. We crashed the lab
 *  computers a few times before we found these limits.
 *****************************************************************************/
static void increment_vertices()
{
    if(num_vertices >= 10)
        return;
    num_vertices++;
    new_generator(); 
    glutPostRedisplay();
}

/******************************************************************************
 * Function: decrement_vertices
 * Paramters: none
 * Returns: none
 * Description: Decrease the number of vertices to be drawn in the generator
 *  pattern. Then reset the pattern because it would be really hard to delete
 *  a point without disrupting the old pattern.
 *
 *  Also make sure the user doesn't have too few points to actually make a
 *  fractal.
 *****************************************************************************/
static void decrement_vertices()
{
    if(num_vertices <= 3)
        return;
    num_vertices--;
    new_generator();
    glutPostRedisplay();
}

/******************************************************************************
 * Function: pickup_point
 * Paramters: none
 * Returns: none
 * Description: Check if the user clicked near enough to a point that they
 *  probably want to drag it, and flag that point for dragging.
 *****************************************************************************/
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

/******************************************************************************
 * Function: release_point
 * Paramters: none
 * Returns: none
 * Description: Unflag a point for dragging because the user release the button
 *****************************************************************************/
static void release_point()
{
    acquired_point = -1;
}

/******************************************************************************
 * Function: drag - Callback function
 * Paramters:
 *  x - x coordinate of the mouse drag in pixels
 *  y - y coordinate fo the mouse drag in pixels
 * Returns: none
 * Description: Update a point's location if the user is dragging it.
 *****************************************************************************/
static void drag( int x, int y )
{
    float float_x = x;
    float float_y = ScreenHeight - y;

    //convert to gl coordinates
    screen_to_gl(float_x,float_y);

    //move the point the user is dragging, if any
    if(acquired_point != -1)
        move_point(float_x, float_y);
}

/******************************************************************************
 * Function: move_point
 * Parameters:
 *  x - x coordinate we want to move the point to in gl coordinates
 *  y - y coordinate we want to move the point to in gl coordinates
 * Returns: none
 * Description: Try to move the point to the dragged location, but snap it
 *  back to the drawing area if the user tried to drag it outside.
 *****************************************************************************/
static void move_point(float x, float y)
{
    //check the x bounds
    if(x < BORDER_BUFFER)
        x = BORDER_BUFFER;
    else if( x > DRAW_WINDOW_WIDTH - BORDER_BUFFER )
        x = DRAW_WINDOW_WIDTH - BORDER_BUFFER;
    
    //check the y bounds
    if( y < BORDER_BUFFER )
        y = BORDER_BUFFER;
    else if( y > DRAW_WINDOW_HEIGHT - BORDER_BUFFER )
        y = DRAW_WINDOW_HEIGHT - BORDER_BUFFER;
    
    //update the point location
    generator_points[acquired_point].x = x;
    generator_points[acquired_point].y = y;

    //redraw
    glutPostRedisplay();
}

/******************************************************************************
 * Function: screen_to_gl
 * Paramters:
 *  x - x coordinate to convert
 *  y - y coordinate to convet
 * Returns: modified x and y
 * Description: Converts screen coordinates to gl coordinates, respecting
 *  scale and aspect ratio to make life easier for the rest of the program.
 *****************************************************************************/
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
