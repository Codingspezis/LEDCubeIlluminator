#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "communicator.h"
#include "effects.h"

int main(int argc, char **argv) {
    // check arguments
    if(argc < 3) {
        printf("usage: %s addr port\n", *argv);
        return 0;
    }
    // connect to server
    if(initClient(argv[1], atoi(argv[2])) < 0) {
        printf("could not set up connection\n");
        return -1;
    }
    // illumination loop
    for(;;) {
        textRotateEffectLoop("LED", 100, 1);
        randomEffectLoop(100, 20);
        snakeEffectLoop(10, 100, 50);
        textXEffectLoop("WWW.CODINGSPEZIS.COM", 75, 1);
        rotateXEffectLoop(100, 1);
        rotateYEffectLoop(100, 1);
        rotateZEffectLoop(100, 1);
    }
    return 0;
}
