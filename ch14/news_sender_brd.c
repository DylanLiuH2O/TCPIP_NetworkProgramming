/*
 * @Author: dylan
 * @Date: 2021-06-19 15:26:25
 * @LastEditTime: 2021-06-27 14:59:06
 * @LastEditors: dylan
 * @Description: broadcast sender
 * @FilePath: /TCPIP_NetworkProgramming/ch14/news_sender_brd.c
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
        printf("usage: %s <broadcastip> <port>\n", argv[0]);
        exit(1);
    }

    int my_sock;
    struct sockaddr_in broad_addr;

    /* register socket */
    my_sock = socket(PF_INET, SOCK_DGRAM, 0);
    if (my_sock == -1) {
       error_handling("socket() error");
    }

    /* initialize broad_addr */
    memset(&broad_addr, 0, sizeof(broad_addr));
    broad_addr.sin_family      = AF_INET;
    broad_addr.sin_addr.s_addr = inet_addr(argv[1]);
    broad_addr.sin_port        = htons(atoi(argv[2]));

    /* set socket option */
    int so_broad_val = 1;
    int status = setsockopt(my_sock, SOL_SOCKET, 
            SO_BROADCAST, (void*)&so_broad_val, sizeof(so_broad_val));
    if (status == -1) {
        error_handling("setsockopt() error");
    }

    /* open file */
    FILE *fp = NULL;
    if ((fp = fopen("news.txt", "r")) == NULL) {
        error_handling("fopen() error");
    }

    char buf[BUF_SIZE];
    while (!feof(fp)) {
        fgets(buf, BUF_SIZE, fp);
        sendto(my_sock, buf, strlen(buf), 0,
                (struct sockaddr*)&broad_addr, sizeof(broad_addr));
        sleep(2);
    }
    fclose(fp);
    close(my_sock);

    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}