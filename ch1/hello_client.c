/*
 * @Author: dylan
 * @Date: 2021-06-05 14:08:14
 * @LastEditTime: 2021-06-26 14:15:10
 * @LastEditors: dylan
 * @Description: a simple C/S program
 * @FilePath: /TCPIP_NetworkProgramming/ch1/hello_client.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

void error_handling(char *message);

int main(int argc, char *argv[])
{
    if (argc != 3) {
        printf("usage: %s <IP> <port>\n", argv[0]);
        exit(1);
    }

    int serv_sock;
    struct sockaddr_in serv_addr;
    char message[50];

    /* register socket */
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

    /* receive message from server */
    int str_len = read(serv_sock, message, sizeof(message) - 1);
    if (str_len == -1) {
        error_handling("read() error");
    }

    printf("Message from server: %s\n", message);

    /* release resource */
    close(serv_sock);

    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}