#ifndef _INITIATOR_H_
#define _INITIATOR_H_

/******************************************************************************
 * File: initiator.h
 * Authors: Ian Carlson, Christopher Smith
 * Description: Prototypes and globals private to initiator.cpp.
 *****************************************************************************/

// include files
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <math.h>
using namespace std;

// use OpenGL graphics and the GLUT graphical user interface
#include <GL/freeglut.h>
#include "../include/shared_constants.h"
#include "../include/common_functions.h"
#include "../include/initiator_init.h"

static void display( void );
static void click( int button, int state, int x, int y);
static void drag( int x, int y );
static void reshape( int w, int h );
static void draw_initiator();
static void init_default_fractal();
static void draw_initiator();
static void screen_to_gl(float & x, float & y);
static void release_point();
static void pickup_point(float x, float y);
static void move_point(float x, float y);
static void reset();
static void increment_vertices();
static void decrement_vertices();
static void new_initiator();

//shared with display_fractal
vector<point> initiator_points;

static int ScreenWidth = 0.5*(TOTAL_WIDTH);
static int ScreenHeight = 0.5*(TOTAL_HEIGHT);
static int acquired_point = -1;
static int num_vertices = 4;

#endif
