#include "../include/shared_constants.h"
#include "../include/common_functions.h"
#include "../include/fractal_init.h"
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <math.h>
using namespace std;
#include<GL/freeglut.h>

//all the static functions and variables are declared here to restrict scope to this file

static int ScreenWidth = TOTAL_WIDTH;
static int ScreenHeight = TOTAL_HEIGHT + TITLE_BAR_VERTICAL_SIZE;

static void display( void );
static void click( int button, int state, int x, int y);
static void reshape( int w, int h );
static void draw_fractal_display();
static void draw_all_fractals();
static void screen_to_gl(float & x, float & y);
static void increment_iterations();
static void decrement_iterations();
static void recalculate_fractal();
static void draw_text();
extern vector<point> initiator_points;
extern vector<point> generator_points;

vector< vector<point> > fractal_iterations;
static int number_of_iterations = 1;
static bool draw_previous = false;
void initFractalDisplay( void )
{
    glutInitWindowSize( ScreenWidth, ScreenHeight );    // initial window size
    glutInitWindowPosition( ScreenWidth/2, 0 );          // initial window position
    glutCreateWindow( "Fractal Display" );          // window title
    
    glClearColor( 0.0, 0.0, 0.0, 1.0 );         // use black for glClear command
    fractal_iterations.push_back( initiator_points );

    // callback routines
    glutDisplayFunc( display );             // how to redisplay window
    glutReshapeFunc( reshape );             // how to resize window
    glutMouseFunc( click );
    recalculate_fractal();
    //set up default fractal initiator
}

static void display( void )
{
    glClear( GL_COLOR_BUFFER_BIT );
    draw_menu_backgrounds();
    draw_up_down_arrows();
    draw_go_button();
    draw_text_area();
    draw_text();
    draw_border();
    if( !draw_previous )
        draw_fractal_display();
    else
        draw_all_fractals();
    glFlush();
    glutSwapBuffers();
}

static void draw_fractal_display()
{
    glColor3f(1,1,1);
    glBegin(GL_LINE_STRIP);
    for( unsigned int i = 0; i < fractal_iterations[number_of_iterations -1].size(); i++)
    {
        glVertex2f( fractal_iterations[number_of_iterations - 1][i].x, fractal_iterations[number_of_iterations - 1][i].y );
    }
    glEnd();
}

static void draw_all_fractals()
{
    glColor3f(1,1,1);
    glBegin(GL_LINE_STRIP);
    for( int i = 0; i < number_of_iterations; i++)
    {
        for( unsigned int j = 0; j < fractal_iterations[i].size(); j++ )
            glVertex2f( fractal_iterations[i][j].x, fractal_iterations[i][j].y );
    }
    glEnd();
}


static void reshape( int w, int h )
{
    // store new window dimensions globally
    ScreenWidth = w;
    ScreenHeight = h;

    // how to project 3-D scene onto 2-D
    glMatrixMode( GL_PROJECTION );      // use an orthographic projection
    glLoadIdentity();                   // initialize transformation matrix
    if ( w > ( h * ASPECT_RATIO ) )                        // use width:height aspect ratio to specify view extents
        gluOrtho2D( 0, TOTAL_WIDTH * w / ( h * ASPECT_RATIO ), 0 , TOTAL_HEIGHT );
    else
        gluOrtho2D( 0, TOTAL_WIDTH, 0, TOTAL_HEIGHT * ( h * ASPECT_RATIO )/ w );
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
            if(up_pressed(float_x,float_y))
            {
                increment_iterations();
            }
            else if(down_pressed(float_x,float_y))
            {
                decrement_iterations();
            }
            else if( go_pressed(float_x, float_y) )
            {    
                fractal_iterations.clear();
                fractal_iterations.push_back( initiator_points );
                recalculate_fractal();
            }
        }
    }

}

