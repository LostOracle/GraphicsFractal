/*****************************************************************************
 * File: common_functions.cpp
 * Authors: Ian Carlson, Christopher Smith
 * Description: This file contains functions needed by the initiator,
 *  generator, and display_fractal windows.
 *  **************************************************************************/
#include "../include/common_functions.h"

/******************************************************************************
 * Function: draw_big_point
 * Parameters:
 *  x - x coordinate in GL coordinates at which to draw the point
 *  y - y coordinate in GL coordinates at which to draw the point
 * Returns: none
 * Description: This function draws a large point at the specified x y location.
 *  The color of the point is dependant on a call to glColorxx before the
 *  function call.
 *
 *  This function was pretty much shamelessly stolen from Dr. Weiss's 
 *  OpenGLDemo code.
 *****************************************************************************/
void draw_big_point(float x, float y)
{
    float radius = 5;
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    glTranslatef( x, y, 0 );
    glScalef(1.0,1.0, 1.0 );    // by ratio of major to minor axes
    GLUquadricObj *disk = gluNewQuadric();
    gluDisk( disk, 0, radius,500, 1 );
    gluDeleteQuadric( disk );
    glLoadIdentity();
}

/******************************************************************************
 * Function: draw_up_down_arrows
 * Parameters: none
 * Returns: none
 * Description: This function draws the up and down arrows on the window. This
 *  function relies on the #defined constants in shared_constants.h to know
 *  where to draw the arrows and the colors to use.
 *****************************************************************************/
void draw_up_down_arrows()
{
    float x,y;
 
    //Draw Increment Arrow
    glColor3fv(UP_DOWN_BUTTON_COLOR);
    glBegin(GL_POLYGON);
        //Top vertex
        x = RIGHT_MENU_CENTER_X;
        y = UP_ARROW_CENTER_Y + ARROW_ALTITUDE;
        glVertex2f(x,y);
        
        //Bottom Left Vertex
        x = RIGHT_MENU_CENTER_X + (ARROW_ALTITUDE*(-sin(120*M_PI/180.0)));
        y = UP_ARROW_CENTER_Y + (ARROW_ALTITUDE*(cos(120*M_PI/180.0)));
        glVertex2f(x,y);
        
        //Bottom Right Vertex
        x = RIGHT_MENU_CENTER_X + (ARROW_ALTITUDE*(-sin(-120*M_PI/180.0)));
        y = UP_ARROW_CENTER_Y + (ARROW_ALTITUDE*(cos(-120*M_PI/180.0)));
        glVertex2f(x,y);
    glEnd();

    //Draw Increment Arrow Border
    glColor3fv(BORDER_COLOR);
    glBegin(GL_LINE_LOOP);
        //Top Vertex
        x = RIGHT_MENU_CENTER_X;
        y = UP_ARROW_CENTER_Y + ARROW_ALTITUDE;
        glVertex2f(x,y);
        
        //Bottom Left Vertex
        x = RIGHT_MENU_CENTER_X + (ARROW_ALTITUDE*(-sin(120*M_PI/180.0)));
        y = UP_ARROW_CENTER_Y + (ARROW_ALTITUDE*(cos(120*M_PI/180.0)));
        glVertex2f(x,y);
        
        //Bottom Right Vertex
        x = RIGHT_MENU_CENTER_X + (ARROW_ALTITUDE*(-sin(-120*M_PI/180.0)));
        y = UP_ARROW_CENTER_Y + (ARROW_ALTITUDE*(cos(-120*M_PI/180.0)));
        glVertex2f(x,y);
    glEnd();

    //Draw Decrement Arrow
    glColor3fv(UP_DOWN_BUTTON_COLOR);
    glBegin(GL_POLYGON);
        //Bottom Vertex
        x = RIGHT_MENU_CENTER_X;
        y = DOWN_ARROW_CENTER_Y - ARROW_ALTITUDE;
        glVertex2f(x,y);
        
        //Top Right Vertex
        x = RIGHT_MENU_CENTER_X + (ARROW_ALTITUDE*(-sin(120*M_PI/180.0)));
        y = DOWN_ARROW_CENTER_Y - (ARROW_ALTITUDE*(cos(120*M_PI/180.0)));
        glVertex2f(x,y);
        
        //Top Left Vertex
        x = RIGHT_MENU_CENTER_X + (ARROW_ALTITUDE*(-sin(-120*M_PI/180.0)));
        y = DOWN_ARROW_CENTER_Y - (ARROW_ALTITUDE*(cos(-120*M_PI/180.0)));
        glVertex2f(x,y);
    glEnd();

    //Draw Decrement Arrow Border
    glColor3fv(BORDER_COLOR);
    glBegin(GL_LINE_LOOP);
        //Bottom Vertex
        x = RIGHT_MENU_CENTER_X;
        y = DOWN_ARROW_CENTER_Y - ARROW_ALTITUDE;
        glVertex2f(x,y);
        
        //Top Right Vertex
        x = RIGHT_MENU_CENTER_X + (ARROW_ALTITUDE*(-sin(120*M_PI/180.0)));
        y = DOWN_ARROW_CENTER_Y - (ARROW_ALTITUDE*(cos(120*M_PI/180.0)));
        glVertex2f(x,y);
        
        //Top Left Vertex
        x = RIGHT_MENU_CENTER_X + (ARROW_ALTITUDE*(-sin(-120*M_PI/180.0)));
        y = DOWN_ARROW_CENTER_Y - (ARROW_ALTITUDE*(cos(-120*M_PI/180.0)));
        glVertex2f(x,y);
    glEnd();
}

