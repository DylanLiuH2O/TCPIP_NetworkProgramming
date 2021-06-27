/*
 * @Author: dylan
 * @Date: 2021-06-24 22:57:58
 * @LastEditTime: 2021-06-26 14:15:39
 * @LastEditors: dylan
 * @Description: a tcp client
 * @FilePath: /TCPIP_NetworkProgramming/ch2/tcp_client.c
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
    int str_len = 0;
    int read_len = 0;
    int idx = 0;
    int count = 0;
    while ((read_len = read(serv_sock, &message[idx++], sizeof(message) - 1))) {
        if (read_len == -1) {
            error_handling("read() error");
        }
        count++;
        str_len += read_len;
    }

    printf("Message from server: %s\n", message);
    printf("Function read call count: %d, idx: %d, length: %d\n", count, idx, str_len);

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