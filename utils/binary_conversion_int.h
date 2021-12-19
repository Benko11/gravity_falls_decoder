#include <stdlib.h>
#include <string.h>
#include <math.h>

#ifndef BINARY_CONVERSION_INT_H
#define BINARY_CONVERSION_INT_H
unsigned char binary_conversion_int(char *numeric) {
    if (strlen(numeric) != 8)
        return -1;
    
    int res = 0;
    int current_power = 0;
    for (int i = 7; i >= 0; i--) {
        int multiplier = (int) pow(2, current_power);
        if (numeric[i] == '1')
            res += multiplier;
        current_power++;
    }

    return res;
}

#endif