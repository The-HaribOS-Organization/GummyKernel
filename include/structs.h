/*
    File          : structs.h
    Creation date : 11/07/2023
    Utility       : Contains useful structs to limit includes
 */

#ifndef GLOBAL_STRUCTS_H_INCLUDED
#define GLOBAL_STRUCTS_H_INCLUDED

////////////////////////
//  Maths structures  //
////////////////////////

typedef struct {
    uint32_t x;
    uint32_t y;
} Vec2u;

typedef struct {
    int32_t x;
    int32_t y;
} Vec2i;

typedef struct {
    float x;
    float y;
} Vec2f;

#endif // GLOBAL_STRUCTS_H_INCLUDED