/*
This file contains my solutions to Exercise 01 for Software Systems SP20.
I worked with Kristin Aoki on these exercises.

Author: Shreya Chowdhary
*/

#include <stdio.h>
#include <stdlib.h>

/*
Retrieves the value for a card based on the name of the card.

Returns the appropriate card value for valid card names, -1 if the
inputted card name is the stop character 'X', and prints out
an error message if the card name was invalid.

card_name: string array that contains the name of the card
*/
int get_value(char *card_name) {
  int val = 0;
  switch(card_name[0]) {
    case 'K':
    case 'Q':
    case 'J':
      val = 10;
      break;
    case 'A':
      val = 11;
      break;
    case 'X':
      val = -1;
      break;
    default:
      val = atoi(card_name);
      if ((val <= 0) || (val>10)) {
        puts("I don't understand that value!");
      }
  }
  return val;
}

/*
Returns the appropriate delta for the card count based on the
value of the card.

Returns +1 if the card value is between 2 and 7 and -1 if
the card value is 10.

val: integer representing the value of the card
*/
int update_count(int val) {
  if ((val > 2) && (val < 7)) {
    return 1;
  } else if (val == 10) {
    return -1;
  }
  return 0;
}

/*
Prompts the user for a card name and puts the reply in the given buffer.

card_name: the buffer where the result is stored
*/
void get_card_name(char* card_name) {
  puts("Enter the card name: ");
  scanf("%2s", card_name);
}

int main() {
  // Initializes the card name array and other variables
  char card_name[3];
  int count = 0;
  int val;

  // Keep counting cards until the user inputs the stop character
  do {
    get_card_name(card_name);
    val = get_value(card_name);
    count += update_count(val);
    printf("Current count: %i\n", count);
  } while (card_name[0] != 'X');

  return 0;
}
