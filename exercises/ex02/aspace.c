/* Example code for Think OS.

Copyright 2014 Allen Downey
License: GNU GPLv3

*/

#include <stdio.h>
#include <stdlib.h>

int var1;

void print_address() {
  int local = 0;
  printf("Address is %p\n", &local);
}

int main ()
{
    int var2 = 5;
    void* p = malloc(128);
    char* s = "Hello, World";
    void* q = malloc(128);
    print_address();

    void* chunk1 = malloc(32);
    void* chunk2 = malloc(32);

    printf ("Address of main is %p\n", main);
    printf ("Address of var1 is %p\n", &var1);
    printf ("Address of var2 is %p\n", &var2);
    printf ("p points to %p\n", p);
    printf ("s points to %p\n", s);
    printf("q points to %p\n", q);
    printf("Address of chunk1: %p\n", chunk1);
    printf("Address of chunk2: %p\n", chunk2);

    return 0;
}
