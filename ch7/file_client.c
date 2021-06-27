/*
 * @Author: dylan
 * @Date: 2021-06-09 20:18:40
 * @LastEditTime: 2021-06-26 16:07:54
 * @LastEditors: dylan
 * @Description: client - file transfer program based on half-close
 * @FilePath: /TCPIP_NetworkProgramming/ch7/file_client.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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

    int serv_sock;
    struct sockaddr_in serv_addr;
    char buff[BUF_SIZE];

    /* open file */
    FILE *fp;
    fp = fopen("receive.dat", "wb");
    if (fp == NULL) {
        error_handling("fopen() error");
    }

    /* register socket */
    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1) {
        error_handling("socket() error");
    }

    /* initialize serv_addr */
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family      = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port        = htons(atoi(argv[2]));

    /* make serv_sock connect to server specified by serv_addr */
    if (connect(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) {
        error_handling("connect() error");
    }
    puts("server connected");

    /* read data from server */
    int read_cnt;
    bool isread = false;
    while ((read_cnt = read(serv_sock, buff, BUF_SIZE)) != 0) {
        fwrite((void*)buff, 1, read_cnt, fp);
        if (!isread) {
            puts("receiving data...");
        }
        isread = true;
    }
    if (isread) {
        puts("receive complete");
    }

    write(serv_sock, "Thank you", sizeof("Thank you")+1);

    /* release resources */
    fclose(fp);
    close(serv_sock);

    return 0;
}

void error_handling(char *message)
{
    fputs(message, stdout);
    fputc('\n', stdout);
    exit(1);
}