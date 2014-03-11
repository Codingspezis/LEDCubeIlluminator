#include <math.h>
#include <string.h>

#include "utils.h"
#include "characters.h"

#define PI 3.14159265
double  TO_DEG = PI / 180.0;

void rotatePoint(float angle, int x0, int y0, int x1, int y1, int *x2, int *y2) {
	double c = cos(angle * TO_DEG);
	double s = sin(angle * TO_DEG);
	*x2 = round(c * (x1 - x0) - s * (y1 - y0) + x0);
	*y2 = round(s * (x1 - x0) - c * (y1 - y0) + y0);
}

void rotateCubeZ(float angle, uint8_t *src, uint8_t *dst) {
	int i, j, z;
	int x, y;
	memset(dst, 0, 16);
	for(z=0; z<5; z++) {
		for(i=0; i<5; i++) {
			for(j=0; j<5; j++) {
				if(ledState(src, i, j, z)) {
					rotatePoint(angle, 2, 2, i, j, &x, &y);
					setLed(dst, x, y, z);
				}
			}
		}
	}
}

void setChar(uint8_t *data, char c, int axis, int level) {
	int i;
	if(c >= 33 && c <= 122) {
		uint32_t charBits = characters[c-33];
		for(i=0; i<25; i++) {
			if(((uint8_t *)&charBits)[3 - i/8] & (1 << i%8)) {
				if(axis == 0)
					setLed(data, level, 4 - i%5, 4 - i/5);
				else if(axis == 1)
					setLed(data, i%5, level, 4 - i/5);
				else
					setLed(data, i%5, i/5, level);
			}
		}
	}
}

void shiftLeft(uint8_t *data) {
	int i;
	for(i=15; i>=0; i--) {
		data[i] <<= 1;
		if(i >= 1 && (data[i-1]&(1 << 7)))
			data[i] |= 1;
	}
}

void setLed(uint8_t *data, int x, int y, int z) {
	int ledNum = x + 5*y + 25*z;
	data[ledNum/8] |= (1 << (ledNum%8));
}

int ledState(uint8_t *data, int x, int y, int z) {
	int ledNum = x + 5*y + 25*z;
	return data[ledNum/8] & (1 << (ledNum%8));
}
