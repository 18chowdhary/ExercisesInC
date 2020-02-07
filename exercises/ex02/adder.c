/*
This file contains my solution for Exercise 3, Adder, for HW02
of Software Systems. I worked with Kristin Aoki on these exercises.

Author: Shreya Chowdhary
*/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
// Limits the number of numbers to 100
#define ARRAY_SIZE 100
// Limits the length of the input string to 32 characters
#define BUFFER 32

// Declares the array of numbers and the sum of the array as global variables
int nums[ARRAY_SIZE];
int sum = 0;

/*
Converts the user-input number, represented as a string, to its integer value,
or returns the appropriate error message if the input was invalid. If the input
is not a number or longer than the string buffer, the appropriate error message
is printed and the function returns -1. Otherwise, it returns the value of the
number.

num: string array that contains the input number
*/
int get_num(char *num) {
  int num_val = atoi(num);
  // Checks if the input was in fact a number
  // I also check if the input was '0', because atoi returns 0 by default
  if (num_val == 0 && *num != '0') {
    printf("Error: that's not a valid input.\n");
    return -1;
  }
  // Checks if the input was longer than the buffer
  if (strlen(num) >= BUFFER) {
    printf("Error: your input string was too long.");
    return -1;
  }
  return num_val;
}

/*
Calculates the sum of nums, the array of numbers, and updates sum,
the global variable keeping track of the sum, appropriately.
*/
void sum_array() {
  for (int i = 0; i < sizeof(nums); i++) {
    sum += nums[i];
  }
}

int main() {
  char input_string[BUFFER];
  // Keeps track of the position of the index
  int i = 0;
  // Keeps reading until receives the EOF character
  while (fgets(input_string, sizeof(input_string), stdin) != NULL) {
    // Converts the input string
    int num = get_num(input_string);
    // If the array is full, break
    if (i >= ARRAY_SIZE) {
      printf("Error: you have exceeded the allocated buffer.\n");
      break;
    }
    // If the number is valid
    if (num != -1) {
      nums[i] = num;
      i++;
    }
  }

  // Calculate and print the sum of the array
  sum_array();
  printf("Your sum is %i\n", sum);
}
