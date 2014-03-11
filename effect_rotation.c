#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

#include "communicator.h"
#include "utils.h"

void rotateEffectLoop(int delayMs, int axis) {
	uint8_t *buffer = (uint8_t *) malloc(16);
	float angle;
	int x, z, x2, y2;
	for(angle=0; angle<180.0; angle+=22.5) {
		memset(buffer, 0, 16);
		for(x=-1; x<6; x++) {
			rotatePoint(angle, 2, 2, x, 2, &x2, &y2);
			for(z=0; z<5; z++) {
				if(x2 < 5 && y2 < 5 &&
				   x2 >= 0 && y2 >= 0) {
					if(axis == 0)
						setLed(buffer, z, x2, y2);
					else if(axis == 1)
						setLed(buffer, x2, z, y2);
					else
						setLed(buffer, x2, y2, z);
				}
			}
		}
		sendState(buffer);
		usleep(delayMs * 1000);
	}
	free(buffer);
}

void rotateXEffectLoop(int delayMs, int rounds) {
	int i;
	for(i=0; i<(rounds*2); i++)
		rotateEffectLoop(delayMs, 0);
}

void rotateYEffectLoop(int delayMs, int rounds) {
	int i;
	for(i=0; i<(rounds*2); i++)
		rotateEffectLoop(delayMs, 1);
}

void rotateZEffectLoop(int delayMs, int rounds) {
	int i;
	for(i=0; i<(rounds*2); i++)
		rotateEffectLoop(delayMs, 2);
}