/******************************************************************************
 * Function draw_go_button
 * Parameters: none
 * Returns: none
 * Description: This function draws the Go button in the fractal_display
 *  window. It depends on #defines in shared_constants.h.
 *****************************************************************************/
void draw_go_button()
{
    float x,y;
    //Draw the button background
    glColor3fv(GO_BUTTON_COLOR);
    glBegin(GL_POLYGON);
        //TL Corner
        x = RIGHT_MENU_CENTER_X - TEXT_AREA_WIDTH/2.0;
        y = RIGHT_MENU_SPACE + TEXT_AREA_HEIGHT;
        glVertex2f(x,y);

        //TR Corner
        x = RIGHT_MENU_CENTER_X + TEXT_AREA_WIDTH/2.0;
        glVertex2f(x,y);

        //BR Corner
        y = RIGHT_MENU_SPACE;
        glVertex2f(x,y);
    
        //BL Corner
        x = RIGHT_MENU_CENTER_X - TEXT_AREA_WIDTH/2.0;
        glVertex2f(x,y);
    glEnd();

    //Draw the button Border
    glColor3fv(BORDER_COLOR);
    glBegin(GL_LINE_LOOP);
        //TL Corner
        x = RIGHT_MENU_CENTER_X - TEXT_AREA_WIDTH/2.0;
        y = RIGHT_MENU_SPACE + TEXT_AREA_HEIGHT;
        glVertex2f(x,y);

        //TR Corner
        x = RIGHT_MENU_CENTER_X + TEXT_AREA_WIDTH/2.0;
        glVertex2f(x,y);

        //BR Corner
        y = RIGHT_MENU_SPACE;
        glVertex2f(x,y);

        //BL Corner
        x = RIGHT_MENU_CENTER_X - TEXT_AREA_WIDTH/2.0;
        glVertex2f(x,y);
    glEnd();
    
    //Display the Go button text
    glColor3fv(Black);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(RIGHT_MENU_CENTER_X - GO_HORIZONTAL_OFFSET ,RIGHT_MENU_SPACE + GO_VERTICAL_OFFSET,0);
    glScalef(0.15,0.15,1);
    glutStrokeString(GLUT_STROKE_ROMAN, (const unsigned char *)"Go");
    glPopMatrix();
}

/******************************************************************************
 * Function: draw_reset_button
 * Parameters: None
 * Returns: None
 * Description: This function draws the reset button on the initiator and
 *  generator windows. It depends on #defines in shared_constands.h
 *****************************************************************************/
