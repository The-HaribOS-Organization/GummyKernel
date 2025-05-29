#include <stdint.h>
#include "gfx/framebuffer.h"
#include "gfx/utils.h"
#include "klibc/string.h"
#include "files_format/psf.h"


volatile void *framebuffer, *backbuffer, *virtual_framebuffer;
uint_fast32_t pitch = 0;
Vec3 background_color = {66, 73, 58, 0};
psf_glyphs glyphs;


void scroll_windows(void) {

    uint32_t line_size = WIDTH * 4, scroll_pixels = 36;
    uint32_t *dest = NULL, *src = NULL;

    for (uint32_t y = 0; y < HEIGHT - scroll_pixels; y++) {

        src = &framebuffer[pitch * (y + 1) + (4 * WIDTH)];
        dest = &framebuffer[pitch * y + (4 * WIDTH)];
        memcpy(dest, src, line_size);
    }

    for (uint32_t y = HEIGHT - scroll_pixels; y < HEIGHT; y++) {
        for (uint32_t x = 0; x < WIDTH; x++) {
            drawPoint((Vec2){x, y}, (Vec3){66, 73, 58, 0});
        }
    }

    return;
}
