/*
    File    : sound_blaster.h
    Utility : The SoundBlaster driver
 */

#ifndef KERNEL_SOUND_BLASTER_H_INCLUDED
#define KERNEL_SOUND_BLASTER_H_INCLUDED

// #include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "hardwareCommunication/io.h"

/////////////////////////
//  Constants & types  //
/////////////////////////

typedef enum {
	DSP_MIXER_PORT = 0x224,
	DSP_MIXER_DATA_PORT = 0x225,
	DSP_RESET_PORT = 0x226,
	DSP_READ_PORT = 0x22A,
	DSP_WRITE_PORT = 0x22C,
	DSP_READ_STATUS_PORT = 0x22E,
	DSP_ACK_PORT = 0x22F
} SoundBlasterPorts;

typedef enum {
	SET_TIME_CONSTANT = 0x40,
	SET_OUTPUT_SAMPLE_RATE = 0x41,
	TURN_SPEAKER_ON = 0xD1,
	TURN_SPEAKER_OFF = 0xD3,
	STOP_PLAYING_8_BITS_CHANNEL = 0xD0,
	RESUME_PLAYING_8_BITS_CHANNEL = 0xD4,
	STOP_PLAYING_16_BITS_CHANNEL = 0xD5,
	RESUME_PLAYING_16_BITS_CHANNEL = 0xD6,
	GET_DSP_VERSION = 0xE1
} DSPWritePortCommand;

typedef enum {
	MASTER_VOLUME = 0x22,
	SET_IRQ = 0x80
} DSPMixerPortCommand;

/////////////////
//  Functions  //
/////////////////

void soundBlaster_init();
void soundBlaster_turnOn();
void soundBlaster_turnOff();

uint8_t soundBlaster_setVolume(uint8_t left, uint8_t right);
void soundBlaster_setIrq(uint8_t irq_number);

#endif // KERNEL_SOUND_BLASTER_H_INCLUDED
