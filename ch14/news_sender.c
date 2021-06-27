/*
 * @Author: dylan
 * @Date: 2021-06-19 10:17:18
 * @LastEditTime: 2021-06-27 14:59:14
 * @LastEditors: dylan
 * @Description: multicast sender
 * @FilePath: /TCPIP_NetworkProgramming/ch14/news_sender.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define TTL 64
#define BUF_SIZE 100

void error_handling(char *message);

int main(int argc, char *argv[])
{
    if (argc != 3) {
        printf("usage: %s <groupip> <port>\n", argv[0]);
        exit(1);
    }

    int my_sock;
    struct sockaddr_in mul_addr;
    char buf[BUF_SIZE];
    int time_live = TTL;

    /* register socket */
    my_sock = socket(PF_INET, SOCK_DGRAM, 0);
    if (my_sock == -1) {
        error_handling("socket() error");
    }

    /* initialize mul_addr */
    memset(&mul_addr, 0, sizeof(mul_addr));
    mul_addr.sin_family      = AF_INET;
    mul_addr.sin_addr.s_addr = inet_addr(argv[1]);
    mul_addr.sin_port        = htons(atoi(argv[2]));

    /* set socket option */
    int status = setsockopt(my_sock, IPPROTO_IP, 
            IP_MULTICAST_TTL, (void*)&time_live, sizeof(time_live));
    if (status == -1) {
        error_handling("setsockopt() error");
    }

    /* open file */
    FILE *fp = NULL;
    if ((fp = fopen("news.txt", "r")) == NULL) {
        error_handling("fopen() error");
    }

    /* multicast */
    while (!feof(fp)) {
        fgets(buf, BUF_SIZE, fp);
        sendto(my_sock, buf, sizeof(buf), 0, (struct sockaddr*)&mul_addr, 
                sizeof(mul_addr));
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

