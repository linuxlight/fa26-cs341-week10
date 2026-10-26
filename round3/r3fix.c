#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <signal.h>

static void sigpipe_handler(int signum)
{
    perror("write failed");
}

int main(void)
{
    int fds[2];
    signal(SIGPIPE, sigpipe_handler);
    pipe(fds);
    if (fork() == 0) {               /* child: reads once, then quits */
        close(fds[1]);
        char buf[16];
        read(fds[0], buf, sizeof buf);
        return 0;
    }
    close(fds[0]);
    for (int i = 0; i < 100000; i++)
        write(fds[1], "line\n", 5);
    close(fds[1]);
    waitpid(-1, NULL, 0);
    printf("Round 3 done\n");
    return 0;
}
