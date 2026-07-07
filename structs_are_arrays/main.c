#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

typedef struct {
    uint16_t num1;
    uint8_t num2;
} MyStruct ;

int main(void) {
    MyStruct s1 = { 1000, 100 };

    MyStruct *ptr = &s1;

    printf("size: %zu\n", sizeof(MyStruct));
    printf("offset num1: %zu\n", offsetof(MyStruct, num1));
    printf("offset num2: %zu\n", offsetof(MyStruct, num2));

    printf("%d\n", s1.num1);
    printf("%d\n", *ptr);

    return 0;
}
