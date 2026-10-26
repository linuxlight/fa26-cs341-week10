#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <wait.h>

int main(void)
{
    int fds[2];
    pipe(fds);
    if (fork() == 0) {               /* child: reader */
        close(fds[0]);
        char buf[64]; ssize_t n, total = 0;
        while ((n = read(fds[1], buf, sizeof buf)) > 0)
            total += n;
        printf("child read %zd bytes\n", total);
        return 0;
    }
    close(fds[1]);                   /* parent: writer */
    write(fds[0], "hello\n", 6);
    close(fds[0]);
    waitpid(-1, NULL, 0);
    printf("done\n");
}
