#ifndef CBNS_H
#define CBNS_H

#include <stdio.h>
#include <stdint.h>
#include <complex.h>

void printBinary(uint64_t x);

uint64_t intRealToCBNS(uint32_t real);
uint64_t intComplexToCBNS(uint32_t real, uint32_t imag);

uint64_t addCBNS(uint64_t num1, uint64_t num2);
// num1 - num2
uint64_t subCBNS(uint64_t num1, uint64_t num2);
uint64_t mulCBNS(uint64_t num1, uint64_t num2);

#endif