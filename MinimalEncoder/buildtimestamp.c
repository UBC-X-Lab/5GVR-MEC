
#include <stdio.h>
#include "buildtimestamp.h"

double buildtimestamp(long sec, long usec) {
    return sec + (usec * 0.000001);
}