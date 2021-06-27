/*
 * @Author: dylan
 * @Date: 2021-06-12 13:34:01
 * @LastEditTime: 2021-06-26 17:30:22
 * @LastEditors: dylan
 * @Description: call fork() to verify the memory structure
 * @FilePath: /TCPIP_NetworkProgramming/ch10/fork.c
 */
#include <stdio.h>
#include <unistd.h>

int gval = 10;

int main(int argc, char *argv[])
{
    pid_t pid;
    int lval = 20;

    gval++;
    lval += 5;
    
    pid = fork();
    if (pid == 0) {
        gval += 2;
        lval += 2;
    } else {
        gval -= 2;
        lval -= 2;
    }

    if (pid == 0) {
        printf("child process: [%d, %d]\n", gval, lval);
    } else {
        printf("parent process: [%d, %d]\n", gval, lval);
    }

    return 0;
}
