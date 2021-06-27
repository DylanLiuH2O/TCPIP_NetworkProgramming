/*
 * @Author: dylan
 * @Date: 2021-06-18 15:32:43
 * @LastEditTime: 2021-06-27 01:37:28
 * @LastEditors: dylan
 * @Description: call send() to send 
 *               urgent message
 * @FilePath: /TCPIP_NetworkProgramming/ch13/oob_send.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define BUF_SIZE 100

void error_handling(char *message);

int main(int argc, char *argv[])
{
    if (argc != 3) {
        printf("usage: %s <ip> <port>\n", argv[0]);
        exit(1);
    }

    int recv_sock;
    struct sockaddr_in recv_addr;

    /* register socket */
    recv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (recv_sock == -1) {
        error_handling("socket() error");
    }

    /* initialize recv_addr */
    memset(&recv_addr, 0, sizeof(recv_addr));
    recv_addr.sin_family      = AF_INET;
    recv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    recv_addr.sin_port        = htons(atoi(argv[2]));

    /* connect to receiver */
    if (connect(recv_sock , (struct sockaddr*)&recv_addr, sizeof(recv_addr)) == -1) {
        error_handling("connect() error");
    }

    write(recv_sock, "first message\n", strlen("first message\n"));
    send(recv_sock, "first urgent message", strlen("first urgent message"), MSG_OOB);
    write(recv_sock, "second message\n", strlen("second message\n"));
    send(recv_sock, "second urgent message", strlen("second urgent message"), MSG_OOB);

    /* release resource */
    close(recv_sock);

    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}