/*
 * @Author: dylan
 * @Date: 2021-06-13 00:27:44
 * @LastEditTime: 2021-06-26 17:31:07
 * @LastEditors: dylan
 * @Description: call waitpid() which is non-blocking,
 *               to kill zombie proc
 * @FilePath: /TCPIP_NetworkProgramming/ch10/waitpid.c
 */
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int status;
    pid_t pid;

    pid = fork();
    if (pid == 0) {
        sleep(10);
        return 2;
    } else {
        while (!waitpid(-1, &status, WNOHANG)) {
            sleep(2);
            puts("sleep 2 secs");
        }
        if (WIFEXITED(status)) {
            printf("child send %d\n", WEXITSTATUS(status));
        }
    }

    return 0;
}