void draw_reset_button()
{
    float x,y;
    //Button Background
    glColor3fv(RESET_BUTTON_COLOR);
    glBegin(GL_POLYGON);
        //TL Corner
        x = RIGHT_MENU_CENTER_X - TEXT_AREA_WIDTH/2.0;
        y = RIGHT_MENU_SPACE + TEXT_AREA_HEIGHT;
        glVertex2f(x,y);

        //TR Corner
        x = RIGHT_MENU_CENTER_X + TEXT_AREA_WIDTH/2.0;
        glVertex2f(x,y);

        //BR Corner
        y = RIGHT_MENU_SPACE;
        glVertex2f(x,y);

        //BL Corner
        x = RIGHT_MENU_CENTER_X - TEXT_AREA_WIDTH/2.0;
        glVertex2f(x,y);
    glEnd();
    //Button Border
    glColor3fv(BORDER_COLOR);
    glBegin(GL_LINE_LOOP);
        //TL Corner
        x = RIGHT_MENU_CENTER_X - TEXT_AREA_WIDTH/2.0;
        y = RIGHT_MENU_SPACE + TEXT_AREA_HEIGHT;
        glVertex2f(x,y);

        //TR Corner
        x = RIGHT_MENU_CENTER_X + TEXT_AREA_WIDTH/2.0;
        glVertex2f(x,y);

        //BR Corner
        y = RIGHT_MENU_SPACE;
        glVertex2f(x,y);

        //BL Corner
        x = RIGHT_MENU_CENTER_X - TEXT_AREA_WIDTH/2.0;
        glVertex2f(x,y);
    glEnd();
    
    //Display the Reset button text
    glColor3fv(Black);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(RIGHT_MENU_CENTER_X - RESET_HORIZONTAL_OFFSET ,RIGHT_MENU_SPACE + RESET_VERTICAL_OFFSET,0);
    glScalef(0.15,0.15,1);
    glutStrokeString(GLUT_STROKE_ROMAN, (const unsigned char *)"Reset");
    glPopMatrix();
}

/******************************************************************************
 * Function draw_toggle_button
 * Parameters: none
 * Returns: none
 * Description: This function draws the toggle button in the display
 *  window. It depends on #defines in shared_constants.h
 *****************************************************************************/
void draw_toggle_button(bool toggle_color)
{
    float x,y;
    //Pick the proper color
    if(toggle_color)
        glColor3fv(GO_BUTTON_COLOR);
    else
        glColor3fv(RESET_BUTTON_COLOR);

    //Draw the button background
    glBegin(GL_POLYGON);
        //TL Corner
        x = RIGHT_MENU_CENTER_X - TEXT_AREA_WIDTH/2.0;
        y = RIGHT_MENU_HEIGHT - TEXT_AREA_HEIGHT - RIGHT_MENU_SPACE;
        glVertex2f(x,y);

        //TR Corner
        x = RIGHT_MENU_CENTER_X + TEXT_AREA_WIDTH/2.0;
        glVertex2f(x,y);

        //BR Corner
        y = RIGHT_MENU_HEIGHT - RIGHT_MENU_SPACE;
        glVertex2f(x,y);

        //BL Corner
        x = RIGHT_MENU_CENTER_X - TEXT_AREA_WIDTH/2.0;
        glVertex2f(x,y);
    glEnd();

    //Draw the button border
    glColor3fv(BORDER_COLOR);
    glBegin(GL_LINE_LOOP);
        //TL Corner
        x = RIGHT_MENU_CENTER_X - TEXT_AREA_WIDTH/2.0;
        y = RIGHT_MENU_HEIGHT - TEXT_AREA_HEIGHT - RIGHT_MENU_SPACE;
        glVertex2f(x,y);

        //TR Corner
        x = RIGHT_MENU_CENTER_X + TEXT_AREA_WIDTH/2.0;
        glVertex2f(x,y);

        //BR Corner
        y = RIGHT_MENU_HEIGHT - RIGHT_MENU_SPACE;
        glVertex2f(x,y);

        //BL Corner
        x = RIGHT_MENU_CENTER_X - TEXT_AREA_WIDTH/2.0;
        glVertex2f(x,y);
    glEnd();
    
    //Display the toggle button text
    glColor3fv(Black);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(RIGHT_MENU_CENTER_X - TOGGLE_HORIZONTAL_OFFSET, RIGHT_MENU_HEIGHT - TOGGLE_VERTICAL_OFFSET,0);
    glScalef(0.15,0.15,1);
    glutStrokeString(GLUT_STROKE_ROMAN, (const unsigned char *)"View All");
    glPopMatrix();
}

/******************************************************************************
 * Function: toggle_pressed
 * Paramters: 
 *  x - x coordinate of the click in gl coordinates
 *  y - y coordinate of the click in gl coordinates
 * Returns:
 *  true if the click was on the toggle button
 *  else false
 *  Description: This function checks for clicks on the toggle button
 *      Relies on #defines in shared_constants.h
 *****************************************************************************/
