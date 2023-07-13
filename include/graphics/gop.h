/*
    File          : gop.h
    Creation date : 11/07/2023
    Utility       : Contains functions to print and draw with gop
 */

#ifndef TERMINAL_GOP_H_INCLUDED
#define TERMINAL_GOP_H_INCLUDED

#include <string.h>
#include <stdbool.h>

#include "structs.h"

/////////////////////////
//  Constants & types  //
/////////////////////////

#define GOP_BYTES_PER_PIXEL 4

////////////////////////
//  Global functions  //
////////////////////////

// Set the gop that will be used as front buffer
void gop_setGop(EFIGOP *newGop);

// With all the functions you write/draw on a internal buffer
// With this function, you write the internal buffer on the screen
void gop_swapBuffers();

//////////////////////
//  Draw functions  //
//////////////////////

void gop_drawPoint32bpp(Vec2u position, uint32_t pixel);
void gop_drawLine(Vec2u posA, Vec2u posB, uint32_t pixel);

void gop_drawRect(Vec2u posUpperLeft, Vec2u posDownRight, uint32_t pixel, bool filled);

#endif // TERMINAL_GOP_H_INCLUDED