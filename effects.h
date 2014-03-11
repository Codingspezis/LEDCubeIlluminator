#ifndef EFFECTS_H
#define EFFECTS_H

#include <stdint.h>

void levelXEffectLoop(int delayMs, int rounds);
void levelYEffectLoop(int delayMs, int rounds);
void levelZEffectLoop(int delayMs, int rounds);

void rotateXEffectLoop(int delayMs, int rounds);
void rotateYEffectLoop(int delayMs, int rounds);
void rotateZEffectLoop(int delayMs, int rounds);

void textXEffectLoop(char *text, int delayMs, int rounds);
void textYEffectLoop(char *text, int delayMs, int rounds);
void textZEffectLoop(char *text, int delayMs, int rounds);

void randomEffectLoop(int delayMs, int rounds);

void snakeEffectLoop(int length, int delayMs, int rounds);

void textRotateEffectLoop(char *text, int delayMs, int rounds);

#endif // EFFECTS_H
