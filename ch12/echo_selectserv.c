/*
 * @Author: dylan
 * @Date: 2021-06-18 13:16:26
 * @LastEditTime: 2021-06-27 00:17:41
 * @LastEditors: dylan
 * @Description: echo server using select()
 * @FilePath: /TCPIP_NetworkProgramming/ch12/echo_selectserv.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/select.h>

#define BUF_SIZE 50

void error_handling(char *message);
int max(int a, int b);

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
    socklen_t addr_sz;
    char buf[BUF_SIZE];

    /* register sock */
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
    addr_sz = sizeof(serv_addr);
    if (bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) {
        error_handling("bind() error");
    }

    /* start to listen request */
    if (listen(serv_sock, 5) == -1) {
        error_handling("listen() error");
    }

    fd_set init_set;
    fd_set res_set;
    struct timeval timeout;
    int res;
    int maxfd = -1;

    FD_ZERO(&init_set);
    FD_SET(serv_sock, &init_set);
    maxfd = serv_sock;

    while (true) {
        res_set = init_set;
        timeout.tv_sec  = 5;
        timeout.tv_usec = 5000;

        //number of fd start from zero, so the actual number of 
        //descriptors is maxfd+1
        res = select(maxfd+1, &res_set, 0, 0, &timeout);
        if (res == -1) {
            error_handling("select() error");
        }
        if (res == 0) {
            continue;
        }

        for (int i = 0; i <= maxfd; i++) {
            if (FD_ISSET(i, &res_set)) {
                if (i == serv_sock) {
                    addr_sz = sizeof(clnt_addr);
                    clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &addr_sz);
                    if (clnt_sock == -1) {
                        continue;
                    }
                    puts("new client connected");

                    maxfd = max(maxfd, clnt_sock);
                    FD_SET(clnt_sock, &init_set);
                } else {
                    int str_len = read(i, buf, BUF_SIZE);
                    if (str_len == 0) {
                        FD_CLR(i, &init_set);
                        close(i);
                    } else {
                        write(i, buf, str_len); //send back to client
                        write(1, buf, str_len); //display data
                    }
                    // the previous practice
                    // while ((str_len = read(i, buf, BUF_SIZE)) != 0) {
                    //     write(i, buf, str_len); //send back to client
                    //     write(1, buf, str_len); //display data
                    // }
                }
            }
        }
    }
    close(serv_sock);

    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

int max(int a, int b)
{
    return (a >= b) ? a : b; 
}