/* Ce fichier contient les macros ainsi que les 
prototypes de fonctions nécessaires à l'utilisation
du sound blaster afin de jouer des sons sur l'ordinateur.*/

#ifndef _SOUND_BLASTER_
#define _SOUND_BLASTER_

#include <stdint.h>
#include <stdbool.h>

enum sound_blaster_ports {
	DSP_MIXER_PORT = 0x224,
	DSP_MIXER_DATA_PORT = 0x225,
	DSP_RESET_PORT = 0x226,
	DSP_READ_PORT = 0x22A,
	DSP_WRITE_PORT = 0x22C,
	DSP_READ_STATUS_PORT = 0x22E,
	DSP_ACK_PORT = 0x22F
};

enum dsp_write_port_command {
	SET_TIME_CONSTANT = 0x40,
	SET_OUTPUT_SAMPLE_RATE = 0x41,
	TURN_SPEAKER_ON = 0xD1,
	TURN_SPEAKER_OFF = 0xD3,
	STOP_PLAYING_8_BITS_CHANNEL = 0xD0,
	RESUME_PLAYING_8_BITS_CHANNEL = 0xD4,
	STOP_PLAYING_16_BITS_CHANNEL = 0xD5,
	RESUME_PLAYING_16_BITS_CHANNEL = 0xD6,
	GET_DSP_VERSION = 0xE1
};

enum dsp_mixer_port_command {
	MASTER_VOLUME = 0x22,
	SET_IRQ = 0x80
};

void init_sound_blaster();
void turn_on_speaker();
void turn_off_speaker();
uint8_t set_volume(uint8_t left, uint8_t right);
void set_irq(uint8_t irq_number);

#endif
