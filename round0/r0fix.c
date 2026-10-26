#include <stdio.h>
#include <unistd.h>
#include <wait.h>

int main(void)
{
    printf("hello");
    fflush(stdout);
    if (fork() == 0)
        return 0;                    /* child does nothing */
    wait(NULL);
}
