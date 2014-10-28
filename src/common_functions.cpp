#include <GL/freeglut.h>
#include <math.h>
#include "../include/shared_constants.h"
#include "../include/common_functions.h"


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

void draw_up_down_arrows()
{
    float x,y;
    //Draw Increment Arrow
    glColor3fv(UP_DOWN_BUTTON_COLOR);
    glBegin(GL_POLYGON);
        x = RIGHT_MENU_CENTER_X;
        y = UP_ARROW_CENTER_Y + ARROW_ALTITUDE;
        glVertex2f(x,y);
        
        x = RIGHT_MENU_CENTER_X + (ARROW_ALTITUDE*(-sin(120*M_PI/180.0)));
        y = UP_ARROW_CENTER_Y + (ARROW_ALTITUDE*(cos(120*M_PI/180.0)));
        glVertex2f(x,y);
        
        x = RIGHT_MENU_CENTER_X + (ARROW_ALTITUDE*(-sin(-120*M_PI/180.0)));
        y = UP_ARROW_CENTER_Y + (ARROW_ALTITUDE*(cos(-120*M_PI/180.0)));
        glVertex2f(x,y);
    glEnd();
    glColor3fv(BORDER_COLOR);
    glBegin(GL_LINE_LOOP);
        x = RIGHT_MENU_CENTER_X;
        y = UP_ARROW_CENTER_Y + ARROW_ALTITUDE;
        glVertex2f(x,y);
        
        x = RIGHT_MENU_CENTER_X + (ARROW_ALTITUDE*(-sin(120*M_PI/180.0)));
        y = UP_ARROW_CENTER_Y + (ARROW_ALTITUDE*(cos(120*M_PI/180.0)));
        glVertex2f(x,y);
        
        x = RIGHT_MENU_CENTER_X + (ARROW_ALTITUDE*(-sin(-120*M_PI/180.0)));
        y = UP_ARROW_CENTER_Y + (ARROW_ALTITUDE*(cos(-120*M_PI/180.0)));
        glVertex2f(x,y);
    glEnd();

    //Draw Decrement Arrow
    glColor3fv(UP_DOWN_BUTTON_COLOR);
    glBegin(GL_POLYGON);
        x = RIGHT_MENU_CENTER_X;
        y = DOWN_ARROW_CENTER_Y - ARROW_ALTITUDE;
        glVertex2f(x,y);
        
        x = RIGHT_MENU_CENTER_X + (ARROW_ALTITUDE*(-sin(120*M_PI/180.0)));
        y = DOWN_ARROW_CENTER_Y - (ARROW_ALTITUDE*(cos(120*M_PI/180.0)));
        glVertex2f(x,y);
        
        x = RIGHT_MENU_CENTER_X + (ARROW_ALTITUDE*(-sin(-120*M_PI/180.0)));
        y = DOWN_ARROW_CENTER_Y - (ARROW_ALTITUDE*(cos(-120*M_PI/180.0)));
        glVertex2f(x,y);
    glEnd();
    glColor3fv(BORDER_COLOR);
    glBegin(GL_LINE_LOOP);
        x = RIGHT_MENU_CENTER_X;
        y = DOWN_ARROW_CENTER_Y - ARROW_ALTITUDE;
        glVertex2f(x,y);
        
        x = RIGHT_MENU_CENTER_X + (ARROW_ALTITUDE*(-sin(120*M_PI/180.0)));
        y = DOWN_ARROW_CENTER_Y - (ARROW_ALTITUDE*(cos(120*M_PI/180.0)));
        glVertex2f(x,y);
        
        x = RIGHT_MENU_CENTER_X + (ARROW_ALTITUDE*(-sin(-120*M_PI/180.0)));
        y = DOWN_ARROW_CENTER_Y - (ARROW_ALTITUDE*(cos(-120*M_PI/180.0)));
        glVertex2f(x,y);
    glEnd();
}

