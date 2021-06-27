/*
 * @Author: dylan
 * @Date: 2021-06-13 14:48:21
 * @LastEditTime: 2021-06-26 20:14:34
 * @LastEditors: dylan
 * @Description: the same as ch10/echo_mpclient.c
 * @FilePath: /TCPIP_NetworkProgramming/ch11/echo_mpclient.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 50

void error_handling(char *message);
void read_routine(int serv_sock, char *buf);
void write_routine(int serv_sock, char *buf);

int main(int argc, char *argv[])
{
    if (argc != 3) {
        printf("usage: %s <ip> <port>\n", argv[0]);
        exit(1);
    }

    int serv_sock;
    struct sockaddr_in serv_addr;
    pid_t pid;
    char buf[BUF_SIZE];

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
    puts("connected...");

    pid = fork();
    if (pid == 0) {
        write_routine(serv_sock, buf);
    } else {
        read_routine(serv_sock, buf);
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

void read_routine(int serv_sock, char *buf)
{
    while (true) {
        int str_len = read(serv_sock, buf, BUF_SIZE);
        if (str_len == 0) {
            return;
        }
        buf[str_len] = '\0';
        printf("Message from server: %s", buf);
    }
}

void write_routine(int serv_sock, char *buf)
{
    while (true) {
        /* if use the statement below, 
           it will print every time whether it received msg or not. */
        //printf("Input message(q to quit): ");
        fgets(buf, BUF_SIZE, stdin);
        if (!strcmp(buf, "q\n") || !strcmp(buf, "Q\n")) {
            shutdown(serv_sock, SHUT_WR);
            return;
        }
        write(serv_sock, buf, strlen(buf));
        // printf("%d\n", send_len);
    }
}