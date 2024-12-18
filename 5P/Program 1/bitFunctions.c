#include "bitFunctions.h"
//left-shift by n positions
unsigned int circular_shift_left(unsigned int value, int n) {
    unsigned int leftShifted = value << n;
    unsigned int rightShifted = value >> (32 - n);
    return (leftShifted | rightShifted);
}
unsigned int reverse_it(unsigned int value) {
    unsigned result = 0;
    for (int i = 0; i < 32; i++) {
        unsigned int temp = ((value >> i) & 0x1) << (31 - i);
        result = result | temp;
    }
    return result;
}
unsigned short int every_other_bit(unsigned int value) {
    unsigned short int result = 0;
    for (int i = 0; i < 16; i++) {
        unsigned int temp = (value >> (2 * i) & 1) << i;
        result = result | temp;
    }
    return result;
}
unsigned short int date_to_binary(int day, int month, int year) {
    int day_binary = (day & 0x1F) << 11;
    int month_binary = (month & 0x0F) << 7;
    int year_binary = year & 0x7F;
    return day_binary | month_binary | year_binary;
}
void date_from_binary(unsigned short int value, int *day, int *month, int *year) {
    *day = (value >> 11) & 0x1F;
    *month = (value >> 7) & 0x0F;
    *year = value & 0x7F;
}