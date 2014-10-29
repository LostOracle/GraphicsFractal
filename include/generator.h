#ifndef _GENERATOR_H_
#define _GENERATOR_H_

/******************************************************************************
 * File: generator.h
 * Authors: Ian Carlson, Christopher Smith
 * Description: Contains the includes, globals, and prototypes private
 *  to generator.cpp
 *****************************************************************************/

// include files
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <math.h>
#include <stdlib.h>
using namespace std;

// use OpenGL graphics and the GLUT graphical user interface
#include <GL/freeglut.h>
#include "../include/shared_constants.h"
#include "../include/common_functions.h"
#include "../include/generator_init.h"

static int ScreenWidth = 0.5*(TOTAL_WIDTH);
static int ScreenHeight = 0.5*(TOTAL_HEIGHT);

static void display( void );
static void click( int button, int state, int x, int y);
static void drag( int x, int y );
static void reshape( int w, int h );
static void init_default_fractal();
static void draw_generator();
static void screen_to_gl(float & x, float & y);
static void draw_text();
static void release_point();
static void pickup_point(float x, float y);
static void move_point(float x, float y);
static void new_generator();
static void reset();
static void increment_vertices();
static void decrement_vertices();

//this is shared with display_fractal
vector<point> generator_points;

static int acquired_point = -1;
static int num_vertices = 5;

#endif