bool toggle_pressed( float x, float y )
{
    if(x >= RIGHT_MENU_CENTER_X - TEXT_AREA_WIDTH/2.0 &&
       x <= RIGHT_MENU_CENTER_X + TEXT_AREA_HEIGHT/2.0 &&
       y <= RIGHT_MENU_HEIGHT - RIGHT_MENU_SPACE &&
       y >= RIGHT_MENU_HEIGHT - TEXT_AREA_HEIGHT - RIGHT_MENU_SPACE )
        return true;
    return false;
}

/******************************************************************************
 * Function: go_pressed
 * Paramters: 
 *  x - x coordinate of the click in gl coordinates
 *  y - y coordinate of the click in gl coordinates
 * Returns:
 *  true if the click was on the toggle button
 *  else false
 *  Description: This function checks for clicks on the go button
 *      Relies on #defines in shared_constants.h
 *****************************************************************************/
bool go_pressed(float x, float y)
{
    if(x >= RIGHT_MENU_CENTER_X - TEXT_AREA_WIDTH/2.0 &&
       x <= RIGHT_MENU_CENTER_X + TEXT_AREA_WIDTH/2.0 &&
       y >= RIGHT_MENU_SPACE &&
       y <= RIGHT_MENU_SPACE + TEXT_AREA_HEIGHT )
        return true;
    return false;
}

/******************************************************************************
 * Function: reset_pressed
 * Paramters: 
 *  x - x coordinate of the click in gl coordinates
 *  y - y coordinate of the click in gl coordinates
 * Returns:
 *  true if the click was on the reset button
 *  else false
 *  Description: This function checks for clicks on the reset button
 *      Relies on #defines in shared_constants.h
 *****************************************************************************/
bool reset_pressed(float x, float y)
{
    if(x >= RIGHT_MENU_CENTER_X - TEXT_AREA_WIDTH/2.0 &&
       x <= RIGHT_MENU_CENTER_X + TEXT_AREA_WIDTH/2.0 &&
       y >= RIGHT_MENU_SPACE &&
       y <= RIGHT_MENU_SPACE + TEXT_AREA_HEIGHT )
        return true;
    return false;
}

/******************************************************************************
 * Function: up_pressed
 * Paramters: 
 *  x - x coordinate of the click in gl coordinates
 *  y - y coordinate of the click in gl coordinates
 * Returns:
 *  true if the click was on the up button
 *  else false
 *  Description: This function checks for clicks on the up button
 *      Relies on #defines in shared_constants.h
 *****************************************************************************/
bool up_pressed(float x, float y)
{
    if(x >= RIGHT_MENU_CENTER_X + (ARROW_ALTITUDE*(-sin(120*M_PI/180.0))) &&
       x <= RIGHT_MENU_CENTER_X + (ARROW_ALTITUDE*(-sin(-120*M_PI/180.0))) &&
       y >= UP_ARROW_CENTER_Y + (ARROW_ALTITUDE*(cos(120*M_PI/180.0))) &&
       y <= UP_ARROW_CENTER_Y + ARROW_ALTITUDE)
        return true;
    return false;
}

/******************************************************************************
 * Function: down_pressed
 * Paramters: 
 *  x - x coordinate of the click in gl coordinates
 *  y - y coordinate of the click in gl coordinates
 * Returns:
 *  true if the click was on the down button
 *  else false
 *  Description: This function checks for clicks on the down button
 *      Relies on #defines in shared_constants.h
 *****************************************************************************/
bool down_pressed(float x, float y)
{
    if(x >= RIGHT_MENU_CENTER_X + (ARROW_ALTITUDE*(-sin(120*M_PI/180.0))) &&
       x <= RIGHT_MENU_CENTER_X + (ARROW_ALTITUDE*(-sin(-120*M_PI/180.0))) &&
       y <= DOWN_ARROW_CENTER_Y - (ARROW_ALTITUDE*(cos(120*M_PI/180.0))) &&
       y >= DOWN_ARROW_CENTER_Y - ARROW_ALTITUDE)
        return true;
    return false;
}

/******************************************************************************
 * Function: draw_menu_background
 * Parameters: none
 * Returns: none
 * Description: This function draws the backgrounds for the right and top menus
 *  if they exist.
 *  Depends on shared_constants.h
 *****************************************************************************/
