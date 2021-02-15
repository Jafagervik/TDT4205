#include <stdio.h>

#define N 5

static int a = 2;
char b;

int rec_sum(int n) {
    if (n <= 0) return -1;
    if (n == 1) return  1;
    return n + rec_sum(n-1);
}

int main(int argc, char *argv[]) {
    int  c;
    char d;
    printf("The sum of numbers from 1 to %d is %d.\n", N, rec_sum(N));
    printf("Address of a (static int, global):    %p\n", &a);
    printf("Address of b (char,       global):    %p\n", &b);
    printf("Address of c (int,  local in main):   %p\n", &c);
    printf("Address of d (char, local in main):   %p\n", &d);
    return 0;
}

/* a) At some point, with a large enough n, the program will have a
 *    segmentation fault, due to a stack overflow caused by the recursion
 *    depth. On this computer, this occurs for n ~= 261900.
 *
 *    Also, beginning with a certain value of n, an integer overflow will
 *    occur. A normal signed integer usually has a size of 4 bytes, and a
 *    maximum value of (1<<31)-1 = 2147483647. This causes an overflow with n =
 *    2^16 = 65536.
 *
 * b) The distance between the two variables declared in main, `c` and `d`, is
 *    1. Since `d` is declared after `c`, it is placed below it on the stack.
 *    The distance then corresponds to the size of the type of `d`, which is 1.
 *
 *    In some cases the distance might be bigger than the type of the variable
 *    for alignment reasons.
 *
 *    The compiler may also reorder the variables on the stack for better
 *    alignment.
 *
 * c) The global variables are located in the memory segments Initialized Data
 *    or Uninitialized Data (bss), depending on whether they are initialized or
 *    not. `a` is in Initialized Data, and `b` is in the Uninitialized Data
 *    Segment (bss).
 *
 *    Both these segments are after the text segment, meaning they are at a
 *    relatively low memory address.
 *
 *    Global variables cannot be placed on neither the heap nor the stack,
 *    because they persist for the whole duration of the program and are not
 *    "created" at runtime.
 *
 * d) A local variable in a recursive function has to be allocated on the stack
 *    in each recursive call. The memory address decreases because the stack
 *    grows downwards from a high address.
 * */
