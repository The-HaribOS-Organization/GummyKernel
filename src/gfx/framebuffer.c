#include <stdint.h>
#include "gfx/framebuffer.h"
#include "gfx/utils.h"


volatile void *framebuffer;
uint_fast32_t pitch = 0;

Vec3 background_color = {26, 35, 50, 0};