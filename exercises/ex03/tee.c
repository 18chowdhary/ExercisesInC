/*
This file contains my solution to HW03 for the Software Systems class at Olin.
This file is my implementation of `tee`.

Author: Shreya Chowdhary

Answers to questions:

3. I tried to develop incrementally, starting with implementing just the case
for writing and then adding the case for appending. This worked well because I
caught errors earlier and faster. In the future, though, I would try to plan my
implementation ahead of time rather than just jumping into it.

4. The professional code has much more error handling, especially for if
there's issues working with any of the files. For example, before reading in
any user input, the professional code tries to check if there are any issues
opening any of the files and presumably saves the open files somewhere (I
think? This is slightly unclear to me in the professional implementation).
Additionally, the professional code checks to make sure all the operations
were successful (like write and close by checking for an error code) and prints
error messages if they were not.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
  char c;
  int appendMode = 0;
  char input_string[512];
  FILE* outFile;
  int i = 0;

  // Process command line arguments
  while ((c = getopt(argc, argv, "a")) != EOF) {
    switch(c) {
      // Set mode to appending if the -a argument was included
      case 'a':
      appendMode = 1;
      break;
      // Return an error message otherwise
      default:
      fprintf(stderr, "Error: unknown option '%s'\n", optarg);
      return 1;
    }
  }

  // Shift pointers so that we can iterate through the files
  argc -= optind;
  argv += optind;

  // Add input string to file(s) appropriately
  while (fgets(input_string, 512, stdin)) {
    for (i=0; i<argc; i++) {
      // Open each file with the appropriate mode
      if (!appendMode) {
        outFile = fopen(argv[i], "w");
      }
      else {
        outFile = fopen(argv[i], "a");
      }
      // Write string to file
      fputs(input_string, outFile);
      fclose(outFile);
    }
    // Write string to standard out
    fprintf(stdout, "%s", input_string);
  }

  return 0;
}
