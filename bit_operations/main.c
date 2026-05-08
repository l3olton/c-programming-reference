#include <stdint.h>
#include <stdio.h>

int main(void)
{
    uint16_t a = 3 << 6;
    // 00000000 00000011 << 6
    // 00000000 11000000

    uint16_t a0 = a >> 4;
    // 00000000 11000000 >> 4
    // 00000000 00001100

    uint16_t b = ~(3 << 6);
    // ~(00000000 11000000)
    //   11111111 00111111

    uint8_t b0 = ~(3 << 6); // intermediate result of type int because ~ returns an int
    //  11111111 00111111 (int) = in 2s complement -00000000 11000001 = -193
    //           00111111 = 63 (implicit conversion to unsigned 8-bit removes top 8 bits)

    uint8_t b1 = ~(3 << 6) & 255; // masking with lower 8 bits for explicit conversion
    // 11111111 00111111 &
    // 00000000 11111111
    //          00111111 

    uint8_t c = 0b11000000 | 0b10101010;

    uint8_t d = 0b00110011;
    d |=        0b00011000;
    //            00111011

    uint8_t e = 0b00110011;
    e &=        0b00011000;
    //            00010000

    printf(" a: %b = %d\n", a, a);
    printf("a0: %b = %d\n", a0, a0);
    printf(" b: %b = %d\n", b, b);
    printf("b1: %b = %d\n", b1, b1);
    printf(" c: %b = %d\n", c, c);
    printf(" d: %b = %d\n", d, d);
    printf(" e: %b = %d\n", e, e);

    return 0;
}
