/*
 ***** rubberband.cpp *****

 Example of rubberbanding a rectangle in OpenGL.
 This version uses double buffering.

 CSC433/533 Computer Graphics - Fall 2014
Author: John M. Weiss, Ph.D.

Modifications:
*/

/******************************************************************************/

// include files
#include <cstdlib>
#include <iostream>
#include <queue>
#include <math.h>
using namespace std;

// use OpenGL graphics and the GLUT graphical user interface
#include <GL/freeglut.h>

// constants
const int EscapeKey = 27;

const int MouseButtonPress	= 0;
const int MouseButtonRelease	= 1;
const int MouseLeftButton	= 0;
const int MouseMiddleButton	= 1;
const int MouseRightButton	= 2;
#define TOTAL_WIDTH 800
#define TOTAL_HEIGHT 800
#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 750

/*
 *GENERATOR GLOBALS
 */
void DrawBounds();
void DrawMenu();
void DrawCircleVertices();
void DrawLine( );
const int number_of_vertices = 10;
const short int RADIUS = 5;


struct point
{
    point(float x1, float y1): x(x1), y(y1) {};
    float x;
    float y;
};

vector<point> line_vertices;

// colors
const float Black[]     = { 0.0, 0.0, 0.0 };
const float Red[]       = { 1.0, 0.0, 0.0 };
const float Green[]     = { 0.0, 1.0, 0.0 };
const float Blue[]      = { 0.0, 0.0, 1.0 };
const float Magenta[]   = { 1.0, 0.0, 1.0 }; 
const float Cyan[]      = { 0.0, 1.0, 1.0 };
const float Yellow[]    = { 1.0, 1.0, 0.0 };
const float White[]     = { 1.0, 1.0, 1.0 };

const float ViewplaneSize = 1600.0;
short int move_vertex = -1;
bool reset_line = true;

/******************************************************************************/

// global vars
int ScreenWidth  = 350;
int ScreenHeight = 350;

float startx, starty, endx, endy, lastbutton;

// function prototypes
void DrawRectangle( int x1, int y1, int x2, int y2, const float color[] );

// OpenGL callbacks
void display( void );
void reshape( int w, int h );
void keyboard( unsigned char key, int x, int y );
void mouseclick( int button, int state, int x, int y );
void mousedrag( int x, int y );
void mousemotion( int x, int y );

/******************************************************************************/

// main() function
int main( int argc, char *argv[] )
{
    // initialize OpenGL and GLUT
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA );
    glutInitWindowSize( ScreenWidth, ScreenHeight );
    glutInitWindowPosition( 100, 100 );
    glutCreateWindow( "Generator" );

    glClearColor( 0.0, 0.0, 0.0, 0.0 );

    glutDisplayFunc( display );
    glutReshapeFunc( reshape );
    glutKeyboardFunc( keyboard );
    glutMouseFunc( mouseclick );
    glutMotionFunc( mousedrag );
    // glutPassiveMotionFunc( mousemotion );    // track mouse movements (not used)


    for( int i = 0; i < number_of_vertices; i++)
        line_vertices.push_back(point( i * 40 + 50,WINDOW_HEIGHT/2 ) );



    // go into OpenGL/GLUT main loop, never to return
    glutMainLoop(  );

    return 0;
}


/******************************************************************************/
/*                          OpenGL callback functions                         */
/******************************************************************************/

// callback function that tells OpenGL how to redraw window
void display( void )
{
    // clear the display
    glClear( GL_COLOR_BUFFER_BIT );

    //MY GENERATOR DISPLAYS
    DrawLine( );
    DrawCircleVertices();    
    DrawBounds();
    DrawMenu();
    glFlush();
    glutSwapBuffers();
}

// callback function that tells OpenGL how to resize window
void reshape( int w, int h )
{

    ScreenWidth = w;
    ScreenHeight = h;

    // how to project 3-D scene onto 2-D
    glMatrixMode( GL_PROJECTION );      // use an orthographic projection
    glLoadIdentity();                   // initialize transformation matrix
    //float extra_x;
    //float extra_y;
    if ( w > h )                        // use width:height aspect ratio to specify view extents
    {   
        //extra_x = w-h;
        //extra_y = 0;
        gluOrtho2D( 0, TOTAL_WIDTH*w/h, 0, TOTAL_HEIGHT );
    }   
    else
    {   
        //extra_x = 0;
        //extra_y = h-w;
        gluOrtho2D( 0, TOTAL_WIDTH, 0, TOTAL_HEIGHT * h / w );
    }   
    glViewport( 0, 0, w, h );           // adjust viewport to new window


 /*   // store new window dimensions globally
    ScreenWidth = w;
    ScreenHeight = h;

    // how to project 3-D scene onto 2-D
    glMatrixMode( GL_PROJECTION );      // use an orthographic projection
    glLoadIdentity();                   // initialize transformation matrix
    gluOrtho2D( 0, WINDOW_HEIGHT, 0, WINDOW_WIDTH );
    glViewport( 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT );           // adjust viewport to new window
*/

}

// callback function that tells OpenGL how to handle keystrokes
void keyboard( unsigned char key, int x, int y )
{
    switch ( key )
    {
        case EscapeKey:
            exit( 0 );
            break;
    }
}

