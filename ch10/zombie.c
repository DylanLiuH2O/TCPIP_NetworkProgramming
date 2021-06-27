/*
 * @Author: dylan
 * @Date: 2021-06-12 23:19:47
 * @LastEditTime: 2021-06-26 17:36:09
 * @LastEditors: dylan
 * @Description: test zombie process
 *               (run this then use 'ps -ef' to look)
 * @FilePath: /TCPIP_NetworkProgramming/ch10/zombie.c
 */
#include <stdio.h>
#include <unistd.h>

int main(int argc , char *argv[])
{
    pid_t pid;

    pid = fork();

    if (pid == 0) {
        printf("child process here\n");
    } else {
        printf("child process id: %d\n", pid);
        sleep(30);
    }

    if (pid == 0) {
        puts("end child process");
    } else {
        puts("end parent process");
    }

    return 0;
}
