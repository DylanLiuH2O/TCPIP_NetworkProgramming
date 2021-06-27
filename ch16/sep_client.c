/*
 * @Author: dylan
 * @Date: 2021-06-20 08:44:19
 * @LastEditTime: 2021-06-27 15:15:28
 * @LastEditors: dylan
 * @Description: echo client using standard
 *               I/O functions
 * @FilePath: /TCPIP_NetworkProgramming/ch16/sep_client.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1000

void error_handling(char *message);

int main(int argc, char *argv[])
{
    if (argc != 3) {
        printf("usage: %s <ip> <port>\n", argv[0]);
        exit(1);
    }

    int serv_sock;
    struct sockaddr_in serv_addr;
    char buf[BUF_SIZE];
    FILE *readfp  = NULL;
    FILE *writefp = NULL;

    /* register serv_sock */
    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1) {
        error_handling("socket() error");
    }

    /* initialize serv_addr */
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family      = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port        = htons(atoi(argv[2]));

    /* connect to server */
    if (connect(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) {
        error_handling("connect() error");
    }

    /* convert descriptor to FILE pointer */
    readfp  = fdopen(serv_sock, "r");
    writefp = fdopen(serv_sock, "w");
    if (readfp == NULL || writefp == NULL) {
        error_handling("fdopen() error");
    }

    while (true) {
        if (fgets(buf, sizeof(buf), readfp) == NULL) {
            break;
        }
        fputs(buf, stdout);
        fflush(stdout);
    }

    fputs("from client: good bye!\n", writefp);
    fflush(writefp);
    fclose(writefp);
    fclose(readfp);

    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}