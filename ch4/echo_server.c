/*
 * @Author: dylan
 * @Date: 2021-06-24 22:57:58
 * @LastEditTime: 2021-06-26 14:25:01
 * @LastEditors: dylan
 * @Description: a basic echo-server(only support processing request one by one)
 * @FilePath: /TCPIP_NetworkProgramming/ch4/echo_server.c
 */
#include <stdio.h>
#include <stdlib.h>
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
    int clnt_sock;
    int message[BUF_SIZE];

    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    socklen_t clnt_adr_sz;

    /* register socket */
    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1) {
        error_handling("sock() error");
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

    /* start to listen request */
    if (listen(serv_sock, 5) == -1)  {
        error_handling("listen() error");
    }

    /* receive msg from client then send it back */
    for (int i = 0; i < 5; i++) {
        clnt_adr_sz = sizeof(clnt_addr);
        clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_adr_sz);
        if (clnt_sock == -1) {
            error_handling("accept() error");
        } else {
            printf("Connected client %d\n", i+1);
        }

        int str_len = 0;
        while ((str_len = read(clnt_sock, message, BUF_SIZE)) != 0) {
            //printf("recv_len: %d\n", str_len);
            write(clnt_sock, message, str_len);
        }
        close(clnt_sock);
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