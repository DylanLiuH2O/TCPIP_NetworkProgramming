/*
 * @Author: dylan
 * @Date: 2021-06-24 22:57:58
 * @LastEditTime: 2021-06-26 14:41:58
 * @LastEditors: dylan
 * @Description: a extremely simple calculator server
 *               (only support processing request one
 *                by one)
 * @FilePath: /TCPIP_NetworkProgramming/ch5/op_server.c
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
int caculate(int opnum, int opnds[], char operator);

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("usage: %s <port>\n", argv[0]);
        exit(1);
    }

    int serv_sock;
    int clnt_sock;
    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_sz;

    char opbuff[BUFF_SIZE];

    /* register socket */
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

    /* receive info from client then calculate it, finally send it back */
    for (int i = 0; i < 5; i++) {
        clnt_addr_sz = sizeof(clnt_addr);
        clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_sz);
        if (clnt_sock == -1) {
            error_handling("accept() error");
        }
        int opnd_cnt;
        read(clnt_sock, &opnd_cnt, 1);

        int recv_len = 0;
        while (recv_len < (opnd_cnt*OPTYPESZ+1)) {
            int recv_cnt = read(clnt_sock, &opbuff[recv_len], OPTYPESZ);
            recv_len += recv_cnt;
        }

        char oprt = opbuff[recv_len-1];
        int res = caculate(opnd_cnt, (int*)opbuff, oprt);

        write(clnt_sock, (char*)&res, sizeof(res));
        close(clnt_sock);
    }

    /* release resource */
    close(serv_sock);

    return 0;
}

void error_handling(char *message)
{
    fputs(message, stdout);
    fputc('\n', stdout);
    exit(1);
}

int caculate(int opnum, int opnds[], char operator)
{
    int res = opnds[0];
    for (int i = 1; i < opnum; i++) {
        switch (operator) {
            case '+': res += opnds[i];
                break;
            case '-': res -= opnds[i];
                break;
            case '*': res *= opnds[i];
                break;
            default:
                break;
        }
    }
    return res;
}