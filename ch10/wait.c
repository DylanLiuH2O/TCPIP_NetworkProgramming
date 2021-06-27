/*
 * @Author: dylan
 * @Date: 2021-06-12 23:25:32
 * @LastEditTime: 2021-06-26 17:31:00
 * @LastEditors: dylan
 * @Description: call wait() which is blocking,
 *               to kill zombie child proc
 * @FilePath: /TCPIP_NetworkProgramming/ch10/wait.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int status;
    pid_t pid;

    pid = fork();

    if (pid == 0) {
        return 2;
    } else {
        printf("child id: %d\n", pid);
        pid = fork();
        if (pid == 0) {
            return 3;
        } else {
            printf("child id: %d\n", pid);
            wait(&status);
            if (WIFEXITED(status) == true) {
                printf("child send one: %d\n", WEXITSTATUS(status));
            }

            wait(&status);
            if (WIFEXITED(status) == true) {
                printf("child send two: %d\n", WEXITSTATUS(status));
            }
            sleep(10);
        }
    }

    return 0;
}
