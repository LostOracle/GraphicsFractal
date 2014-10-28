/******************************************************************************
 * File: shared_constants.h
 * Authors: Ian Carlson, Christopher Smith
 * Description: This file puts all of the tweakable values used to size the
 *  display and menu for all the windows in one file. A single change here
 *  will affect all of the windows.
 *****************************************************************************/

#ifndef _SHARED_CONSTANTS_H_
#define _SHARED_CONSTANTS_H_

//Define Drawable Area - where the initiator, generator, and fractal appear
#define DRAW_WINDOW_WIDTH 500
#define DRAW_WINDOW_HEIGHT 500

//Define Right Menu Area - buttons and such
#define RIGHT_MENU_WIDTH 125
#define RIGHT_MENU_HEIGHT DRAW_WINDOW_HEIGHT

//Define Top Menu Area - Currently unused
#define TOP_MENU_WIDTH (DRAW_WINDOW_WIDTH + RIGHT_MENU_WIDTH)
//#define TOP_MENU_HEIGHT 125
#define TOP_MENU_HEIGHT 0

//Define Total Window Area
#define TOTAL_WIDTH (DRAW_WINDOW_WIDTH + RIGHT_MENU_WIDTH)
#define TOTAL_HEIGHT (DRAW_WINDOW_HEIGHT + TOP_MENU_HEIGHT)

//Define the window aspect ratio for proper reshaping
#define ASPECT_RATIO ((float)TOTAL_WIDTH/(float)TOTAL_HEIGHT)

//for positioning the windows relative to each other
#define TITLE_BAR_VERTICAL_SIZE 67

//add unusable space around draw area
#define BORDER_BUFFER 50 

//Define Menu Positions
#define RIGHT_MENU_CENTER_X (TOTAL_WIDTH - RIGHT_MENU_WIDTH/2.0)
#define RIGHT_MENU_CENTER_Y RIGHT_MENU_HEIGHT/2.0
#define TEXT_AREA_HEIGHT 40
#define TEXT_AREA_WIDTH RIGHT_MENU_WIDTH * 0.8
#define RIGHT_MENU_SPACE 10

#define VERTICES_HORIZONTAL_OFFSET 32
#define ITERATION_HORIZONTAL_OFFSET 40
#define VERTICE_NUM_HORIZONTAL_OFFSET 15
#define ITERATION_NUM_HORIZONTAL_OFFSET 15
#define RESET_HORIZONTAL_OFFSET 25
#define GO_HORIZONTAL_OFFSET 5

#define VERTICES_VERTICAL_OFFSET 20
#define ITERATION_VERTICAL_OFFSET 20
#define VERTICE_NUM_VERTICAL_OFFSET 20
#define ITERATION_NUM_VERTICAL_OFFSET 20
#define RESET_VERTICAL_OFFSET 10
#define GO_VERTICAL_OFFSET 10

//Define Button Characteristics
#define ARROW_EDGE_LENGTH TEXT_AREA_WIDTH

//perpendicular distance from the center to an edge
#define ARROW_h 0.5*ARROW_EDGE_LENGTH*tan(30*M_PI/180.0)

//Vertical up/down button center points
#define UP_ARROW_CENTER_Y (RIGHT_MENU_CENTER_Y + TEXT_AREA_HEIGHT + RIGHT_MENU_SPACE + ARROW_h)
#define DOWN_ARROW_CENTER_Y (RIGHT_MENU_CENTER_Y - TEXT_AREA_HEIGHT - RIGHT_MENU_SPACE - ARROW_h)

//distance from the center to any vertex
#define ARROW_ALTITUDE ARROW_EDGE_LENGTH*sin(30*M_PI/180.0)/sin(120*M_PI/180.0)

//Some handy mouse handling constants provided by Dr. Weiss
const int MouseButtonPress	= 0;
const int MouseButtonRelease= 1;
const int MouseLeftButton	= 0;
const int MouseMiddleButton	= 1; //unused
const int MouseRightButton	= 2; //unused

struct point
{
    point(float x1, float y1): x(x1), y(y1) {};
    point(const point &p)
    {
        x = p.x;
        y = p.y;
    };
    float x;
    float y;
};

//program specific colors
const float UP_DOWN_BUTTON_COLOR[] = { 0.0, 0.6, 0.0 };
const float RESET_BUTTON_COLOR[] = { 0.9, 0.0, 0.0 };
const float GO_BUTTON_COLOR[] = { 0.0, 0.7, 0.0 };
const float MENU_BACKGROUND_COLOR[] = { 0.5, 0.5, 0.5 };
const float NUMBER_FIELD_COLOR[] = { 0.7, 0.7, 0.7 };
const float BORDER_COLOR[] = { 1.0, 1.0, 1.0 };

//Some other colors provided by Dr. Weiss
const float Black[]     = { 0.0, 0.0, 0.0 };
const float Red[]       = { 1.0, 0.0, 0.0 };
const float Green[]     = { 0.0, 1.0, 0.0 };
const float Blue[]      = { 0.0, 0.0, 1.0 };
const float Magenta[]   = { 1.0, 0.0, 1.0 }; 
const float Cyan[]      = { 0.0, 1.0, 1.0 };
const float Yellow[]    = { 1.0, 1.0, 0.0 };
const float White[]     = { 1.0, 1.0, 1.0 };
#endif
