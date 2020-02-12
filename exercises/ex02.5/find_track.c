/* Example code for Exercises in C.

Modified version of an example from Chapter 2.5 of Head First C.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define NUM_TRACKS 5

char tracks[][80] = {
    "So What",
    "Freddie Freeloader",
    "Blue in Green",
    "All Blues",
    "Flamenco Sketches"
};


// Finds all tracks that contain the given string.
//
// Prints track number and title.
void find_track(char search_for[])
{
    int i;
    for (i=0; i<NUM_TRACKS; i++) {
        if (strstr(tracks[i], search_for)) {
            printf("Track %i: '%s'\n", i, tracks[i]);
        }
    }
}

// Finds all tracks that match the given pattern.
//
// Prints track number and title.
void find_track_regex(char pattern[])
{
  regex_t re;
  int return_value;

  // Tests the compilation of the regular expression and prints appropriate
  // error code if compilation is unsuccessful
  return_value = regcomp(&re, pattern, 0);
  if (return_value) {
    printf("Error with compiling the regular expression.");
    exit(1);
  }

  // Compares every track to the track name you're trying to find
  for (int i=0; i<NUM_TRACKS; i++) {
    // Tests if there is a match
    return_value = regexec(&re, tracks[i], 0, NULL, 0);
    // If match found, print the name of the track
    if (!return_value) {
      printf("Track number %i: %s\n", i, tracks[i]);
    }
    // If match not found, print error message
    else {
      printf("Track number %i: Error with finding the pattern.\n", i);
    }
  }
  regfree(&re);
}

// Truncates the string at the first newline, if there is one.
void rstrip(char s[])
{
    char *ptr = strchr(s, '\n');
    if (ptr) {
        *ptr = '\0';
    }
}

int main (int argc, char *argv[])
{
    char search_for[80];

    /* take input from the user and search */
    printf("Search for: ");
    fgets(search_for, 80, stdin);
    rstrip(search_for);
    //
    // find_track(search_for);
    find_track_regex(search_for);

    return 0;
}
