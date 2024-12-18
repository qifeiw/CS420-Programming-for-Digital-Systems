#include "bitFunctions.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    //circular_shift_left
    assert(circular_shift_left(0x80000001,1) == 0x00000003);

    //reverse function test
    assert(reverse_it(0xC0000001) == 0x80000003);

    //every_other_bit
    assert(every_other_bit(0xC0000001) == 0x8001);

    //date to binary and date from binary
    unsigned short int binary_date = date_to_binary(12,7,80);
    assert(binary_date == 0x63D0);
    int day;
    int month;
    int year;
    date_from_binary(0x1188, &day, &month, &year);
    assert(day==2 && month == 3 && year == 8);
    printf("Tests passed.\n");
    return 0;
}