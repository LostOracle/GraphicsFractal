#ifndef _FRACTAL_DISPLAY_H_
#define _FRACTAL_DISPLAY_H_

/******************************************************************************
 * File: fractal_display.h
 * Authors: Ian Carlson, Christopher Smith
 * Description: This file contains the globals, includes, and prototypes
 *  private to fractal_display.cpp
 *****************************************************************************/

#include "../include/shared_constants.h"
#include "../include/common_functions.h"
#include "../include/fractal_init.h"
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <math.h>
using namespace std;
#include<GL/freeglut.h>

//Local file callbacks and fractal display window functions
static void display( void );
static void click( int button, int state, int x, int y);
static void reshape( int w, int h );
static void draw_fractal_display();
static void draw_all_fractals();
static void screen_to_gl(float & x, float & y);
static void increment_iterations();
static void decrement_iterations();
static void recalculate_fractal();
static void draw_text();

//vectors of points from the initiator and generator
extern vector<point> initiator_points;
extern vector<point> generator_points;

static vector< vector<point> > fractal_iterations;
static int number_of_iterations = 1;
//Flag used to display all iterations or just the current iteration
static bool draw_previous = false;
static int ScreenWidth = TOTAL_WIDTH;
static int ScreenHeight = TOTAL_HEIGHT;
static vector<point> tmp;
#define MAX_ITERATIONS 8

#endif
