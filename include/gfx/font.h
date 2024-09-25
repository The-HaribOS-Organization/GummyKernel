#ifndef _FONT_
#define _FONT_

#define _FONT_PSF2

#include <stdint.h>


// Quelques headers pour parser la font PSF pour plus tard.
#ifdef _FONT_PSF1
#define PSF_FONT_MAGIC 0x0436

typedef struct {
    uint16_t magic;
    uint8_t font_mode;
    uint8_t character_size;
} psf_font;

#elif defined(_FONT_PSF2)
#define PSF_FONT_MAGIC 0x864ab572

typedef struct {
    uint32_t magic;
    uint32_t version;
    uint32_t header_size;
    uint32_t flags;
    uint32_t num_glyph;
    uint32_t bytes_per_glyph;
    uint32_t height;
    uint32_t width;
} psf_font;

#endif

extern uint8_t zap_ext_light18_psf[];
extern const uint32_t zap_ext_light18_psf_len;

#endif