static void draw_text()
{
    char temp_str[10];
    glColor3f(0,0,0);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(RIGHT_MENU_CENTER_X - ITERATION_HORIZONTAL_OFFSET ,RIGHT_MENU_CENTER_Y + ITERATION_VERTICAL_OFFSET,0);
    glScalef(0.15,0.15,1);
    glutStrokeString(GLUT_STROKE_ROMAN, (const unsigned char *)"Iterations");
    glPopMatrix();
 
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(RIGHT_MENU_CENTER_X - ITERATION_NUM_HORIZONTAL_OFFSET, RIGHT_MENU_CENTER_Y - ITERATION_NUM_VERTICAL_OFFSET,0);
    glScalef(0.15,0.15,1);
    sprintf(temp_str, "%02d" ,number_of_iterations - 1);
    glutStrokeString(GLUT_STROKE_ROMAN, (const unsigned char *)temp_str);
    glPopMatrix();
}


static void increment_iterations()
{
    if(number_of_iterations >= 7 )
        return;
    number_of_iterations++;
    if( fractal_iterations.size() < number_of_iterations)
        recalculate_fractal();
    glutPostRedisplay();
}

static void decrement_iterations()
{
    if(number_of_iterations == 1)
        return;
    number_of_iterations--;
    glutPostRedisplay();
}

void recalculate_fractal( void )
{
    for( int i = fractal_iterations.size(); i < number_of_iterations; i++ )
    {
        vector<point> temp_iteration;
        for( unsigned int j = 0; j < (fractal_iterations[i-1].size()-1); j++)
        {
            point end_point(fractal_iterations[i-1][j+1]);
            point start_point(fractal_iterations[i-1][j]);
            vector<point> tmp = generator_points;

            point first_point(tmp[0].x, tmp[0].y);
            for(unsigned int k = 0; k < tmp.size(); k++ )
            {
                tmp[k].x = tmp[k].x - first_point.x;
                tmp[k].y = tmp[k].y - first_point.y;
            }

            float theta = atan2(end_point.y - start_point.y, end_point.x - start_point.x);

            float tmp_distance = tmp[tmp.size()-1].x*tmp[tmp.size()-1].x + tmp[tmp.size()-1].y*tmp[tmp.size()-1].y;

            tmp_distance = sqrt(tmp_distance);

            float scale =(start_point.x - end_point.x ) * (start_point.x - end_point.x);
            scale += (start_point.y - end_point.y ) * (start_point.y - end_point.y);
            scale = sqrt(scale)/tmp_distance;

            for( int l = 0; l < tmp.size()-1; l++)
            {
                point p(0,0);
                p.x = (tmp[l].x * cos(theta) - tmp[l].y * sin(theta) ) * scale + start_point.x;
                p.y = (tmp[l].x * sin(theta) + tmp[l].y * cos(theta) ) * scale + start_point.y;
                temp_iteration.push_back(p);
            }
        }
        temp_iteration.push_back(fractal_iterations[i-1][ fractal_iterations[i-1].size()-1 ]);
        fractal_iterations.push_back(temp_iteration);
        temp_iteration.clear();
    }
    glutPostRedisplay();
}

static void screen_to_gl(float & x, float & y)
{
    if(ScreenWidth == ScreenHeight * ASPECT_RATIO )
    {
        x = (float)x / ScreenWidth * TOTAL_WIDTH;
        y = (float)y / ScreenHeight * TOTAL_HEIGHT;
    }
    else if(ScreenWidth > ScreenHeight * ASPECT_RATIO)
    {
        x = (float)x / ScreenHeight * TOTAL_WIDTH;
        y = (float)y / ScreenHeight * ASPECT_RATIO * TOTAL_HEIGHT;
    }
    else
    {
        x = (float)x / ScreenWidth * TOTAL_WIDTH;
        y = (float)y / ( ScreenWidth / ASPECT_RATIO ) * TOTAL_HEIGHT;
    }
}
