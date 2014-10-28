/******************************************************************************
 * File: common_functions.h
 * Authors: Ian Carlson, Christopher Smith
 * Description: This file contains the function definitions for the common drawing
 *  and click handling functions between all three windows.
 *****************************************************************************/
#ifndef _COMMON_FUNCTIONS_H_
#define _COMMON_FUNCTIONS_H_

void draw_menu_backgrounds();
void draw_text_area();
void draw_up_down_arrows();
void draw_reset_button();
void draw_go_button();
void draw_toggle_button(bool toggle_color);
void draw_border();
void draw_text_area();
void draw_big_point(float x, float y);
bool reset_pressed(float x, float y);
bool go_pressed(float x, float y);
bool up_pressed(float x, float y);
bool down_pressed(float x, float y);
bool toggle_pressed(float x, float y);
#endif
