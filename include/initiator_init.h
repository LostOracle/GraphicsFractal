/******************************************************************************
 * File: initiator_init.h
 * Authors: Ian Carlson, Christopher Smith
 * Description: This file is a little silly, but this was the only way to make
 *  a function defined in initiator.cpp available to main without also exposing
 *  all of the static functions in initiator.cpp, which would have caused
 *  a naming conflict with fractal.cpp and generator.cpp.
 *****************************************************************************/
#ifndef _INITIATOR_INIT_H_
#define _INITIATOR_INIT_H_
void initInitiator( void );
#endif
