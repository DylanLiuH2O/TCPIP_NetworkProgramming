/*
 * @Author: dylan
 * @Date: 2021-06-24 22:57:58
 * @LastEditTime: 2021-06-26 14:55:58
 * @LastEditors: dylan
 * @Description: UDP echo-client with connect()
 * @FilePath: /TCPIP_NetworkProgramming/ch6/uecho_conn_client.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 100

void error_handling(char *message);

int main(int argc, char *argv[])
{
    if (argc != 3) {
        printf("usage: %s <ip> <port>\n", argv[0]);
        exit(1);
    }

    int sock;
    //socklen_t addr_sz;
    char message[BUF_SIZE];
    int str_len;

    struct sockaddr_in serv_addr;
    //struct sockaddr_in from_addr;

    /* register socket */
    sock = socket(PF_INET, SOCK_DGRAM, 0);
    if (sock == -1) {
        error_handling("socket() error");
    }

    /* initialize serv_addr */
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family      = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port        = htons(atoi(argv[2]));

    /* connect to server (not connect in real, 
       just register the info of server)       */
    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) {
        error_handling("connect() error");
    }

    /* transmit data */
    while (1) {
        fputs("Input message(q to quit): ", stdout);
        fgets(message, sizeof(message), stdin);
        if (!strcmp(message, "q\n") || !strcmp(message, "Q\n")) {
            break;
        }

        /*
        sendto(sock, message, strlen(message), 0, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
        */
        write(sock, message, strlen(message));
        /*
        addr_sz = sizeof(from_addr);
        str_len = recvfrom(sock, message, BUF_SIZE, 0, (struct sockaddr*)&from_addr, &addr_sz);
        */
        str_len = read(sock, message, sizeof(message)-1);
        message[str_len] = 0;
        printf("Message from server: %s", message);
    }

    /* release resource */
    close(sock);

    return 0;
}

void error_handling(char *message)
{
    fputs(message, stdout);
    fputc('\n', stdout);
    exit(1);
}