#include <stdint.h>
#include <stddef.h>
#include "files_format/psf.h"


psf_glyphs init_psf_font(uint8_t *font) {

#ifdef USE_PSF1_FORMAT
    psf1_header *header = (psf1_header *)font;
    if (header->magic != PSF1_FONT_MAGIC) return (psf_glyphs){NULL, NULL};

    psf_glyphs glyphs = (psf_glyphs){header, font + sizeof(psf1_header)};
    return glyphs;
#endif

#ifdef USE_PSF2_FORMAT
    psf2_font *header = (psf2_font *)font;
#endif
}