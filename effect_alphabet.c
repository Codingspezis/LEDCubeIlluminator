#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

#include "communicator.h"
#include "utils.h"

void shiftChar(int delayMs, char c, int axis) {
	uint8_t *data = (uint8_t *) malloc(16);
	int i;
	for(i=0; i<5; i++) {
		memset(data, 0, 16);
		setChar(data, c, axis, i);
		sendState(data);
		usleep(delayMs * 1000);
	}
	usleep(delayMs * 1000);
	free(data);
}

void textEffectLoop(char *text, int delayMs, int rounds, int axis) {
	int i;
	for(i=0; i<rounds; i++) {
		char *ptr = text;
		while(*ptr) {
			shiftChar(delayMs, *ptr++, axis);
		}
	}
}

void textXEffectLoop(char *text, int delayMs, int rounds) {
	textEffectLoop(text, delayMs, rounds, 0);
}

void textYEffectLoop(char *text, int delayMs, int rounds) {
	textEffectLoop(text, delayMs, rounds, 1);
}

void textZEffectLoop(char *text, int delayMs, int rounds) {
	textEffectLoop(text, delayMs, rounds, 2);
}
