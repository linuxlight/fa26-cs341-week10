#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

int main(void)
{
    int fds[2];
    pipe(fds);
    if (fork() == 0) {               /* child: becomes wc */
        dup2(fds[0], 0);             /* stdin = read end */
        close(fds[0]);
        execlp("wc", "wc", "-c", NULL);
        exit(1);
    }
    close(fds[0]);
    write(fds[1], "hello\n", 6);
    close(fds[1]);
    waitpid(-1, NULL, 0);
    printf("Round 2 done\n");
    return 0;
}
