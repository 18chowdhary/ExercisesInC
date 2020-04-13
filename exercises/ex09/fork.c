/* Example code for Exercises in C.

Copyright 2016 Allen B. Downey
License: MIT License https://opensource.org/licenses/MIT


Answer to Part 2 of fork:
In order to test whether the heap, globals, and stack are shared by the child
process, I dynamically allocated an integer on the heap in the parent, defined
a string literal at the top of my code, and declared two local variables,
one in the parent code and one in the child. Then I printed out the values
and addresses of all of these variables. I observed that the dynamically
allocated integer had the same address for all children. I incremented the
dynamically allocated integer whenever I created a child, and observed
that the integer's value was updated for the child as well, further
confirming that child and parent processes share the same heap. Similarly, I
observed that the string literal was always the value in the same location
for each child and the parent, confirming that child and parent proesses share
the same globals section. Finally, I noticed that the local variables were in
different locations in the stack, confirming that they have different stacks.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/types.h>
#include <wait.h>


// errno is an external global variable that contains
// error information
extern int errno;
char* literal = "Hello World";

// get_seconds returns the number of seconds since the
// beginning of the day, with microsecond precision
double get_seconds() {
    struct timeval tv[1];

    gettimeofday(tv, NULL);
    return tv->tv_sec + tv->tv_usec / 1e6;
}


void child_code(int i, int* dynamic)
{
    sleep(i);
    printf("Hello from child %d.\n", i);
    int number = 5;

    printf("Child sees literal as %s\n", literal);
    printf("Child sees dynamically allocated number as %d and it is at address %p\n", *dynamic, dynamic);
    printf("Child sees stack-allocated number as %d and it is at address %p\n", number, &number);
}

// main takes two parameters: argc is the number of command-line
// arguments; argv is an array of strings containing the command
// line arguments
int main(int argc, char *argv[])
{
    int status;
    pid_t pid;
    double start, stop;
    int i, num_children;

    int* dynamic = malloc(sizeof(int*));
    *dynamic = 1;
    int number = 5;

    // the first command-line argument is the name of the executable.
    // if there is a second, it is the number of children to create.
    if (argc == 2) {
        num_children = atoi(argv[1]);
    } else {
        num_children = 1;
    }

    // get the start time
    start = get_seconds();

    for (i=0; i<num_children; i++) {
        *dynamic = *dynamic + 1;
        // create a child process
        printf("Creating child %d.\n", i);

        pid = fork();

        /* check for an error */
        if (pid == -1) {
            fprintf(stderr, "fork failed: %s\n", strerror(errno));
            perror(argv[0]);
            exit(1);
        }

        /* see if we're the parent or the child */
        if (pid == 0) {
            child_code(i, dynamic);
            exit(i);
        }
    }

    /* parent continues */
    printf("Hello from the parent.\n");

    for (i=0; i<num_children; i++) {
        pid = wait(&status);

        if (pid == -1) {
            fprintf(stderr, "wait failed: %s\n", strerror(errno));
            perror(argv[0]);
            exit(1);
        }

        // check the exit status of the child
        status = WEXITSTATUS(status);
        printf("Child %d exited with error code %d.\n", pid, status);
        printf("Parent sees literal as %s\n", literal);
        printf("Parent sees dynamically allocated number as %d and it is at address %p\n", *dynamic, dynamic);
        printf("Parent sees stack-allocated number as %d and it is at address %p\n", number, &number);
    }

    // compute the elapsed time
    stop = get_seconds();
    printf("Elapsed time = %f seconds.\n", stop - start);

    exit(0);
}
