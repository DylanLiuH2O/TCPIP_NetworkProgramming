/*
 * @Author: dylan
 * @Date: 2021-06-24 22:57:58
 * @LastEditTime: 2021-06-26 15:05:19
 * @LastEditors: dylan
 * @Description: UDP echo-server
 * @FilePath: /TCPIP_NetworkProgramming/ch6/uecho_server.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 100

void error_handling(char *message);

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("usage: %s <port>\n", argv[0]);
        exit(1);
    }

    int serv_sock;
    socklen_t clnt_addr_sz;
    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;

    char message[BUF_SIZE];

    /* register socket */
    serv_sock = socket(PF_INET, SOCK_DGRAM, 0);
    if (serv_sock == -1) {
        error_handling("socket() error");
    }

    /* initialize serv_addr */
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family      = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port        = htons(atoi(argv[1]));

    /* bind serv_sock to serv_addr */
    if (bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) {
        error_handling("bind() error");
    }

    /* receive UDP datagram from socket then send back */
    while (true) {
        clnt_addr_sz = sizeof(clnt_addr);
        int str_len = recvfrom(serv_sock, message, BUF_SIZE, 0, (struct sockaddr*)&clnt_addr, &clnt_addr_sz);
        sendto(serv_sock, message, str_len, 0, (struct sockaddr*)&clnt_addr, clnt_addr_sz);
    }

    /* receive resource */
    close(serv_sock);

    return 0;
}

void error_handling(char *message)
{
    fputs(message, stdout);
    fputc('\n', stdout);
    exit(1);
}