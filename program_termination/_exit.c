#include <stdio.h>
// for _exit
#include <unistd.h>

int main() {

    printf("clean line buffer\n");
    printf("line buffer");
    _exit(0);

    return 0;
}
