/* Ce fichier contient les fonctions nécessaires
à l'utilisation du haut-parleur */

#ifndef _PC_SPEAKER_
#define _PC_SPEAKER_

#include <stdint.h>

void make_beep(uint32_t frequency);
void shutup();

#endif