void draw_menu_backgrounds()
{
    glColor3fv(MENU_BACKGROUND_COLOR);
    //right menu
    glBegin(GL_POLYGON);
        //TL Corner
        glVertex2f( TOTAL_WIDTH - RIGHT_MENU_WIDTH, TOTAL_HEIGHT);
        //TR Corner
        glVertex2f( TOTAL_WIDTH , TOTAL_HEIGHT);
        //BR Corner
        glVertex2f(TOTAL_WIDTH ,0);
        //BL Corner
        glVertex2f( TOTAL_WIDTH - RIGHT_MENU_WIDTH,0);
    glEnd();

    //top menu
    glBegin(GL_POLYGON);
        //TL Corner
        glVertex2f( 0, TOTAL_HEIGHT );
        //TR Corner
        glVertex2f( TOTAL_WIDTH, TOTAL_HEIGHT );
        //BR Corner
        glVertex2f( TOTAL_WIDTH, TOTAL_HEIGHT - TOP_MENU_HEIGHT );
        //BL Corner
        glVertex2f( 0, TOTAL_HEIGHT - TOP_MENU_HEIGHT );
    glEnd();
}

/******************************************************************************
 * Function: draw_text_area
 * Paramters: none
 * Returns: none
 * Description: This function draws the background for the text field for each
 *  window. Depends on shared_constants.h
 *****************************************************************************/
void draw_text_area()
{
    glColor3fv(NUMBER_FIELD_COLOR);
    float x, y;
    //text area background
    glBegin(GL_POLYGON);
        //TL Corner
        x = RIGHT_MENU_CENTER_X - TEXT_AREA_WIDTH/2.0;
        y = RIGHT_MENU_CENTER_Y + TEXT_AREA_HEIGHT;
        glVertex2f(x,y);

        //TR Corner
        x = RIGHT_MENU_CENTER_X + TEXT_AREA_WIDTH/2.0;
        glVertex2f(x,y);

        //BR Corner
        y = RIGHT_MENU_CENTER_Y - TEXT_AREA_HEIGHT;
        glVertex2f(x,y);

        //BL Corner
        x = RIGHT_MENU_CENTER_X - TEXT_AREA_WIDTH/2.0;
        glVertex2f(x,y);
    glEnd();
    
    //text area border
    glColor3fv(BORDER_COLOR);
    glBegin(GL_LINE_LOOP);
        //TL Corner
        x = RIGHT_MENU_CENTER_X - TEXT_AREA_WIDTH/2.0;
        y = RIGHT_MENU_CENTER_Y + TEXT_AREA_HEIGHT;
        glVertex2f(x,y);

        //TR Corner
        x = RIGHT_MENU_CENTER_X + TEXT_AREA_WIDTH/2.0;
        glVertex2f(x,y);

        //BR Corner
        y = RIGHT_MENU_CENTER_Y - TEXT_AREA_HEIGHT;
        glVertex2f(x,y);

        //BL Corner
        x = RIGHT_MENU_CENTER_X - TEXT_AREA_WIDTH/2.0;
        glVertex2f(x,y);
    glEnd();

}

/******************************************************************************
 * Function: draw_border
 * Paramters: none
 * Returns: none
 * Description: Draws lines around the drawing window
 *****************************************************************************/
void draw_border()
{
    glColor3fv(BORDER_COLOR);

    //Draw drawable area bounding box
    glBegin(GL_LINE_LOOP);
        //BL Corner
        glVertex2f(0,0);
        //BR Corner
        glVertex2f(0,TOTAL_HEIGHT - TOP_MENU_HEIGHT);
        //TR Corner
        glVertex2f(DRAW_WINDOW_WIDTH,TOTAL_HEIGHT - TOP_MENU_HEIGHT);
        //TL Corner
        glVertex2f(DRAW_WINDOW_WIDTH,0);
    glEnd();

    //Draw top/right menu divider
    glBegin(GL_LINE_STRIP);
        glVertex2f(TOTAL_WIDTH - RIGHT_MENU_WIDTH, TOTAL_HEIGHT - TOP_MENU_HEIGHT );
        glVertex2f(TOTAL_WIDTH, TOTAL_HEIGHT - TOP_MENU_HEIGHT);
    glEnd();
}
