/*
 * @Author: dylan
 * @Date: 2021-06-11 22:13:07
 * @LastEditTime: 2021-06-26 16:56:32
 * @LastEditors: dylan
 * @Description: call setsockopt() to turn off time-wait
 * @FilePath: /TCPIP_NetworkProgramming/ch9/reuseadr_eserver.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 50
#define SET_REUSEADDR true //set it true or false to compare output 

void error_handling(char *message);

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("usage: %s <port>\n", argv[0]);
        exit(1);
    }

    int serv_sock;
    int clnt_sock;
    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_sz;

    char message[BUF_SIZE];

    /* register TCP socket */
    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1) {
        error_handling("socket() error");
    }

#if SET_REUSEADDR
    int option = 1; //notice that option cannot be 'bool'
    // printf("%d\n", (int)option);
    socklen_t optlen = sizeof(option);
    int status = setsockopt(serv_sock, SOL_SOCKET, SO_REUSEADDR, (void*)&option, optlen);
    if (status != 0) {
        error_handling("setsockopt() error");
    }
#endif

    /* initialize serv_addr */
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family      = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port        = htons(atoi(argv[1]));

    /* bind serv_sock to serv_addr */
    if (bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) {
        error_handling("bind() error");
    }

    /* start to listen requests */
    if (listen(serv_sock, 5) == -1) {
        error_handling("listen() error");
    }

    /* accept request */
    clnt_addr_sz = sizeof(clnt_sock);
    clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_sz);
    if (clnt_sock == -1) {
        error_handling("clnt_sock() error");
    }

    /* transmit data */
    int str_len = 0;
    while ((str_len = read(clnt_sock, message, sizeof(message))) != 0) {
        write(clnt_sock, message, str_len);
        write(1, message, str_len);     //write message to stdout
    }

    /* release resources */
    close(clnt_sock);
    close(serv_sock);

    return 0;
}

void error_handling(char *message)
{
    fputs(message, stdout);
    fputc('\n', stdout);
    exit(1);
}