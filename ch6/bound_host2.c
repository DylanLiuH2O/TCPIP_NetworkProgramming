/*
 * @Author: dylan
 * @Date: 2021-06-24 22:57:58
 * @LastEditTime: 2021-06-26 14:50:04
 * @LastEditors: dylan
 * @Description: UDP datagram boundary test(client)
 * @FilePath: /TCPIP_NetworkProgramming/ch6/bound_host2.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 30

void error_handling(char *message);

int main(int argc, char *argv[])
{
    if (argc != 3) {
        printf("usage: %s <ip> <port>\n", argv[0]);
        exit(1);
    }

    int local_sock;
    struct sockaddr_in serv_addr;

    char msg1[] = "Hi!";
    char msg2[] = "I'm another UDP host!";
    char msg3[] = "Nice to meet you";

    /* register socket */
    local_sock = socket(PF_INET, SOCK_DGRAM, 0);
    if  (local_sock == -1) {
        error_handling("socket() error");
    }

    /* initialize serv_addr */
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family      = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port        = htons(atoi(argv[2]));

    /* send messages */
    sendto(local_sock, msg1, sizeof(msg1), 0,
            (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    sendto(local_sock, msg2, sizeof(msg2), 0,
            (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    sendto(local_sock, msg3, sizeof(msg3), 0,
            (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    /* release resource */
    close(local_sock);

    return 0;
}

void error_handling(char *message)
{
    fputs(message, stdout);
    fputc('\n', stdout);
    exit(1);
}