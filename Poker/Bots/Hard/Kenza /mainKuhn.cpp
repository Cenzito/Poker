#include <iostream>
#include "Trainer.h"

int mainKuhn() {
    int iterations = 10000000;  // This takes around  40 seconds, if you take iterations = 1000000 then it takes around 5 seconds
    Trainer trainer;
    trainer.train(iterations);
    return 0;
}
