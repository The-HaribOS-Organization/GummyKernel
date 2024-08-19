#ifndef _FONT_
#define _FONT_

#include <stdint.h>

#define PSF_GLYPH_WIDTH 8       // largeur des glyphes en pixels
#define PSF1_MODE512 0x01       // si le bit est set la font a 512 glyphs sinon elle en a 256
#define PSF1_MODEHASTAB 0x02    // si le bit est set la font a une table unicode (remap des unicode)
#define PSF1_MODESEQ 0x04       // Equivalent de PSF1_MODEHASTAB

typedef struct {
    uint8_t magic[2];       // toujours 0x0436 (0x36 0x04)
    uint8_t flags;          // flags (PSF1_MODE512, PSF1_MODEHASTAB, PSF1_MODESEQ)
    uint8_t char_height;    // hauteur des glyphes en pixels
} PSF1Header;

extern uint8_t zap_light18_psf[];
extern uint_fast32_t zap_light18_psf_len;

#endif
