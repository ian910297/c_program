#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define DIRECT_EXIT

void func1() {
    printf("func1 is called\n");
}

void func2() {
    printf("func2 is called\n");
}

int main() {

    printf("main function\n");
    // Register function to a list, and then function in the list would 
    // work as stack. Those function would execute in an order Last In Fast Out(LIFO)
    atexit(func1);
    atexit(func2);

#ifdef DIRECT_EXIT
    _exit(0);
#elif
    // If the program doesn't exit instantly, the exit list would execute.
    exit(0);
#endif

    return 0;
}
