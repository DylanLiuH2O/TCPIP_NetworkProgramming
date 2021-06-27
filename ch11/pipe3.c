/*
 * @Author: dylan
 * @Date: 2021-06-13 21:25:13
 * @LastEditTime: 2021-06-26 18:12:35
 * @LastEditors: dylan
 * @Description: two-way communication using two pipes
 * @FilePath: /TCPIP_NetworkProgramming/ch11/pipe3.c
 */
#include <stdio.h>
#include <unistd.h>

#define BUF_SIZE 50

int main(int argc, char *argv[])
{
    int fds1[2];
    int fds2[2];
    char str1[] = "Who are you?";
    char str2[] = "I am your father.";
    char buf[BUF_SIZE];

    pid_t pid;

    /* create pipes */
    pipe(fds1);
    pipe(fds2);

    /* fork child proc */
    pid = fork();
    if (pid == 0) {
        write(fds1[1], str1, sizeof(str1));
        read(fds2[0], buf, BUF_SIZE);
        printf("child proc output: %s\n", buf);
    } else {
        read(fds1[0], buf, BUF_SIZE);
        printf("parent proc output: %s\n", buf);
        write(fds2[1], str2, sizeof(str2));
        sleep(1);   //prevent command popping up too early
    }

    return 0;
}