/*****************************************************************************
 * File: fractal_display.cpp
 * Authors: Ian Carlson, Christopher Smith
 * Description: This file contains fractal display window callbacks and all
 * the functions used to calculate the iterations.
 * 
 *****************************************************************************/

#include "../include/fractal_display.h"

/******************************************************************************
 * Function: initFractalDisplay
 * Parameters: none
 * Returns: none
 * Description: This function initializes the window and its callbacks
 *
 *****************************************************************************/
void initFractalDisplay( void )
{
    glutInitWindowSize( ScreenWidth + TITLE_BAR_VERTICAL_SIZE/1.65*ASPECT_RATIO, 
                        ScreenHeight + TITLE_BAR_VERTICAL_SIZE/1.65 );
    glutInitWindowPosition( ScreenWidth/2, 0 );          // initial window position
    glutCreateWindow( "Fractal Display" );          // window title
    
    glClearColor( 0.0, 0.0, 0.0, 1.0 );         // use black for glClear command
    
    //Stores the fractal with no iterations from the generator in the first spot
    fractal_iterations.push_back( initiator_points );
    tmp = generator_points;
    //Calculates all the fractal iterations up to MAX_ITERATIONS
    recalculate_fractal();

    // callback routines
    glutDisplayFunc( display );             // how to redisplay window
    glutReshapeFunc( reshape );             // how to resize window
    glutMouseFunc( click );
}
/******************************************************************************
 * Function: display
 * Parameters: none
 * Returns: none
 * Description: GLUT call back used for fractal display
 *
 *****************************************************************************/
static void display( void )
{
    glClear( GL_COLOR_BUFFER_BIT );
    //If user does not want to display all iterations
     if( !draw_previous )
        draw_fractal_display();
    else
        draw_all_fractals();
    draw_menu_backgrounds();
    draw_up_down_arrows();
    draw_go_button();
    draw_toggle_button( draw_previous);
    draw_text_area();
    draw_text();
    draw_border();
    glFlush();
    glutSwapBuffers();
}
/******************************************************************************
 * Function: draw_fractal_display
 * Parameters: none
 * Returns: none
 * Description: This function draws the current iteration of the fractal
 *
 *****************************************************************************/
static void draw_fractal_display()
{
    glColor3f(1,1,1);
    glBegin(GL_LINE_STRIP);
    //Draws the current iteration of the fractal
    for( unsigned int i = 0; i < fractal_iterations[number_of_iterations -1].size(); i++)
    {
        glVertex2f( fractal_iterations[number_of_iterations - 1][i].x, fractal_iterations[number_of_iterations - 1][i].y );
    }
    glEnd();
}
/******************************************************************************
 * Function: draw_all_fractals
 * Parameters: none
 * Returns: none
 * Description: This function draws all the iterations of the fractals
 *
 *****************************************************************************/
static void draw_all_fractals()
{
    float fade_step = 1.0/number_of_iterations;
    //Draws all iterations of the fractal
    for( int i = number_of_iterations-1; i >= 0; i--)
    {
        
        glColor3f(0, fade_step * i , 1 - i * fade_step);
        if( i == 0)
            glColor3f(1,1,1);
        glBegin(GL_LINE_STRIP);
        for( unsigned int j = 0; j < fractal_iterations[i].size(); j++ )
            glVertex2f( fractal_iterations[i][j].x, fractal_iterations[i][j].y );
        glEnd();
    }
}

/******************************************************************************
 * Function: reshape
 * Parameters: int w, int h
 * Returns: none
 * Description: This function is the reshape callback for fractal display
 *
 *****************************************************************************/
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

/******************************************************************************
 * Function: click
 * Parameters: int button, int state, int x , int y
 * Returns: none
 * Description: Call back function for mouse clicks in Fractal Display
 *
 *****************************************************************************/ 
static void click( int button, int state, int x, int y )
{
    float float_y = ScreenHeight - y;
    float float_x = x;
    screen_to_gl(float_x,float_y);
    if( button == MouseLeftButton )
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
                //Sets tmp to new generator and clears fractal iterations and recalculates the new fractal
                tmp = generator_points;
                fractal_iterations.clear();
                fractal_iterations.push_back( initiator_points );
                recalculate_fractal();
            }
            else if( toggle_pressed(float_x, float_y) )
            {
                //Toggles displaying all iterations
                draw_previous = !draw_previous;
                glutPostRedisplay();
            }
        }
    }

}
/******************************************************************************
 * Function: draw_text
 * Parameters: none
 * Returns: none
 * Description: This function draws the text for the number of iterations so 
 * user know what is being displayed
 *
 *****************************************************************************/
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

