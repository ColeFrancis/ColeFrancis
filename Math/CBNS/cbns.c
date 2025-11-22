#include "cbns.h"

void print_binary(unsigned long x) {
    // Prints an unsigned long in binary form without leading zeros

    int bits = sizeof(x) * 8;

    int started = 0;
    for (int i = bits-1; i >= 0; i--) {
        if (x & (1u << i)) {
            putchar('1');
            started = 1;
        }
        else if (started) {
            putchar('0');
        }
    }
}



uint64_t intRealToCBNS(uint32_t real) {
    uint64_t cbns = 0;
    int8_t digts_base_4[16] = {0};

    // convert to absolute value
    uint8_t neg = 0;
    if (real < 0){
        real *= -1;
        neg = 1;
    }
    // Convert real part to base 4
    for (int i = 15; i >= 0 && real > 0; i--) {
        digts_base_4[i] = real % 4;
        real /= 4;
    }

    // convert to normalized base -4
    for (int i = 14; i >= 0; i--) {
        digts_base_4[i] *= -1;
        
        if (i >= 1){
            digts_base_4[i-1] += 1;
        }
    }
    for (int i = 15; i >= 0; i--) {
        if (digts_base_4[i] == 4) {
            digts_base_4[i] == 0;

            if (i >= 1) {
                digts_base_4[i-1] -= 1;
            }
        }
    }

    // convert to CBNS
    for (int i = 15; i >= 0; i--) {
        switch(digts_base_4[i]) {
            case 1:
                cbns |= 0x1 << (4*i);
                break;

            case 2:
                cbns |= 0xc << (4*i);
                break;

            case 3:
                cbns |= 0xd << (5*i);
                break;

            default:
                break;
        }
    }

    return cbns;
}

uint64_t intImagToCBNS(uint32_t imag) {
    uint64_t cbns = intRealToCBNS(imag);
    if (imag >= 0) {
        cbns = mulCBNS(cbns, 0x3);
    }
    else {
        cbns = mulCBNS(cbns, 0x7);
    }

    return cbns;
}

uint64_t intComplexToCBNS(int32_t real, int32_t imag) {
    //convert real part to cbns
    uint64_t cbns_real = intRealToCBNS(real);

    // convert imaginary part to cbns
    uint64_t cbns_imag = intImagToCBNS(imag);

    // obtain full cbns
    uint64_t cbns = addCBNS(cbns_real, cbns_imag);

    return cbns;
}


uint64_t addCBNS(uint64_t num1, uint64_t num2) {

}

uint64_t subCBNS(uint64_t num1, uint64_t num2) {

}

uint64_t mulCBNS(uint64_t num1, uint64_t num2) {

}