// callback function for mouse button click events
void mouseclick( int button, int state, int x, int y )
{
    // correct for upside-down screen coordinates
    y = ScreenHeight - y;
    lastbutton = button;

    switch ( button )
    {
        case MouseLeftButton:				// left button: create objects

            move_vertex = -1;

            if ( state == MouseButtonPress )		// press - new start point
            {

                if(ScreenWidth > ScreenHeight)
                {
                    startx = (float) x /ScreenHeight *TOTAL_WIDTH;
                    starty = (float) y /ScreenHeight *TOTAL_HEIGHT;
                }
                else if(ScreenWidth < ScreenHeight)
                {
                    startx = (float) x/ScreenWidth * TOTAL_WIDTH;//* ScreenWidth / TOTAL_WIDTH;				// store start coordinates
                    starty = (float) y/ ScreenWidth * TOTAL_HEIGHT;
                }
                else
                {
                    startx = (float ) x / ScreenWidth * TOTAL_WIDTH;
                    starty = (float ) y / ScreenHeight * TOTAL_HEIGHT;
                }
                cout << "STARTY: " << starty << endl;
                cout << "STARTX: " << startx << endl;
                for( int i = 1; i < number_of_vertices-1 && move_vertex == -1; i++ )
                {
                    float distance = ( line_vertices[i].x - startx ) * ( line_vertices[i].x - startx ) + 
                        ( line_vertices[i].y - starty ) * ( line_vertices[i].y - starty );
                    cout << line_vertices[i].x << " " << line_vertices[i].y << endl;
                    distance = sqrt(distance);
                    cout << "DISTANCE TO " << i << " IS " << distance << endl;   
                    if( distance <= RADIUS )
                    {
                        move_vertex = i;
                    }
                }
            }
            break;

        case MouseMiddleButton:				// middle button: not used
            break;

        case MouseRightButton:				// right button: not used
            break;
    }
}

// callback function for mouse dragging events
void mousedrag( int x, int y )
{
    float startx;
    float starty;
    y = ScreenHeight - y;
    if( lastbutton == MouseLeftButton && move_vertex != -1 )
    {
        if(ScreenWidth > ScreenHeight)
        {
            startx = (float) x / ScreenHeight * TOTAL_WIDTH;
            starty = (float) y /ScreenHeight *TOTAL_HEIGHT;
        }
        else if(ScreenWidth < ScreenHeight)
        {
            startx = (float) x/ScreenWidth * TOTAL_WIDTH;//* ScreenWidth / TOTAL_WIDTH;				// store start coordinates
            starty = (float) y/ ScreenWidth * TOTAL_HEIGHT;
        }
        else
        {
            startx = (float ) x / ScreenWidth * TOTAL_WIDTH;
            starty = (float ) y / ScreenHeight * TOTAL_HEIGHT;
        }
        line_vertices[move_vertex].x = startx;
        line_vertices[move_vertex].y = starty;


        if( startx <= line_vertices[move_vertex - 1].x )
            line_vertices[move_vertex].x = line_vertices[ move_vertex - 1 ].x;
        
        if( startx >= line_vertices[ move_vertex + 1 ].x )
            line_vertices[move_vertex].x = line_vertices[ move_vertex + 1 ].x;
        
        if( starty >= WINDOW_HEIGHT)
            line_vertices[move_vertex].y = WINDOW_HEIGHT - RADIUS;

        if( starty <= RADIUS )
            line_vertices[move_vertex].y = RADIUS;

    }

        glutPostRedisplay();
}

// callback function for mouse motion events (not used)
void mousemotion( int x, int y )
{

}

void DrawLine( )
{
    glColor3fv( Cyan );
    glScalef( 1.0,1.0,1.0);
    glBegin( GL_LINE_STRIP );
    for( unsigned int i = 0; i < line_vertices.size(); i++ )
        glVertex2f( line_vertices[i].x, line_vertices[i].y );
    glEnd();
}

void DrawCircleVertices()
{
    for( unsigned int i = 0; i < line_vertices.size(); i++ )
    {
        glColor3fv( Cyan );
        glMatrixMode( GL_MODELVIEW );
        glLoadIdentity();
        glTranslatef( line_vertices[i].x, line_vertices[i].y, 0 );
        glScalef( 1.0, 1.0, 1.0 );    // by ratio of major to minor axes
        GLUquadricObj *disk = gluNewQuadric();
        gluDisk( disk, 0, RADIUS,500, 1 );
        gluDeleteQuadric( disk );
        glLoadIdentity();
    }
}

void DrawMenu()
{
    glColor3fv( White );
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef( 20, 760, 0 );
    // while ( *string ) glutStrokeCharacter( GLUT_STROKE_ROMAN, *string++ );
    glScalef( .2,.2,1);
    glutStrokeString( GLUT_STROKE_ROMAN, (const unsigned char*)"Click and Drag Points to Modify Generator" );
    glPopMatrix(); 

    glPushMatrix();
    glTranslatef( WINDOW_WIDTH + 10, WINDOW_HEIGHT-20, 0 );
    // while ( *string ) glutStrokeCharacter( GLUT_STROKE_ROMAN, *string++ );
    glScalef( .2,.2,1);
    glutStrokeString( GLUT_STROKE_ROMAN, (const unsigned char*)"Number of Vertices" );
    glPopMatrix(); 



}

void DrawBounds()
{
    glColor3fv( White );
    glBegin( GL_LINE_STRIP );
        glVertex2f( RADIUS,RADIUS );
        glVertex2f( RADIUS,WINDOW_HEIGHT);
        glVertex2f( WINDOW_WIDTH,WINDOW_HEIGHT);
        glVertex2f( WINDOW_WIDTH,RADIUS );
    glEnd();
}