/******************************************************************************
 * Function: increment_iterations
 * Parameters: none
 * Returns: none
 * Description: Increments the number of iterations global as button is pressed
 *
 *****************************************************************************/
static void increment_iterations()
{
    //Allows only a certain number of iterations
    if(number_of_iterations == MAX_ITERATIONS )
        return;
    number_of_iterations++;
    glutPostRedisplay();
}
/******************************************************************************
 * Function: draw_fractal_display
 * Parameters: none
 * Returns: none
 * Description: Decrements the number of iterations global as button is pressed
 *
 *****************************************************************************/
static void decrement_iterations()
{
    //Can not go to -1 iterations.
    if(number_of_iterations == 1)
        return;
    number_of_iterations--;
    glutPostRedisplay();
}
/******************************************************************************
 * Function: recalculate_fractal
 * Parameters: none
 * Returns: none
 * Description: This function calculates all the fractals up to a global constant
 *
 *****************************************************************************/
void recalculate_fractal( void )
{
    for( int i = fractal_iterations.size(); i < MAX_ITERATIONS; i++ )
    {
        //temporary iteration that is pushed into fractal_iterations
        vector<point> temp_iteration;
        for( unsigned int j = 0; j < (fractal_iterations[i-1].size()-1); j++)
        {
            //gets the start and end point of the segment that is getting replaced
            point end_point(fractal_iterations[i-1][j+1]);
            point start_point(fractal_iterations[i-1][j]);

            //Stores the first point so that all points in generator will be translated to origin
            point first_point(tmp[0].x, tmp[0].y);
            for(unsigned int k = 0; k < tmp.size(); k++ )
            {
                tmp[k].x = tmp[k].x - first_point.x;
                tmp[k].y = tmp[k].y - first_point.y;
            }
            //calculates the rotation needed
            float theta = atan2(end_point.y - start_point.y, end_point.x - start_point.x);
            //used to calculate scale between generator and line segment
            float tmp_distance = tmp[tmp.size()-1].x*tmp[tmp.size()-1].x + tmp[tmp.size()-1].y*tmp[tmp.size()-1].y;

            tmp_distance = sqrt(tmp_distance);
            //calculates the scale factor
            float scale =(start_point.x - end_point.x ) * (start_point.x - end_point.x);
            scale += (start_point.y - end_point.y ) * (start_point.y - end_point.y);
            scale = sqrt(scale)/tmp_distance;

            //applies the scaling and rotation to the generator then translates the points
            for( unsigned int l = 0; l < tmp.size()-1; l++)
            {
                point p(0,0);
                p.x = (tmp[l].x * cos(theta) - tmp[l].y * sin(theta) ) * scale + start_point.x;
                p.y = (tmp[l].x * sin(theta) + tmp[l].y * cos(theta) ) * scale + start_point.y;
                temp_iteration.push_back(p);
            }
        }
        //pushes the calculated iteration into fractal iterations
        temp_iteration.push_back(fractal_iterations[i-1][ fractal_iterations[i-1].size()-1 ]);
        fractal_iterations.push_back(temp_iteration);
        temp_iteration.clear();
    }
    glutPostRedisplay();
}
/******************************************************************************
 * Function: screen_to_gl
 * Parameters: float &x, float &y
 * Returns: none
 * Description: This function converts screen clicks to openGL coordinates
 *
 *****************************************************************************/
static void screen_to_gl(float & x, float & y)
{
    //Translates x and y into gl coordinates based on ScreenWidth and ScreenHeight
    if(ScreenWidth == ScreenHeight * ASPECT_RATIO )
    {
        x = (float)x / ScreenWidth * TOTAL_WIDTH;
        y = (float)y / ScreenHeight * TOTAL_HEIGHT;
    }
    else if(ScreenWidth > ScreenHeight * ASPECT_RATIO)
    {
        x = (float)x / (ScreenHeight * ASPECT_RATIO) * TOTAL_WIDTH;
        y = (float)y / ScreenHeight * TOTAL_HEIGHT;
    }
    else
    {
        x = (float)x / ScreenWidth * TOTAL_WIDTH;
        y = (float)y / ( ScreenWidth / ASPECT_RATIO ) * TOTAL_HEIGHT;
    }
}
