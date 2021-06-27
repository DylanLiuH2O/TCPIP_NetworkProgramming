/*
 * @Author: dylan
 * @Date: 2021-06-13 20:01:47
 * @LastEditTime: 2021-06-27 17:02:27
 * @LastEditors: dylan
 * @Description: two-way communication using one pipe
 * @FilePath: /TCPIP_NetworkProgramming/ch11/pipe2.c
 */
#include <stdio.h>
#include <unistd.h>

#define BUF_SIZE 50

int main(int argc, char *argv[])
{
    int fds[2];
    char str1[] = "Who are you?";
    char str2[] = "I am you father.";
    char buf[BUF_SIZE];
    pid_t pid;

    pipe(fds);
    pid = fork();
    if (pid == 0) {
        write(fds[1], str1, sizeof(str1));
        sleep(2);   //remove this will cause problem
        read(fds[0], buf, BUF_SIZE);
        printf("child proc output: %s\n", buf);
    } else {
        read(fds[0], buf, BUF_SIZE);
        printf("parent proc output: %s\n", buf);
        write(fds[1], str2, sizeof(str2));
        sleep(3);
    }

    return 0;
}