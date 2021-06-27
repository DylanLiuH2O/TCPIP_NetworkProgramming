/*
 * @Author: dylan
 * @Date: 2021-06-18 12:12:38
 * @LastEditTime: 2021-06-27 00:16:23
 * @LastEditors: dylan
 * @Description: call select() to monitor
 *               the standard input
 * @FilePath: /TCPIP_NetworkProgramming/ch12/select.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/select.h>

#define BUF_SIZE 30

void error_handling(char *message);

int main(int argc, char *argv[])
{
    fd_set reads;
    fd_set temps;
    int result;
    int str_len;

    char buf[BUF_SIZE];
    struct timeval timeout;

    FD_ZERO(&reads);
    FD_SET(0, &reads);

    while (true) {
        temps = reads;
        timeout.tv_sec  = 5;
        timeout.tv_usec = 0;
        result = select(1, &temps, 0, 0, &timeout);
        if (result == -1) {
            error_handling("select() error");
        } else if (result == 0) {
            puts("time-out!");
        } else {
            if (FD_ISSET(0, &temps)) {
                str_len = read(0, buf, BUF_SIZE);
                buf[str_len] = 0;
                printf("message from console: %s", buf);
            }
        }
    }

    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}