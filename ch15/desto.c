/*
 * @Author: dylan
 * @Date: 2021-06-19 17:51:01
 * @LastEditTime: 2021-06-27 15:05:53
 * @LastEditors: dylan
 * @Description: convert descriptor to
 *               FILE pointer
 * @FilePath: /TCPIP_NetworkProgramming/ch15/desto.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

void error_handling(char *message);

int main(void)
{
    FILE *fp = NULL;

    int fd = open("data2.txt", O_WRONLY | O_CREAT | O_TRUNC);
    if (fd == -1) {
        error_handling("open() error");
    }

    fp = fdopen(fd, "w");
    puts("convert successfully");
    fclose(fp);

    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}