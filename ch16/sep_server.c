/*
 * @Author: dylan
 * @Date: 2021-06-20 08:26:55
 * @LastEditTime: 2021-06-27 15:15:36
 * @LastEditors: dylan
 * @Description: split I/O stream, close FILE
 *               pointer without shutdown()
 * @FilePath: /TCPIP_NetworkProgramming/ch16/sep_server.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1000

void error_handling(char *message);

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("usage: %s <port>\n", argv[0]);
        exit(1);
    }

    int serv_sock;
    int clnt_sock;
    FILE *readfp  = NULL;
    FILE *writefp = NULL;
    
    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    socklen_t addr_sz;

    char buf[BUF_SIZE];

    /* register scoket */
    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1) {
        error_handling("socket() error");
    }

    /* initialize serv_addr */
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family      = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port        = htons(atoi(argv[1]));

    /* bind serv_sock to serv_addr */
    if (bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) {
        error_handling("bind() error");
    }

    /* start to listen request */
    if (listen(serv_sock, 5) == -1) {
        error_handling("listen() error");
    }

    /* accept request */
    addr_sz = sizeof(clnt_addr);
    clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &addr_sz);
    if (clnt_sock == -1) {
        error_handling("accept() error");
    }

    /* convert descriptor to FILE pointer */
    readfp  = fdopen(clnt_sock, "r");
    writefp = fdopen(clnt_sock, "w");
    if (readfp == NULL || writefp == NULL) {
        error_handling("fdopen() error");
    }

    memset(buf, '\0', sizeof(buf));

    fputs("from server: hi client.\n", writefp);
    /* this statement below is really important, 
       otherwise it will not send message immediately */
    fflush(writefp);
    fclose(writefp);
    /* cannot receive anything after close(writefp) */
    fgets(buf, sizeof(buf), readfp);
    fputs(buf, stdout);
    fclose(readfp);

    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
