/*
 * @Author: dylan
 * @Date: 2021-06-13 18:52:23
 * @LastEditTime: 2021-06-26 21:28:23
 * @LastEditors: dylan
 * @Description: call pipe() to create pipes
 * @FilePath: /TCPIP_NetworkProgramming/ch11/pipe1.c
 */
#include <stdio.h>
#include <unistd.h>

#define BUF_SIZE 20

int main(int argc, char *argv[])
{
    int fds[2];
    char str[] = "Who are you ?";
    char buf[BUF_SIZE];
    pid_t pid;

    pipe(fds);
    pid = fork();
    if (pid == 0) {
        write(fds[1], str, sizeof(str));
    } else {
        read(fds[0], buf, BUF_SIZE);
        puts(buf);
    }

    return 0;
}