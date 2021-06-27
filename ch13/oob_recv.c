/*
 * @Author: dylan
 * @Date: 2021-06-18 15:32:37
 * @LastEditTime: 2021-06-27 01:35:38
 * @LastEditors: dylan
 * @Description: call recv() to receive
 *               message from sender
 * @FilePath: /TCPIP_NetworkProgramming/ch13/oob_recv.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 100

void error_handling(char *message);
void urg_handler(int signo);

int recv_sock;
int send_sock;

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("usage: %s <port>\n", argv[0]);
        exit(1);
    }

    struct sockaddr_in recv_addr;
    struct sockaddr_in send_addr;
    socklen_t addr_sz;
    char buf[BUF_SIZE];

    /* register signal handler */
    struct sigaction act;
    act.sa_handler = urg_handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    /* register recv_sock */
    recv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (recv_sock == -1) {
        error_handling("socker() error");
    }

    /* initialize recv_addr */
    memset(&recv_addr, 0, sizeof(recv_addr));
    recv_addr.sin_family      = AF_INET;
    recv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    recv_addr.sin_port        = htons(atoi(argv[1]));

    /* bind recv_addr to recv_sock */
    if (bind(recv_sock, (struct sockaddr*)&recv_addr, sizeof(recv_addr)) == -1) {
        error_handling("bind() error");
    }

    /* start to listen request */
    if (listen(recv_sock, 5) == -1) {
        error_handling("listen() error");
    }

    /* accept request */
    addr_sz = sizeof(send_addr);
    send_sock = accept(recv_sock, (struct sockaddr*)&send_addr, &addr_sz);
    if (send_sock == -1) {
        error_handling("accept() error");
    }

    fcntl(recv_sock, F_SETOWN, getpid());
    int status = sigaction(SIGURG, &act, 0);
    if (status == -1) {
        error_handling("sigaction() error");
    }

    int str_len = 0;
    while ((str_len = recv(send_sock, buf, sizeof(buf), 0)) != 0) {
        if (str_len == -1) {
            continue;
        }
        buf[str_len] = '\0';
        // puts(buf);
        printf("message: %ld %s\n", strlen(buf), buf);
    }

    /* release resource */
    close(send_sock);
    close(recv_sock);

    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

void urg_handler(int signo)
{
    int str_len;
    char buf[BUF_SIZE];
    str_len = recv(send_sock, buf, sizeof(buf), MSG_OOB);
    buf[str_len] = '\0';
    printf("urgent message: %s", buf);
}