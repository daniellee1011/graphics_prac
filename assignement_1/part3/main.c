#include <stdio.h>

int* px = NULL;

void foo() {
    printf("foo\n");
    *px = 7;
}

int main() {
    char* name = "dongwook";
    char* name2 = "lee";

    printf("my name is: %s\n", name);

    foo();

    name = name2;
    printf("my name is: %s\n", name);

    return 0;
}