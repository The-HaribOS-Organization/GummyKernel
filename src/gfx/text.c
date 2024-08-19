#include <stdint.h>
#include "gfx/text.h"
#include "gfx/framebuffer.h"
#include "gfx/font.h"
#include "gfx/utils.h"

/*
void drawChar(char character, Vec2 position, int_fast32_t foregroundColor) {

	Vec3 Colors;
	int_fast32_t mask[8] = {128, 64, 32, 16, 8, 4, 2, 1};
	uint8_t *glyph = zap_light18_psf + (int_fast32_t)character * 18;

	for (uint8_t cy = 0; cy < 22; cy++) {
		for (uint8_t cx = 0; cx < 8; cx++) {
			
			Colors = getPixelValue((Vec2){position.x + cx, position.y + cy});
			drawPoint((Vec2){(position.x + cx), ((position.y + cy))}, glyph[cy]&mask[cx]?foregroundColor:((Colors.red << 16) | (Colors.green << 8) | Colors.blue));
		}
	}
}
*/


uint16_t convert_int_to_psf(uint16_t c){
    switch (c)
    {
        case '•': return 0x7F; // U+007F
        case 'À': return 0x80; // U+0080
        case 'Á': return 0x81; // U+0081
        case 'Â': return 0x82; // U+0082
        case 'Ã': return 0x83; // U+0083
        case 'Ä': return 0x84; // U+0084
        case 'Å': return 0x85; // U+0085
        case 'Æ': return 0x86; // U+0086
        case 'Ç': return 0x87; // U+0087
        case 'È': return 0x88; // U+0088
        case 'É': return 0x89; // U+0089
        case 'Ê': return 0x8A; // U+008A
        case 'Ë': return 0x8B; // U+008B
        case 'Ì': return 0x8C; // U+008C
        case 'Í': return 0x8D; // U+008D
        case 'Î': return 0x8E; // U+008E
        case 'Ï': return 0x8F; // U+008F
        case 'Ð': return 0x90; // U+0090
        case 'Ñ': return 0x91; // U+0091
        case 'Ò': return 0x92; // U+0092
        case 'Ó': return 0x93; // U+0093
        case 'Ô': return 0x94; // U+0094
        case 'Õ': return 0x95; // U+0095
        case 'Ö': return 0x96; // U+0096
        case '*': return 0x97; // U+0097
        case 'Ø': return 0x98; // U+0098
        case 'Ù': return 0x99; // U+0099
        case 'Ú': return 0x9A; // U+009A
        case 'Û': return 0x9B; // U+009B
        case 'Ü': return 0x9C; // U+009C
        case 'Ý': return 0x9D; // U+009D
        case 'Þ': return 0x9E; // U+009E
        case 'ß': return 0x9F; // U+009F
        case '▒': return 0xA0; // U+00A0
        case '¡': return 0xA1; // U+00A1
        case '¢': return 0xA2; // U+00A2
        case '£': return 0xA3; // U+00A3
        case '€': return 0xA4; // U+00A4
        case '¥': return 0xA5; // U+00A5
        case 'Š': return 0xA6; // U+00A6
        case '§': return 0xA7; // U+00A7
        case 'š': return 0xA8; // U+00A8
        case '©': return 0xA9; // U+00A9
        case 'ª': return 0xAA; // U+00AA
        case '«': return 0xAB; // U+00AB
        case '¬': return 0xAC; // U+00AC
        case '¤': return 0xAD; // U+00AD
        case '®': return 0xAE; // U+00AE
        case 'ˉ': return 0xAF; // U+00AF
        case '°': return 0xB0; // U+00B0
        case '±': return 0xB1; // U+00B1
        case '²': return 0xB2; // U+00B2
        case '³': return 0xB3; // U+00B3
        case 'Ž': return 0xB4; // U+00B4
        case 'µ': return 0xB5; // U+00B5
        case '¶': return 0xB6; // U+00B6
        case '·': return 0xB7; // U+00B7
        case 'ž': return 0xB8; // U+00B8
        case '¹': return 0xB9; // U+00B9
        case 'º': return 0xBA; // U+00BA
        case '»': return 0xBB; // U+00BB
        case 'Œ': return 0xBC; // U+00BC
        case 'œ': return 0xBD; // U+00BD
        case 'Ÿ': return 0xBE; // U+00BE
        case '¿': return 0xBF; // U+00BF
        case '─': return 0xC0; // U+00C0
        case '│': return 0xC1; // U+00C1
        case '┌': return 0xC2; // U+00C2
        case '┐': return 0XC3; // U+00C3
        case '└': return 0xC4; // U+00C4
        case '┘': return 0xC5; // U+00C5
        case '├': return 0xC6; // U+00C6
        case '┤': return 0xC7; // U+00C7
        case '┬': return 0xC8; // U+00C8
        case '┴': return 0xC9; // U+00C9
        case '┼': return 0xCA; // U+00CA
        case '░': return 0xCB; // U+00CB
        case '⎺': return 0xCC; // U+00CC
        case '⎻': return 0xCD; // U+00CD
        case '⎼': return 0xCE; // U+00CE
        case '⎽': return 0xCF; // U+00CF
        case '═': return 0xD0; // U+00D0
        case '║': return 0xD1; // U+00D1
        case '╔': return 0xD2; // U+00D2
        case '╗': return 0xD3; // U+00D3
        case '╚': return 0xD4; // U+00D4
        case '╝': return 0xD5; // U+00D5
        case '╠': return 0xD6; // U+00D6
        case '╣': return 0xD7; // U+00D7
        case '╦': return 0xD8; // U+00D8
        case '╩': return 0xD9; // U+00D9
        case '╬': return 0xDA; // U+00DA
        case '█': return 0xDB; // U+00DB
        case '↑': return 0xDC; // U+00DC
        case '↓': return 0xDD; // U+00DD
        case '←': return 0xDE; // U+00DE
        case '→': return 0xDF; // U+00DF
        case 'à': return 0xE0; // U+00E0
        case 'á': return 0xE1; // U+00E1
        case 'â': return 0xE2; // U+00E2
        case 'ã': return 0xE3; // U+00E3
        case 'ä': return 0xE4; // U+00E4
        case 'å': return 0xE5; // U+00E5
        case 'æ': return 0xE6; // U+00E6
        case 'ç': return 0xE7; // U+00E7
        case 'è': return 0xE8; // U+00E8
        case 'é': return 0xE9; // U+00E9
        case 'ê': return 0xEA; // U+00EA
        case 'ë': return 0xEB; // U+00EB
        case 'ì': return 0xEC; // U+00EC
        case 'í': return 0xED; // U+00ED
        case 'î': return 0xEE; // U+00EE
        case 'ï': return 0xEF; // U+00EF
        case 'ð': return 0xF0; // U+00F0
        case 'ñ': return 0xF1; // U+00F1
        case 'ò': return 0xF2; // U+00F2
        case 'ó': return 0xF3; // U+00F3
        case 'ô': return 0xF4; // U+00F4
        case 'õ': return 0xF5; // U+00F5
        case 'ö': return 0xF6; // U+00F6
        case '÷': return 0xF7; // U+00F7
        case 'ø': return 0xF8; // U+00F8
        case 'ù': return 0xF9; // U+00F9
        case 'ú': return 0xFA; // U+00FA
        case 'û': return 0xFB; // U+00FB
        case 'ü': return 0xFC; // U+00FC
        case 'ý': return 0xFD; // U+00FD
        case 'þ': return 0xFE; // U+00FE
        case 'ÿ': return 0xFF; // U+00FF
        default: return c;
    }
}


void drawChar(uint16_t character, Vec2 position, int_fast32_t foregroundColor) {
	PSF1Header *header = (PSF1Header *)zap_light18_psf;
    uint8_t *glyphs = (uint8_t *)(zap_light18_psf + sizeof(PSF1Header));

    character = convert_int_to_psf(character);

    // Taille du glyphe (hauteur)
    uint32_t glyph_height = header->char_height;

    // Calculer l'offset du glyphe
    uint32_t offset = character * glyph_height;
    uint8_t *glyph = glyphs + offset;

    for (int row = 0; row < glyph_height; ++row) {
        uint8_t rowData = glyph[row];
        for (int col = 0; col < PSF_GLYPH_WIDTH; ++col) {
            if (rowData & (1 << (PSF_GLYPH_WIDTH - 1 - col))) {
                drawPoint((Vec2) {position.x + col, position.y + row}, foregroundColor);
            }
        }
    }
}


void drawString(char *string, Vec2 position, Vec3 color) {

    uint_fast32_t dx = 0;

    while(*string) {
        drawChar((uint16_t)(*string), (Vec2){position.x + dx, position.y}, ((color.red << 16) | (color.green << 8) | color.blue));
        dx += PSF_GLYPH_WIDTH;
		string++;
    } 
}
