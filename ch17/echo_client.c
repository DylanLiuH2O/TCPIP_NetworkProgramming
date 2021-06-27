/*
 * @Author: dylan
 * @Date: 2021-06-13 13:45:29
 * @LastEditTime: 2021-06-27 15:25:45
 * @LastEditors: dylan
 * @Description: the same as ch5/echo_client2.c
 * @FilePath: /TCPIP_NetworkProgramming/ch17/echo_client.c
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
    if (argc != 3) {
        printf("usage: %s <ip> <port>\n", argv[0]);
        exit(1);
    }

    int serv_sock;
    struct sockaddr_in serv_addr;

    char message[BUF_SIZE];

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

    puts("Connected......");

    /* get msg from stdin and send it to server, then receive msg from server */
    while (true) {
        fputs("Input message(q to quit): ", stdout);
        fgets(message, BUF_SIZE, stdin);
        
        if (!strcmp(message, "q\n") || !strcmp(message, "Q\n")) {
            break;
        }

        /* more perfect practice of receiving byte stream message */
        int str_len = write(serv_sock, message, strlen(message));
        int recv_len = 0;
        while (recv_len < str_len) {
            int recv_cnt = read(serv_sock, &message[recv_len], BUF_SIZE-1);
            if (recv_cnt == -1) {
                error_handling("read() error");
            }
            recv_len += recv_cnt;
        }
        message[recv_len] = '\0';
        printf("Message from server(len %d): %s", str_len, message);
    }

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