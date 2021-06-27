/*
 * @Author: dylan
 * @Date: 2021-06-20 00:08:50
 * @LastEditTime: 2021-06-27 18:35:21
 * @LastEditors: dylan
 * @Description: echo server using standard
 *               I/O function
 * @FilePath: /TCPIP_NetworkProgramming/ch15/echo_stdserver.c
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
    if (argc != 2) {
        printf("usage: %s <port>\n", argv[0]);
        exit(1);
    }

    int serv_sock;
    int clnt_sock;
    char message[BUF_SIZE];

    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    socklen_t clnt_adr_sz;


    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1) {
        error_handling("sock() error");
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family      = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port        = htons(atoi(argv[1]));

    if (bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) {
        error_handling("bind() error");
    }

    if (listen(serv_sock, 5) == -1)  {
        error_handling("listen() error");
    }

    for (int i = 0; i < 5; i++) {
        clnt_adr_sz = sizeof(clnt_addr);
        clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_adr_sz);
        if (clnt_sock == -1) {
            error_handling("accept() error");
        } else {
            printf("Connected client %d\n", i+1);
        }

        FILE *readfp = fdopen(clnt_sock, "r");
        FILE *writefp = fdopen(clnt_sock, "w");
        while (!feof(readfp)) {
            //printf("recv_len: %d\n", str_len);
            // write(clnt_sock, message, str_len);
            fgets(message, BUF_SIZE, readfp);
            fputs(message, stdout);
            fputs(message, writefp);
            fflush(writefp);
        }

        fclose(readfp);
        fclose(writefp);
    }

    close(serv_sock);

    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}