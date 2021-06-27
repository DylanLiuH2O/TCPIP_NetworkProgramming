/*
 * @Author: dylan
 * @Date: 2021-06-24 22:57:58
 * @LastEditTime: 2021-06-26 14:37:27
 * @LastEditors: dylan
 * @Description: a extremely simple calculator client
 * @FilePath: /TCPIP_NetworkProgramming/ch5/op_client.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUFF_SIZE 1024
#define OPTYPESZ 4
#define RESSZ 4

void error_handling(char *message);

int main(int argc, char *argv[])
{
    if (argc != 3) {
        printf("usage: %s <ip> <port>\n", argv[0]);
        exit(1);
    }

    int serv_sock;
    struct sockaddr_in serv_addr;

    char opbuff[BUFF_SIZE];

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

    /* connect to server */
    if (connect(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) {
        error_handling("connect() error");
    }

    printf("Connected...\n");

    /* get info from stdin */
    int opnd_cnt;
    fputs("Operand count: ", stdout);
    scanf("%d", &opnd_cnt);
    opbuff[0] = (char)opnd_cnt;

    for (int i = 0; i < opnd_cnt; i++) {
        printf("Operand %d: ", i+1);
        scanf("%d", (int*)&opbuff[1+i*OPTYPESZ]);
    }
    fgetc(stdin);
    fputs("Operator: ", stdout);
    scanf("%c", &opbuff[1+opnd_cnt*OPTYPESZ]);

    /* send info to server and receive result from server */
    int res;
    write(serv_sock, opbuff, opnd_cnt*OPTYPESZ+2);
    read(serv_sock, &res, RESSZ);

    printf("Operation result: %d\n", res);

    /* release resource */
    close(serv_sock);

    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}