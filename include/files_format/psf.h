#ifndef _PSF_H
#define _PSF_H

#include <stdint.h>

#define USE_PSF1_FORMAT
#define PSF1_FONT_MAGIC 0x3604
#define PSF1_MODE512 0x01
#define PSF1_MODEHASTAB 0x02
#define PSF1_MODESEQ 0x04
#define PSF2_FONT_MAGIC 0x72b54a86
#define PSF2_HAS_UNICODE_TABLE 0x00000001



// Quelques headers pour parser la font PSF pour plus tard.

typedef struct {
    uint16_t magic;
    uint8_t font_mode;
    uint8_t character_size;
} psf1_header;

typedef struct {
    uint32_t magic;
    uint32_t version;
    uint32_t header_size;
    uint32_t flags;
    uint32_t num_glyph;
    uint32_t bytes_per_glyph;
    uint32_t height;
    uint32_t width;
} psf2_header;

typedef struct {
#ifdef USE_PSF1_FORMAT
    psf1_header *header;
#endif
#ifdef USE_PSF2_FORMAT
    psf2_header *header;
#endif
    uint8_t *glyphs;
} psf_glyphs;

psf_glyphs init_psf_font(uint8_t *font);

#endif
