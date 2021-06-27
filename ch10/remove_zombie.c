/*
 * @Author: dylan
 * @Date: 2021-06-13 12:53:26
 * @LastEditTime: 2021-06-26 17:30:33
 * @LastEditors: dylan
 * @Description: use signal techniques to
 *               remove zombie processes
 * @FilePath: /TCPIP_NetworkProgramming/ch10/remove_zombie.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

/*
strcut sigaction {
    void (*sa_handler)(int);
    sigset_t sa_mask;
    int sa_flags;
}
*/

void read_childproc(int sig)
{
    int status;
    pid_t pid;
    pid = waitpid(-1, &status, WNOHANG);
    if (WIFEXITED(status) == true) {
        printf("removed proc id: %d\n", pid);
        printf("child sent: %d\n", WEXITSTATUS(status));
    }
}

int main(int argc, char *argv[])
{
    pid_t pid;
    struct sigaction act;
    act.sa_handler = read_childproc;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    // the function will be triggered
    // when the child process end
    sigaction(SIGCHLD, &act, 0);

    pid = fork();
    if (pid == 0) {
        puts("child process here");
        sleep(10);
        return 3;
    } else {
        printf("child process id: %d\n", pid);
        pid = fork();
        if (pid == 0) {
            puts("child process here");
            sleep(10);
            return 4;
        } else {
            printf("child process id: %d\n", pid);
            for (int i = 0; i < 5; i++) {
                puts("wait...");
                sleep(5);
            }
        }
    }

    return 0;
}