/*
 * @Author: dylan
 * @Date: 2021-06-19 15:56:50
 * @LastEditTime: 2021-06-27 14:58:47
 * @LastEditors: dylan
 * @Description: broadcast receiver
 * @FilePath: /TCPIP_NetworkProgramming/ch14/news_receiver_brd.c
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
    if (argc != 2) {
        printf("usage: %s <port>", argv[0]);
    }
    int my_sock;
    struct sockaddr_in send_addr;
    char buf[BUF_SIZE];

    /* register socket */
    my_sock = socket(PF_INET, SOCK_DGRAM, 0);
    if (my_sock == -1) {
        error_handling("socket() error");
    }
    
    /* initialize send_addr */
    memset(&send_addr, 0, sizeof(send_addr));
    send_addr.sin_family      = AF_INET;
    send_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    send_addr.sin_port        = htons(atoi(argv[1]));

    /* bind my_sock to send_addr */
    if (bind(my_sock, (struct sockaddr*)&send_addr, sizeof(send_addr)) == -1) {
        error_handling("bind() error");
    }
    
    while (true) {
        int str_len = recvfrom(my_sock, buf, BUF_SIZE-1, 0, NULL, 0);
        if (str_len == -1) {
            error_handling("recvfrom() error");
        }
        if (str_len == 0) {
            break;
        }
        buf[str_len] = 0;
        puts(buf);
    }
    close(my_sock);

    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}