void draw_go_button()
{
    float x,y;
    //Reset Button
    glColor3fv(GO_BUTTON_COLOR);
    glBegin(GL_POLYGON);
        x = RIGHT_MENU_CENTER_X - TEXT_AREA_WIDTH/2.0;
        y = RIGHT_MENU_SPACE + TEXT_AREA_HEIGHT;
        glVertex2f(x,y);

        x = RIGHT_MENU_CENTER_X + TEXT_AREA_WIDTH/2.0;
        glVertex2f(x,y);

        y = RIGHT_MENU_SPACE;
        glVertex2f(x,y);

        x = RIGHT_MENU_CENTER_X - TEXT_AREA_WIDTH/2.0;
        glVertex2f(x,y);
    glEnd();
    glColor3fv(BORDER_COLOR);
    glBegin(GL_LINE_LOOP);
        x = RIGHT_MENU_CENTER_X - TEXT_AREA_WIDTH/2.0;
        y = RIGHT_MENU_SPACE + TEXT_AREA_HEIGHT;
        glVertex2f(x,y);

        x = RIGHT_MENU_CENTER_X + TEXT_AREA_WIDTH/2.0;
        glVertex2f(x,y);

        y = RIGHT_MENU_SPACE;
        glVertex2f(x,y);

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

void draw_reset_button()
{
    float x,y;
    //Reset Button
    glColor3fv(RESET_BUTTON_COLOR);
    glBegin(GL_POLYGON);
        x = RIGHT_MENU_CENTER_X - TEXT_AREA_WIDTH/2.0;
        y = RIGHT_MENU_SPACE + TEXT_AREA_HEIGHT;
        glVertex2f(x,y);

        x = RIGHT_MENU_CENTER_X + TEXT_AREA_WIDTH/2.0;
        glVertex2f(x,y);

        y = RIGHT_MENU_SPACE;
        glVertex2f(x,y);

        x = RIGHT_MENU_CENTER_X - TEXT_AREA_WIDTH/2.0;
        glVertex2f(x,y);
    glEnd();
    glColor3fv(BORDER_COLOR);
    glBegin(GL_LINE_LOOP);
        x = RIGHT_MENU_CENTER_X - TEXT_AREA_WIDTH/2.0;
        y = RIGHT_MENU_SPACE + TEXT_AREA_HEIGHT;
        glVertex2f(x,y);

        x = RIGHT_MENU_CENTER_X + TEXT_AREA_WIDTH/2.0;
        glVertex2f(x,y);

        y = RIGHT_MENU_SPACE;
        glVertex2f(x,y);

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

bool go_pressed(float x, float y)
{
    if(x >= RIGHT_MENU_CENTER_X - TEXT_AREA_WIDTH/2.0 &&
       x <= RIGHT_MENU_CENTER_X + TEXT_AREA_WIDTH/2.0 &&
       y >= RIGHT_MENU_SPACE &&
       y <= RIGHT_MENU_SPACE + TEXT_AREA_HEIGHT )
        return true;
    return false;
}

bool reset_pressed(float x, float y)
{
    if(x >= RIGHT_MENU_CENTER_X - TEXT_AREA_WIDTH/2.0 &&
       x <= RIGHT_MENU_CENTER_X + TEXT_AREA_WIDTH/2.0 &&
       y >= RIGHT_MENU_SPACE &&
       y <= RIGHT_MENU_SPACE + TEXT_AREA_HEIGHT )
        return true;
    return false;
}

bool up_pressed(float x, float y)
{
    if(x >= RIGHT_MENU_CENTER_X + (ARROW_ALTITUDE*(-sin(120*M_PI/180.0))) &&
       x <= RIGHT_MENU_CENTER_X + (ARROW_ALTITUDE*(-sin(-120*M_PI/180.0))) &&
       y >= UP_ARROW_CENTER_Y + (ARROW_ALTITUDE*(cos(120*M_PI/180.0))) &&
       y <= UP_ARROW_CENTER_Y + ARROW_ALTITUDE)
        return true;
    return false;
}

bool down_pressed(float x, float y)
{
    if(x >= RIGHT_MENU_CENTER_X + (ARROW_ALTITUDE*(-sin(120*M_PI/180.0))) &&
       x <= RIGHT_MENU_CENTER_X + (ARROW_ALTITUDE*(-sin(-120*M_PI/180.0))) &&
       y <= DOWN_ARROW_CENTER_Y - (ARROW_ALTITUDE*(cos(120*M_PI/180.0))) &&
       y >= DOWN_ARROW_CENTER_Y - ARROW_ALTITUDE)
        return true;
    return false;
}

void draw_menu_backgrounds()
{
    glColor3fv(MENU_BACKGROUND_COLOR);
    //right menu
    glBegin(GL_POLYGON); 
        glVertex2f( TOTAL_WIDTH - RIGHT_MENU_WIDTH, TOTAL_HEIGHT);
        glVertex2f( TOTAL_WIDTH , TOTAL_HEIGHT);
        glVertex2f( TOTAL_WIDTH ,0);
        glVertex2f( TOTAL_WIDTH - RIGHT_MENU_WIDTH,0);
    glEnd();

    //top menu
    glBegin(GL_POLYGON);
        glVertex2f( 0, TOTAL_HEIGHT );
        glVertex2f( TOTAL_WIDTH, TOTAL_HEIGHT );
        glVertex2f( TOTAL_WIDTH, TOTAL_HEIGHT - TOP_MENU_HEIGHT );
        glVertex2f( 0, TOTAL_HEIGHT - TOP_MENU_HEIGHT );
    glEnd();
}
void draw_text_area()
{
    glColor3fv(NUMBER_FIELD_COLOR);
    float x, y;
    glBegin(GL_POLYGON);
        x = RIGHT_MENU_CENTER_X - TEXT_AREA_WIDTH/2.0;
        y = RIGHT_MENU_CENTER_Y + TEXT_AREA_HEIGHT;
        glVertex2f(x,y);

        x = RIGHT_MENU_CENTER_X + TEXT_AREA_WIDTH/2.0;
        glVertex2f(x,y);

        y = RIGHT_MENU_CENTER_Y - TEXT_AREA_HEIGHT;
        glVertex2f(x,y);

        x = RIGHT_MENU_CENTER_X - TEXT_AREA_WIDTH/2.0;
        glVertex2f(x,y);
    glEnd();

    glColor3fv(BORDER_COLOR);
    glBegin(GL_LINE_LOOP);
        x = RIGHT_MENU_CENTER_X - TEXT_AREA_WIDTH/2.0;
        y = RIGHT_MENU_CENTER_Y + TEXT_AREA_HEIGHT;
        glVertex2f(x,y);

        x = RIGHT_MENU_CENTER_X + TEXT_AREA_WIDTH/2.0;
        glVertex2f(x,y);

        y = RIGHT_MENU_CENTER_Y - TEXT_AREA_HEIGHT;
        glVertex2f(x,y);

        x = RIGHT_MENU_CENTER_X - TEXT_AREA_WIDTH/2.0;
        glVertex2f(x,y);
    glEnd();

}

void draw_border()
{
    glColor3fv(BORDER_COLOR);

    //Draw drawable area bounding box
    glBegin(GL_LINE_LOOP);
        glVertex2f(0,0);
        glVertex2f(0,TOTAL_HEIGHT - TOP_MENU_HEIGHT);
        glVertex2f(DRAW_WINDOW_WIDTH,TOTAL_HEIGHT - TOP_MENU_HEIGHT);
        glVertex2f(DRAW_WINDOW_WIDTH,0);
    glEnd();

    //Draw top/right menu divider
    glBegin(GL_LINE_STRIP);
        glVertex2f(TOTAL_WIDTH - RIGHT_MENU_WIDTH, TOTAL_HEIGHT - TOP_MENU_HEIGHT );
        glVertex2f(TOTAL_WIDTH, TOTAL_HEIGHT - TOP_MENU_HEIGHT);
    glEnd();
}
