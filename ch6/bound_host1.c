/*
 * @Author: dylan
 * @Date: 2021-06-24 22:57:58
 * @LastEditTime: 2021-06-26 14:51:02
 * @LastEditors: dylan
 * @Description: UDP datagram boundary test(server)
 * @FilePath: /TCPIP_NetworkProgramming/ch6/bound_host1.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 30

void error_handling(char *message);

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("usage: %s <port>\n", argv[0]);
        exit(1);
    }

    int local_sock;
    struct sockaddr_in my_addr;
    struct sockaddr_in your_addr;
    socklen_t addr_sz;

    char message[BUF_SIZE];

    /* register socket */
    local_sock = socket(PF_INET, SOCK_DGRAM, 0);
    if  (local_sock == -1) {
        error_handling("socket() error");
    }

    /* initialize my_addr */
    memset(&my_addr, 0, sizeof(my_addr));
    my_addr.sin_family      = AF_INET;
    my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    my_addr.sin_port        = htons(atoi(argv[1]));

    /* bind local_sock and my_adr */
    if (bind(local_sock, (struct sockaddr*)&my_addr, sizeof(my_addr)) == -1) {
        error_handling("bind() error");
    }

    /* receive datagram */
    for (int i = 0; i < 3; i++) {
        sleep(5);
        addr_sz = sizeof(your_addr);
        recvfrom(local_sock, message, BUF_SIZE, 0,
                 (struct sockaddr*)&your_addr, &addr_sz);
        printf("Message %d: %s\n", i+1, message);
    }

    /* release resource */
    close(local_sock);

    return 0;
}

void error_handling(char *message)
{
    fputs(message, stdout);
    fputc('\n', stdout);
    exit(1);
}