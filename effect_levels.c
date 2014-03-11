#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "communicator.h"
#include "effects.h"
#include "utils.h"

void generateXLevelEffect(uint8_t *data, int level) {
	memset(data, 0x00, 16);
	int i, j;
	for(i=0; i<5; i++) {
		for(j=0; j<5; j++) {
			setLed(data, level, i, j);
		}
	}
}

void generateYLevelEffect(uint8_t *data, int level) {
	memset(data, 0x00, 16);
	int i, j;
	for(i=0; i<5; i++) {
		for(j=0; j<5; j++) {
			setLed(data, i, level, j);
		}
	}
}

void generateZLevelEffect(uint8_t *data, int level) {
	memset(data,     0xFF,  3);
	memset(data + 3, 0x00, 13);
	data[3] |= 1;
	int i, j;
	for(i=0; i<level; i++) {
		for(j=0; j<25; j++)
			shiftLeft(data);
	}
}

void effectLoop(void (*fn)(uint8_t *, int), int delayMs, int rounds) {
	uint8_t *data = (uint8_t *) malloc(16);
	int i, j;
	for(i=0; i<rounds; i++) {
		for(j=0; j<5; j++) {
			fn(data, j);
			sendState(data);
			usleep(delayMs * 1000);
		}
		for(j=3; (i==(rounds-1) && j>=0) || (i<(rounds-1) && j>0); j--) {
			fn(data, j);
			sendState(data);
			usleep(delayMs * 1000);
		}
	}
	free(data);
}

void levelXEffectLoop(int delayMs, int rounds) {
	effectLoop(generateXLevelEffect, delayMs, rounds);
}

void levelYEffectLoop(int delayMs, int rounds) {
	effectLoop(generateYLevelEffect, delayMs, rounds);
}

void levelZEffectLoop(int delayMs, int rounds) {
	effectLoop(generateZLevelEffect, delayMs, rounds);
}
