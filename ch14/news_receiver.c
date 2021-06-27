/*
 * @Author: dylan
 * @Date: 2021-06-19 10:17:27
 * @LastEditTime: 2021-06-27 14:58:54
 * @LastEditors: dylan
 * @Description: multicast receiver
 * @FilePath: /TCPIP_NetworkProgramming/ch14/news_receiver.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <errno.h>

#define BUF_SIZE 100

void error_handling(char *message);

int main(int argc, char *argv[])
{
    if (argc != 3) {
        printf("usage: %s <groupip> <port>", argv[0]);
    }
    int send_sock;
    struct sockaddr_in send_addr;
    struct ip_mreq join_addr;
    char buf[BUF_SIZE];

    /* register socket */
    send_sock = socket(PF_INET, SOCK_DGRAM, 0);
    if (send_sock == -1) {
        error_handling("socket() error");
    }
    
    /* initialize send_addr */
    memset(&send_addr, 0, sizeof(send_addr));
    send_addr.sin_family      = AF_INET;
    send_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    // send_addr.sin_addr.s_addr = inet_addr(argv[1]);
    send_addr.sin_port        = htons(atoi(argv[2]));

    /* bind send_sock to send_addr */
    if (bind(send_sock, (struct sockaddr*)&send_addr, sizeof(send_addr)) == -1) {
        error_handling("bind() error");
    }

    /* initialize join_addr */
    join_addr.imr_multiaddr.s_addr = inet_addr(argv[1]);
    join_addr.imr_interface.s_addr = htonl(INADDR_ANY);

    /* set socket option */
    int status = setsockopt(send_sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, 
                (void*)&join_addr, sizeof(join_addr));
    if (status == -1) {
        printf("errno: %d %s\n", errno, strerror(errno));
        error_handling("setsockopt() error");
    }
    
    while (true) {
        int str_len = recvfrom(send_sock, buf, BUF_SIZE-1, 0, NULL, 0);
        if (str_len == -1) {
            error_handling("recvfrom() error");
        }
        if (str_len == 0) {
            break;
        }
        buf[str_len] = 0;
        puts(buf);
    }
    close(send_sock);

    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

