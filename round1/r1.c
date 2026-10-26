#include <stdio.h>
#include <unistd.h>
#include <wait.h>

int main(void)
{
    int fds[2];
    pipe(fds);
    if (fork() == 0) {               /* child: reader */
        close(fds[1]);
        char buf[64]; ssize_t n, total = 0;
        while ((n = read(fds[0], buf, sizeof buf)) > 0)
            total += n;
        printf("child read %zd bytes\n", total);
        return 0;
    }
    write(fds[1], "hello\n", 6);     /* parent: writer */
    waitpid(-1, NULL, 0);
    printf("Round 1 done\n");
    return 0;
}
