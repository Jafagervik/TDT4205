#include <stdio.h>

const int c = 1;
int d, counter = 0;

unsigned int rec(unsigned int number) {
    char array[1000];
    counter++;
    return rec(counter);
}

int main(void) {
    int a = rec(c);
    printf("%d\n", a);
    return 0;
}

