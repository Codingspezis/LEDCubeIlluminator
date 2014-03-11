#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>

#include "communicator.h"

void randomEffectLoop(int delayMs, int rounds) {
	uint8_t *data = (uint8_t *)malloc(16);
	int i;
	for(i=0; i<rounds; i++) {
		memset(data, 0, 16);
		int j;
		for(j=0; j<16; j++) {
			data[j] = rand()%256;
		}
		usleep(delayMs * 1000);
		sendState(data);
	}
	free(data);
}
