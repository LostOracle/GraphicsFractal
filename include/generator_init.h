/******************************************************************************
 * File: generator_init.h
 * Authors: Ian Carlson, Christopher Smith
 * Description: This file is a little silly, but this was the only way to make
 *  a function defined in generator.cpp available to main without also exposing
 *  all of the static functions in generator.cpp, which would have caused
 *  a naming conflict with fractal.cpp and initiator.cpp.
 *****************************************************************************/
#ifndef _GENERATOR_INIT_H_
#define _GENERATOR_INIT_H_

void initGenerator( void );

#endif
