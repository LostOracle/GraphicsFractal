#ifndef _SHARED_CONSTANTS_H_
#define _SHARED_CONSTANTS_H_

//Define Drawable Area
#define DRAW_WINDOW_WIDTH 500
#define DRAW_WINDOW_HEIGHT 500

//Define Right Menu Area
#define RIGHT_MENU_WIDTH 125
#define RIGHT_MENU_HEIGHT DRAW_WINDOW_HEIGHT

//Define Top Menu Area
#define TOP_MENU_WIDTH (DRAW_WINDOW_WIDTH + RIGHT_MENU_WIDTH)
#define TOP_MENU_HEIGHT 125
//#define TOP_MENU_HEIGHT 0

//Define Total Window Area
#define TOTAL_WIDTH (DRAW_WINDOW_WIDTH + RIGHT_MENU_WIDTH)
#define TOTAL_HEIGHT (DRAW_WINDOW_HEIGHT + TOP_MENU_HEIGHT)

//Define Drawing Characteristics
#define BORDER_BUFFER 50 //add unusable space around draw area
#define MENU_BACKGROUND_RGB 0.5,0.5,0.5 //Menu area color
#define BUTTON_RGB 0,0.6,0
#define TEXT_AREA_RGB 0.7,0.7,0.7
#define BORDER_RGB 1,1,1 //Draw area border color
#define BUTTON_OUTLINE_RGB 1,1,1
#define ARROW_OUTLINE_RGB 1,1,1
#define RESET_RGB .8,0,0
#define RESET_OUTLINE_RGB 1,1,1
#define GO_RGB 0,.7,0
#define GO_OUTLINE_RGB 1,1,1

//Define Menu Positions
#define RIGHT_MENU_CENTER_X TOTAL_WIDTH - RIGHT_MENU_WIDTH/2.0
#define RIGHT_MENU_CENTER_Y (RIGHT_MENU_HEIGHT/2.0)
#define TEXT_AREA_HEIGHT 40
#define TEXT_AREA_WIDTH RIGHT_MENU_WIDTH * 0.8
#define RIGHT_MENU_SPACE 10
#define VERTICES_HORIZONTAL_OFFSET 32
#define RESET_HORIZONTAL_OFFSET 25
#define GO_HORIZONTAL_OFFSET 5
#define VERTICES_VERTICAL_OFFSET 10
#define RESET_VERTICAL_OFFSET 10
#define GO_VERTICAL_OFFSET 10

//Define Button Characteristics
#define ARROW_EDGE_LENGTH TEXT_AREA_WIDTH
#define ARROW_h 0.5*ARROW_EDGE_LENGTH*tan(30*M_PI/180.0)
#define UP_ARROW_CENTER_Y RIGHT_MENU_CENTER_Y + TEXT_AREA_HEIGHT + RIGHT_MENU_SPACE + ARROW_h
#define DOWN_ARROW_CENTER_Y RIGHT_MENU_CENTER_Y - TEXT_AREA_HEIGHT - RIGHT_MENU_SPACE - ARROW_h
#define ARROW_ALTITUDE ARROW_EDGE_LENGTH*sin(30*M_PI/180.0)/sin(120*M_PI/180.0)

const int MouseButtonPress	= 0;
const int MouseButtonRelease	= 1;
const int MouseLeftButton	= 0;
const int MouseMiddleButton	= 1;
const int MouseRightButton	= 2;

struct point
{
    point(float x1, float y1): x(x1), y(y1) {};
    float x;
    float y;
};

// colors
const float Black[]     = { 0.0, 0.0, 0.0 };
const float Red[]       = { 1.0, 0.0, 0.0 };
const float Green[]     = { 0.0, 1.0, 0.0 };
const float Blue[]      = { 0.0, 0.0, 1.0 };
const float Magenta[]   = { 1.0, 0.0, 1.0 }; 
const float Cyan[]      = { 0.0, 1.0, 1.0 };
const float Yellow[]    = { 1.0, 1.0, 0.0 };
const float White[]     = { 1.0, 1.0, 1.0 };
#endif
