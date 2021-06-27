/*
 * @Author: dylan
 * @Date: 2021-06-19 18:11:30
 * @LastEditTime: 2021-06-27 15:06:30
 * @LastEditors: dylan
 * @Description: convert FILE pointer
 *               to descriptor
 * @FilePath: /TCPIP_NetworkProgramming/ch15/todes.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

void error_handling(char *message);

int main(void)
{
    int fd;

    fd = open("data.dat", O_WRONLY | O_CREAT | O_TRUNC);
    if (fd == -1) {
        error_handling("open() error");
    }

    printf("first file descriptor: %d\n", fd);
    FILE *fp = fdopen(fd, "w");
    fputs("convert successfully: %d\n", fp);
    printf("second file descriptor: %d\n", fileno(fp));
    fclose(fp);

    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}