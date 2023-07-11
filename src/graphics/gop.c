/*
    File          : gop.c
    Creation date : 11/07/2023
 */

#include "graphics/gop.h"

static EFI_GRAPHICS_OUTPUT_PROTOCOL *gop;

static struct
{
    UINT32 *data;
    int height;
    int width;
} backBuffer;

////////////////////////
//  Global functions  //
////////////////////////

void gop_setGop(EFI_GRAPHICS_OUTPUT_PROTOCOL *newGop)
{
    gop = newGop;
}

void gop_swapBuffers()
{
    size_t bufferSize = gop->Mode->Info->HorizontalResolution * gop->Mode->Info->VerticalResolution * GOP_BYTES_PER_PIXEL;
    memcpy((UINT32*)gop->Mode->FrameBufferBase, backBuffer.data, bufferSize);
}

//////////////////////
//  Draw functions  //
//////////////////////

void gop_drawPoint32bpp(Vec2u position, UINT32 pixel)
{
    *((backBuffer.data + (4 * backBuffer.width * position.y) + (4 * position.x))) = pixel;
}

void gop_drawLine(Vec2u posA, Vec2u posB, UINT32 pixel)
{
    UINT32 dx = posB.x - posA.x;
    UINT32 dy = posB.y - posA.y;

    if (posA.x != posB.x)
    {
        for (UINT32 x = posA.x; x < posB.x; ++x)
        {
            UINT32 y = posA.y + dy * (x - posA.x) / dx;
            gop_drawPoint32bpp((Vec2u){x, y}, pixel);
        }
    }
    else
    {
        for (UINT32 y = posA.y; y < posB.y; ++y)
        {
            UINT32 x = posA.x + dx * (y - posA.y) / dy;
            gop_drawPoint32bpp((Vec2u){x, y}, pixel);
        }
    }
}

void gop_drawRect(Vec2u posUpperLeft, Vec2u posDownRight, UINT32 pixel, bool filled)
{
    if (filled == true)
    {
        UINT32 dx = posDownRight.x - posUpperLeft.x;
        UINT32 dy = posDownRight.y - posUpperLeft.y;

        gop_drawLine((Vec2u){posUpperLeft.x, posUpperLeft.y}, (Vec2u){posUpperLeft.x + dx, posUpperLeft.y}, pixel);           // Up
        gop_drawLine((Vec2u){posUpperLeft.x, posUpperLeft.y + dy}, (Vec2u){posUpperLeft.x + dx, posUpperLeft.y + dy}, pixel); // Down
        gop_drawLine((Vec2u){posUpperLeft.x, posUpperLeft.y}, (Vec2u){posUpperLeft.x, posUpperLeft.y + dy}, pixel);           // Left
        gop_drawLine((Vec2u){posUpperLeft.x + dx, posUpperLeft.y}, (Vec2u){posUpperLeft.x + dx, posUpperLeft.y + dy}, pixel); // Right
    }
    else
    {
        for (UINT32 y = posUpperLeft.y; y < posDownRight.y; ++y)
        {
            for (UINT32 x = posUpperLeft.x; x < posDownRight.x; ++x)
            {
                gop_drawPoint32bpp((Vec2u){x, y}, pixel);
            }
        }
    }
}