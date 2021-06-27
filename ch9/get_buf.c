/*
 * @Author: dylan
 * @Date: 2021-06-11 22:06:47
 * @LastEditTime: 2021-06-26 16:47:43
 * @LastEditors: dylan
 * @Description: call getsockopt() to get size of I/O buffer
 * @FilePath: /TCPIP_NetworkProgramming/ch9/get_buf.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

void error_handling(char *message);

int main(int argc, char *argv[])
{
    int tcp_sock;
    int send_buf_sz;
    int recv_buf_sz;
    socklen_t buff_sz_len;
    int status;

    tcp_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (tcp_sock == -1) {
        error_handling("socket() error");
    }

    buff_sz_len = sizeof(send_buf_sz);
    status = getsockopt(tcp_sock, SOL_SOCKET, SO_SNDBUF, (void*)&send_buf_sz, &buff_sz_len);
    if (status != 0) {
        error_handling("getsockopt() error");
    }
    printf("Size of send buffer: %d\n", send_buf_sz);

    buff_sz_len = sizeof(recv_buf_sz);
    status = getsockopt(tcp_sock, SOL_SOCKET, SO_SNDBUF, (void*)&recv_buf_sz, &buff_sz_len);
    if (status != 0) {
        error_handling("getsockopt() error");
    }
    printf("Size of recv buffer: %d\n", recv_buf_sz);

    return 0;
}

void error_handling(char *message)
{
    fputs(message, stdout);
    fputc('\n', stdout);
    exit(1);
}