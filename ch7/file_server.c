/*
 * @Author: dylan
 * @Date: 2021-06-09 18:55:42
 * @LastEditTime: 2021-06-26 16:08:02
 * @LastEditors: dylan
 * @Description: server - file transfer program based on half-close
 * @FilePath: /TCPIP_NetworkProgramming/ch7/file_server.c
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
    char buff[BUF_SIZE];

    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;

    /* open file */
    FILE *fp;
    fp = fopen("file_server.c", "rb");
    if (fp == NULL) {
        error_handling("fopen() error");
    }

    /* register socket */
    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
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

    /* listen request from clients */
    if (listen(serv_sock, 5) == -1) {
        error_handling("listen() error");
    }
    puts("server listening...");

    /* accept request */
    socklen_t clnt_addr_sz = sizeof(clnt_addr);
    clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_sz);
    if (clnt_sock == -1) {
        error_handling("accept() error");
    }
    puts("client connected");

    /* transmit data */
    while (1) {
        int read_cnt = fread((void*)buff, 1, BUF_SIZE, fp);
        if (read_cnt < BUF_SIZE) {
            write(clnt_sock, buff, read_cnt);
            break;
        }
        write(clnt_sock, buff, BUF_SIZE);
    }

    /* shutdown */
    shutdown(clnt_sock, SHUT_WR);
    read(clnt_sock, buff, BUF_SIZE);
    printf("Message from client: %s\n", buff);

    /* release resources */
    fclose(fp);
    close(serv_sock);
    close(clnt_sock);

    return 0;
}

void error_handling(char *message)
{
    fputs(message, stdout);
    fputc('\n', stdout);
    exit(1);
}