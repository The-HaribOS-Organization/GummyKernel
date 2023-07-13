/*
    File          : gop.c
    Creation date : 11/07/2023
 */

#include "graphics/gop.h"

static EFIGOP *gop;

static struct
{
    uint32_t *data;
    int height;
    int width;
} backBuffer;

////////////////////////
//  Global functions  //
////////////////////////

void gop_setGop(EFIGOP *newGop)
{
    gop = newGop;
}

void gop_swapBuffers()
{
    size_t bufferSize = gop->horizontalResolution * gop->verticalResolution * GOP_BYTES_PER_PIXEL;
    memcpy((uint32_t*)gop->frameBuffer, backBuffer.data, bufferSize);
}

//////////////////////
//  Draw functions  //
//////////////////////

void gop_drawPoint32bpp(Vec2u position, uint32_t pixel)
{
    *((backBuffer.data + (4 * backBuffer.width * position.y) + (4 * position.x))) = pixel;
}

void gop_drawLine(Vec2u posA, Vec2u posB, uint32_t pixel)
{
    uint32_t dx = posB.x - posA.x;
    uint32_t dy = posB.y - posA.y;

    if (posA.x != posB.x)
    {
        for (uint32_t x = posA.x; x < posB.x; ++x)
        {
            uint32_t y = posA.y + dy * (x - posA.x) / dx;
            gop_drawPoint32bpp((Vec2u){x, y}, pixel);
        }
    }
    else
    {
        for (uint32_t y = posA.y; y < posB.y; ++y)
        {
            uint32_t x = posA.x + dx * (y - posA.y) / dy;
            gop_drawPoint32bpp((Vec2u){x, y}, pixel);
        }
    }
}

void gop_drawRect(Vec2u posUpperLeft, Vec2u posDownRight, uint32_t pixel, bool filled)
{
    if (filled == true)
    {
        uint32_t dx = posDownRight.x - posUpperLeft.x;
        uint32_t dy = posDownRight.y - posUpperLeft.y;

        gop_drawLine((Vec2u){posUpperLeft.x, posUpperLeft.y}, (Vec2u){posUpperLeft.x + dx, posUpperLeft.y}, pixel);           // Up
        gop_drawLine((Vec2u){posUpperLeft.x, posUpperLeft.y + dy}, (Vec2u){posUpperLeft.x + dx, posUpperLeft.y + dy}, pixel); // Down
        gop_drawLine((Vec2u){posUpperLeft.x, posUpperLeft.y}, (Vec2u){posUpperLeft.x, posUpperLeft.y + dy}, pixel);           // Left
        gop_drawLine((Vec2u){posUpperLeft.x + dx, posUpperLeft.y}, (Vec2u){posUpperLeft.x + dx, posUpperLeft.y + dy}, pixel); // Right
    }
    else
    {
        for (uint32_t y = posUpperLeft.y; y < posDownRight.y; ++y)
        {
            for (uint32_t x = posUpperLeft.x; x < posDownRight.x; ++x)
            {
                gop_drawPoint32bpp((Vec2u){x, y}, pixel);
            }
        }
    }
}