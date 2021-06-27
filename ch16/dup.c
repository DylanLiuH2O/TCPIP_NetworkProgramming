/*
 * @Author: dylan
 * @Date: 2021-06-20 09:08:40
 * @LastEditTime: 2021-06-27 15:15:21
 * @LastEditors: dylan
 * @Description: call dup to duplicate
 *               file descriptor
 * @FilePath: /TCPIP_NetworkProgramming/ch16/dup.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUF_SIZE 1000

void error_handling(char *message);

int main(int argc, char *argv[])
{
    int cfd1;
    int cfd2;
    char str1[] = "message 1\n";
    char str2[] = "message 2\n";

    cfd1 = dup(1);
    if (cfd1 == -1) {
        error_handling("dup() error");
    }
    cfd2 = dup2(cfd1, 7);
    if (cfd2 == -1) {
        error_handling("dup2() error");
    }

    printf("cfd1: %d, cfd2: %d\n", cfd1, cfd2);
    write(cfd1, str1, strlen(str1));
    write(cfd2, str2, strlen(str2));

    close(cfd1);
    close(cfd2);
    write(1, str1, sizeof(str1));
    close(1);
    write(1, str2, sizeof(str2));

    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
