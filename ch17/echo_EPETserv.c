/*
 * @Author: dylan
 * @Date: 2021-06-20 11:49:48
 * @LastEditTime: 2021-06-27 17:03:50
 * @LastEditors: dylan
 * @Description: echo server using epoll(),
 *               verify Edge Trigger
 * @FilePath: /TCPIP_NetworkProgramming/ch17/echo_EPETserv.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <errno.h>

#define BUF_SIZE 4
#define EPOLL_SIZE 50

void error_handling(char *message);
void setnonblockingmode(int fd);

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

    struct epoll_event ep_events[EPOLL_SIZE];
    struct epoll_event event;
    int epfd;
    int event_cnt;

    /* create epoll fd and add serv_sock to it */
    epfd = epoll_create(EPOLL_SIZE);
    event.events  = EPOLLIN;
    event.data.fd = serv_sock;
    epoll_ctl(epfd, EPOLL_CTL_ADD, serv_sock, &event);

    while (true) {
        event_cnt = epoll_wait(epfd, ep_events, EPOLL_SIZE, -1);
        if (event_cnt == -1) {
            error_handling("epoll_wait() error");
        }

        puts("return epoll_wait()");
        for (int i = 0; i < event_cnt; i++) {
            if (ep_events[i].data.fd == serv_sock) {
                addr_sz = sizeof(clnt_addr);
                clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &addr_sz);
                if (clnt_sock == -1) {
                    continue;
                }
                setnonblockingmode(clnt_sock);

                event.events  = EPOLLIN | EPOLLET;
                event.data.fd = clnt_sock;
                epoll_ctl(epfd, EPOLL_CTL_ADD, clnt_sock, &event);

                printf("new client connected: %d\n", clnt_sock);
            } else {
                while (true) {
                    int str_len = read(ep_events[i].data.fd, buf, BUF_SIZE);
                    if (str_len == 0) {
                        epoll_ctl(epfd, EPOLL_CTL_DEL, ep_events[i].data.fd, NULL);
                        close(ep_events[i].data.fd);
                        printf("close client: %d\n", ep_events[i].data.fd);
                        break;
                    } else if (str_len < 0) {   //read finish
                        if (errno == EAGAIN) {
                            break;
                        }
                    } else {
                        write(ep_events[i].data.fd, buf, str_len); //send back to client
                        write(1, buf, str_len); //display data
                    }
                }
            }
        }
    }
    close(serv_sock);
    close(epfd);

    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

void setnonblockingmode(int fd)
{
    int flag = fcntl(fd, F_GETFL, 0);
    fcntl(fd, F_SETFL, flag | O_NONBLOCK);
}