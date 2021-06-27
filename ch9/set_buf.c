/*
 * @Author: dylan
 * @Date: 2021-06-11 22:12:53
 * @LastEditTime: 2021-06-26 16:58:11
 * @LastEditors: dylan
 * @Description: call setsockopt() to set the size of I/O buffer
 * @FilePath: /TCPIP_NetworkProgramming/ch9/set_buf.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>

void error_handling(char *message);

int main(int argc, char *argv[])
{
    int tcp_sock;
    int send_buf_sz = 1024 * 4;
    int recv_buf_sz = 1024 * 2;
    socklen_t buff_sz_len;
    int status;

    /* register TCP socket */
    tcp_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (tcp_sock == -1) {
        error_handling("socket() error");
    }

    status = setsockopt(tcp_sock, SOL_SOCKET, SO_SNDBUF, (void*)&send_buf_sz, sizeof(send_buf_sz));
    if (status != 0) {
        error_handling("setsockopt() error");
    }

    buff_sz_len = sizeof(send_buf_sz);
    status = getsockopt(tcp_sock, SOL_SOCKET, SO_SNDBUF, (void*)&send_buf_sz, &buff_sz_len);
    if (status != 0) {
        error_handling("getsockopt() error");
    }

    printf("Size of send buffer: %d\n", send_buf_sz);

    tcp_sock = socket(PF_INET, SOCK_STREAM, 0);
    status = setsockopt(tcp_sock, SOL_SOCKET, SO_RCVBUF, (void*)&recv_buf_sz, sizeof(recv_buf_sz));
    if (status != 0) {
        error_handling("setsockopt() error");
    }

    buff_sz_len = sizeof(recv_buf_sz);
    status = getsockopt(tcp_sock, SOL_SOCKET, SO_RCVBUF, (void*)&recv_buf_sz, &buff_sz_len);
    if (status != 0) {
        error_handling("getsockopt() error");
    }

    printf("Size of recv buffer: %d\n", send_buf_sz);

    return 0;
}

void error_handling(char *message)
{
    fputs(message, stdout);
    fputc('\n', stdout);
    exit(1);
}