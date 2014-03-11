#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>

void shiftLeft(uint8_t *data);
void setLed(uint8_t *data, int x, int y, int z);
int ledState(uint8_t *data, int x, int y, int z);

void rotatePoint(float angle, int x0, int y0, int x1, int y1, int *x2, int *y2);
void rotateCubeZ(float angle, uint8_t *src, uint8_t *dst);

void setChar(uint8_t *data, char c, int axis, int level);

#endif // UTILS_H
