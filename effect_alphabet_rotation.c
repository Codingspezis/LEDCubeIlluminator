#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

#include "communicator.h"
#include "utils.h"

void showCharXY(char c, int delayMs) {
	uint8_t *data1 = (uint8_t *)malloc(16);
	uint8_t *data2 = (uint8_t *)malloc(16);
	int i;
	for(i=0; i<3; i++) {
		memset(data1, 0, 16);
		setChar(data1, c, 0, i);
		sendState(data1);
		usleep(delayMs * 1000);
	}
	float a;
	for(a=0.0; a<=450.0; a=a+22.5) {
		memset(data2, 0, 16);
		rotateCubeZ(a, data1, data2);
		sendState(data2);
		usleep(delayMs * 500);
	}
	for(i=3; i<5; i++) {
		memset(data1, 0, 16);
		setChar(data1, c, 1, i);
		sendState(data1);
		usleep(delayMs * 1000);
	}
	usleep(delayMs * 4000);
	free(data1);
	free(data2);
}

void textRotateEffectLoop(char *text, int delayMs, int rounds) {
	char *ptr;
	int i;
	for(i=0; i<rounds; i++) {
		ptr = text;
		while(*ptr) {
			showCharXY(*ptr++, delayMs);
		}
	}
}
