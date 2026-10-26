#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <wait.h>

// hello from chhello from child 2

int main(void)
{
    int fds[2];
    pipe(fds);
    for (int k = 1; k <= 3; k++) {
        if (fork() == 0) {           /* three writers */
            close(fds[0]);
            char line[32];
            snprintf(line, sizeof line, "hello from child %d\n", k);
            for (int i = 0; i < 3; i++) {
                write(fds[1], line, strlen(line));
                usleep(1000);        /* pretend to work */
            }
            return 0;
        }
    }
    close(fds[1]);                   /* parent: the one reader */
    char buf[256]; ssize_t n;
    while ((n = read(fds[0], buf, sizeof buf)) > 0)
        write(1, buf, n);
    while (wait(NULL) > 0) ;
    printf("done\n");
}
