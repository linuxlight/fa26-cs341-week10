#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

// discuss in group, for the solution.
// don't reveal the answer

void pipe_size(int *fds)
{
    int pipe_sz = fcntl(fds[0], F_GETPIPE_SZ);
    printf("pipe size: %d\n", pipe_sz);
}

int main(int argc, char *argv[])
{
    int fds[2];
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <bytes>\n", argv[0]);
        return 1;
    }
    int n = atoi(argv[1]);           /* bytes to send */
    pipe(fds);
    pipe_size(fds);
    char *buf = calloc(n, 1);
    write(fds[1], buf, n);           /* write everything first... */
    ssize_t got = read(fds[0], buf, n);   /* ...then read it back */
    printf("sent %d, received %ld\n", n, got);
    free(buf);
    return 0;
}
