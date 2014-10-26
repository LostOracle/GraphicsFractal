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
static void draw_all_fractals();
static void screen_to_gl(float & x, float & y);
static void increment_iterations();
static void decrement_iterations();
static void draw_previous_toggle();
static void reset();
static void recalculate_fractal();

vector< vector<point> > fractal_iterations;
static int number_of_iterations = 1;
static bool draw_previous = false;
static float draw_toggle = { .7,0,0};
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
    fractal_iterations.pop_back( initiator_points );
    //set up default fractal initiator
}

static void display( void )
{
    glClear( GL_COLOR_BUFFER_BIT );
    draw_menu();
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
    for( int i = 0; i < fractal_iterations[number_of_iterations -1].size(); i++)
    {
        glVertex2f( fractal_iterations[number_of_iterations - 1][i].x, fractal_iterations[number_of_iterations - 1][i].y );
    }
    glEnd();
}

draw_all_fractals()
{
    glColor3f(1,1,1);
    glBegin(GL_LINE_STRIP);
    for( int i = 0; i < number_of_iterations; i++)
    {
        for( int j = 0; j < fractal_iterations[i].size(); j++ )
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
            if(up_pressed(float_x,float_y))
            {
                printf("UP\n");
                increment_iterations();
            }
            else if(down_pressed(float_x,float_y))
            {
                printf("Down.\n");
                decrement_iterations();
            }
            else if( go_pressed(float_x, float_y) )
            {    
                printf("Go.\n");
                recalculate_fractal();
            }
            else if( display_all_pressed(float_x, float_y))
            {
                printf("Toggle Display. \n");
                draw_previous_toggle();
            } 
        }
        else if(state == MouseButtonRelease)
        {
            //release point
            release_point();
        }
    }

}

static void draw_previous_toggle()
{
    draw_previous = !draw_previous;
    if(!draw_previous)
        draw_toggle = {.7,0,0};
    else
        draw_toggle = {0,.7,0};
}

static void increment_iterations()
{
    if( number_of_iterations == 6)
        return;
    num_vertices++;
    glutPostRedisplay();
}

static void decrement_iterations()
{
    if(number_of_iterations == 1)
        return;
    num_vertices--;
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
