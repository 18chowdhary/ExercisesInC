/* Example code for Exercises in C.

This program shows a way to represent a BigInt type (arbitrary length integers)
using C strings, with numbers represented as a string of decimal digits in reverse order.

Follow these steps to get this program working:

1) Read through the whole program so you understand the design.

2) Compile and run the program.  It should run three tests, and they should fail.

3) Fill in the body of reverse_string().  When you get it working, the first test should pass.

4) Fill in the body of itoc().  When you get it working, the second test should pass.

5) Fill in the body of add_digits().  When you get it working, the third test should pass.

6) Uncomment the last test in main.  If your three previous tests pass, this one should, too.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

/* reverse_string: Returns a new string with the characters reversed.

It is the caller's responsibility to free the result.

s: string
returns: string
*/
char *reverse_string(char *s) {
    int len = strlen(s);
    // Duplicates the string
    char* rev = strdup(s);

    // Creates one variable that iterates through the string forwards from the
    // beginning and one variable that iterates through the string backwards
    // from the end, and swaps letters at analagous positions
    int start = 0;
    int end = len-1;
    while (start < end) {
      char temp = rev[start];
      rev[start] = rev[end];
      rev[end] = temp;

      start++;
      end--;
    }

    return rev;
}

/* ctoi: Converts a character to integer.

c: one of the characters '0' to '9'
returns: integer 0 to 9
*/
int ctoi(char c) {
    assert(isdigit(c));
    return c - '0';
}

/* itoc: Converts an integer to character.

i: integer 0 to 9
returns: character '0' to '9'
*/
char itoc(int i) {
  switch(i) {
    case 0: return '0';
    case 1: return '1';
    case 2: return '2';
    case 3: return '3';
    case 4: return '4';
    case 5: return '5';
    case 6: return '6';
    case 7: return '7';
    case 8: return '8';
    case 9: return '9';
    default: return 'o';
  }
}

/* add_digits: Adds three decimal digits, returns the total and carry.

a: character '0' to '9'
b: character '0' to '9'
c: character '0' to '9'
total: pointer to char
carry: pointer to char

*/
void add_digits(char a, char b, char c, char *total, char *carry) {
    // Calculates the sum
    int i_a = ctoi(a);
    int i_b = ctoi(b);
    int i_c = ctoi(c);
    int sum = i_a+i_b+i_c;

    // Finds the digit that should be in the 1's place using the modulo operator
    // and converts it to a character
    *total = itoc(sum%10);
    // Finds the digit that should be in the 2's place by dividing by 10 and
    // coverts it to a character
    *carry = itoc(sum/10);
}

/* Define a type to represent a BigInt.
   Internally, a BigInt is a string of digits, with the digits in
   reverse order.
*/
typedef char * BigInt;

/* add_bigint: Adds two BigInts

Stores the result in z.

x: BigInt
y: BigInt
carry_in: char
z: empty buffer
*/
void add_bigint(BigInt x, BigInt y, char carry_in, BigInt z) {
    char total, carry_out;
    int dx=1, dy=1, dz=1;
    char a, b;

    /* OPTIONAL TODO: Modify this function to allocate and return z
    *  rather than taking an empty buffer as a parameter.
    *  Hint: you might need a helper function.
    */

    if (*x == '\0') {
        a = '0';
        dx = 0;
    }else{
        a = *x;
    }
    if (*y == '\0') {
        b = '0';
        dy = 0;
    }else{
        b = *y;
    }

    // printf("%c %c %c\n", a, b, carry_in);
    add_digits(a, b, carry_in, &total, &carry_out);
    // printf("%c %c\n", carry_out, total);

    // if total and carry are 0, we're done
    if (total == '0' && carry_out == '0') {
        *z = '\0';
        return;
    }
    // otherwise store the digit we just computed
    *z = total;

    // and make a recursive call to fill in the rest.
    add_bigint(x+dx, y+dy, carry_out, z+dz);
}

/* print_bigint: Prints the digits of BigInt in the normal order.

big: BigInt
*/
void print_bigint(BigInt big) {
    char c = *big;
    if (c == '\0') return;
    print_bigint(big+1);
    printf("%c", c);
}

/* make_bigint: Creates and returns a BigInt.

Caller is responsible for freeing.

s: string of digits in the usual order
returns: BigInt
*/
BigInt make_bigint(char *s) {
    char *r = reverse_string(s);
    return (BigInt) r;
}

void test_reverse_string() {
    char *s = "123";
    char *t = reverse_string(s);
    if (strcmp(t, "321") == 0) {
        printf("reverse_string passed\n");
    } else {
        printf("reverse_string failed\n");
    }
}

void test_itoc() {
    char c = itoc(3);
    if (c == '3') {
        printf("itoc passed\n");
    } else {
        printf("itoc failed\n");
    }
}

void test_add_digits() {
    char total, carry;
    add_digits('7', '4', '1', &total, &carry);
    if (total == '2' && carry == '1') {
        printf("add_digits passed\n");
    } else {
        printf("add_digits failed\n");
    }
}

void test_add_bigint() {
    char *s = "1";
    char *t = "99999999999999999999999999999999999999999999";
    char *res = "000000000000000000000000000000000000000000001";

    BigInt big1 = make_bigint(s);
    BigInt big2 = make_bigint(t);
    BigInt big3 = malloc(100);

    add_bigint(big1, big2, '0', big3);

    if (strcmp(big3, res) == 0) {
        printf("add_bigint passed\n");
    } else {
        printf("add_bigint failed\n");
    }
}

int main (int argc, char *argv[])
{
    test_reverse_string();
    test_itoc();
    test_add_digits();

    test_add_bigint();
    return 0;
}
