/*
 * @Author: dylan
 * @Date: 2021-06-11 22:06:38
 * @LastEditTime: 2021-06-26 16:58:37
 * @LastEditors: dylan
 * @Description: call getsocketopt() to get socket-type of socket
 * @FilePath: /TCPIP_NetworkProgramming/ch9/sock_type.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>

void error_handling(char *message);

int main(int argc, char *argv[])
{
    int tcp_sock;
    int udp_sock;
    int sock_type;
    socklen_t optlen;
    int status;

    optlen = sizeof(sock_type);

    /* register socket */
    tcp_sock = socket(PF_INET, SOCK_STREAM, 0);
    udp_sock = socket(PF_INET, SOCK_DGRAM, 0);
    if (tcp_sock == -1 || udp_sock == -1) {
        error_handling("socket() error");
    }

    /* print the value of protocol */
    printf("SOCK_STREAM: %d\n", SOCK_STREAM);
    printf("SOCK_DGRAM: %d\n", SOCK_DGRAM);

    /* get TCP Socket option */
    status = getsockopt(tcp_sock, SOL_SOCKET, SO_TYPE, (void*)&sock_type, &optlen);
    if (status != 0) {
        error_handling("getsockopt() error");
    }
    printf("TCP Socket type: %d\n", sock_type);

    /* get UDP Socket option */
    status = getsockopt(udp_sock, SOL_SOCKET, SO_TYPE, (void*)&sock_type, &optlen);
    if (status != 0) {
        error_handling("getsockopt() error");
    }
    printf("UDP Socket type: %d\n", sock_type);

    return 0;
}

void error_handling(char *message)
{
    fputs(message, stdout);
    fputc('\n', stdout);
    exit(1);
}