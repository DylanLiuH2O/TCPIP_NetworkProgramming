/*
 * @Author: dylan
 * @Date: 2021-06-06 11:51:19
 * @LastEditTime: 2021-06-27 15:06:01
 * @LastEditors: dylan
 * @Description: echo client using standard
 *               I/O function
 * @FilePath: /TCPIP_NetworkProgramming/ch15/echo_stdclient.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <fcntl.h>

#define BUF_SIZE 100
void error_handling(char *message);

int main(int argc, char *argv[])
{
    int sock;
    char message[BUF_SIZE];
    // int str_len;
    struct sockaddr_in serv_addr;

    if (argc != 3) {
        printf("usage: %s <ip> <port>\n", argv[0]);
        exit(1);
    }

    sock = socket(PF_INET, SOCK_STREAM, 0);

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) {
        error_handling("connect() error");
    } else {
        puts("Connected......");
    }

    FILE *readfp = fdopen(sock, "r");
    FILE *writefp = fdopen(sock, "w");
    while (1) {
        fputs("Input message(q to quit): ", stdout);
        fgets(message, BUF_SIZE, stdin);
        
        if (!strcmp(message, "q\n") || !strcmp(message, "Q\n")) {
            break;
        }

        //write(sock, message, strlen(message));
        fputs(message, writefp);
        // str_len = read(sock, message, BUF_SIZE-1);
        fflush(writefp);
        fgets(message, BUF_SIZE, readfp);
        //printf("recv_len: %d\n", str_len);
        // message[str_len] = '\0';
        printf("Message from server: %s", message);
    }
    // close(sock);
    fclose(writefp);
    fclose(readfp);

    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}