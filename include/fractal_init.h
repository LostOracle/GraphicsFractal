/******************************************************************************
 * File: fractal_display.h
 * Authors: Ian Carlson, Christopher Smith
 * Description: This file is a little silly, but this was the only way to make
 *  a function defined in fractal.cpp available to main without also exposing
 *  all of the static functions in fractal.cpp, which would have caused
 *  a naming conflict with initiator.cpp and generator.cpp.
 *****************************************************************************/
#ifndef _FRACTAL_INIT_H_
#define _FRACTAL_INIT_H_

void initFractalDisplay( void );

#endif
