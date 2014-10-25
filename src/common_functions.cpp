#include <GL/freeglut.h>
#include <math.h>
#include "shared_constants.h"
#include "common_functions.h"


void draw_big_point(float x, float y)
{
    float radius = 5;
    glColor3f(1,1,1);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    glTranslatef( x, y, 0 );
    glScalef(1.0,1.0, 1.0 );    // by ratio of major to minor axes
    GLUquadricObj *disk = gluNewQuadric();
    gluDisk( disk, 0, radius,500, 1 );
    gluDeleteQuadric( disk );
    glLoadIdentity();
}

void draw_buttons()
{
    float x,y;
    //Draw Increment Arrow
    glColor3f(BUTTON_RGB);
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
    glColor3f(ARROW_OUTLINE_RGB);
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
    glColor3f(BUTTON_RGB);
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
    glColor3f(ARROW_OUTLINE_RGB);
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

    //Reset Button
    glColor3f(RESET_RGB);
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
    glColor3f(RESET_OUTLINE_RGB);
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
}

void draw_menu_backgrounds()
{
    glColor3f(MENU_BACKGROUND_RGB);
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
void draw_text_areas()
{
    glColor3f(TEXT_AREA_RGB);
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

    glColor3f(BUTTON_OUTLINE_RGB);
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
void draw_text()
{
    //Displays the Player 1 string to the screen
    glColor3f(0,0,0);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(RIGHT_MENU_CENTER_X - VERTICES_HORIZONTAL_OFFSET ,RIGHT_MENU_CENTER_Y + VERTICES_VERTICAL_OFFSET,0);
    glScalef(0.15,0.15,1);
    glutStrokeString(GLUT_STROKE_ROMAN, (const unsigned char *)"Vertices");
    glPopMatrix();
    
    //Displays the Player 1 string to the screen
    glColor3f(0,0,0);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(RIGHT_MENU_CENTER_X - RESET_HORIZONTAL_OFFSET ,RIGHT_MENU_SPACE + RESET_VERTICAL_OFFSET,0);
    glScalef(0.15,0.15,1);
    glutStrokeString(GLUT_STROKE_ROMAN, (const unsigned char *)"Reset");
    glPopMatrix();
}
void draw_menu()
{
    draw_menu_backgrounds();
    draw_buttons();
    draw_text_areas();
    draw_text();
    glColor3f(1,0,0);
    glBegin(GL_POINTS);
        glVertex2f(RIGHT_MENU_CENTER_X, RIGHT_MENU_CENTER_Y);
    glEnd();
    
}

void draw_border()
{
    glColor3f(1,1,1);

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
