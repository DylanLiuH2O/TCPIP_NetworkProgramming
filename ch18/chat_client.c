/*
 * @Author: dylan
 * @Date: 2021-06-20 16:56:21
 * @LastEditTime: 2021-06-27 15:39:09
 * @LastEditors: dylan
 * @Description: chat client
 * @FilePath: /TCPIP_NetworkProgramming/ch18/chat_client.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 4096
#define MAX_NAME_LEN 50
#define MAX_CLNT_NUM 65535

char name[MAX_NAME_LEN+1] = "default";
pthread_mutex_t mutex;

void error_handling(char *message);
void *send_msg(void *arg);
void *recv_msg(void *arg);

int main(int argc, char *argv[])
{
    if (argc != 4) {
        printf("usage: %s <ip> <port> <name>\n", argv[0]);
        exit(1);
    }

    /* check length of name */
    if (strlen(argv[3]) > MAX_NAME_LEN) {
        error_handling("The name exceeds the maximum length!");
    }
    strcpy(name, argv[3]);

    int serv_sock;
    struct sockaddr_in serv_addr;

    /* registe socket */
    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1) {
        error_handling("socket() errorh");
    }

    /* initialize serv_addr */
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family      = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port        = htons(atoi(argv[2]));

    /* connect to chat server */
    if (connect(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) {
        error_handling("connect() error");
    }

    pthread_t send_id;
    pthread_t recv_id;
    int t_ret;
    int ret1 = pthread_create(&send_id, NULL, send_msg, (void*)&serv_sock);
    int ret2 = pthread_create(&recv_id, NULL, recv_msg, (void*)&serv_sock);
    if (ret1 != 0 || ret2 != 0) {
        error_handling("pthread_create() error");
    }

    ret1 = pthread_join(send_id, (void*)&t_ret);
    ret2 = pthread_join(recv_id, (void*)&t_ret);
    if (ret1 != 0 || ret2 != 0) {
        error_handling("pthread_join() error");
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

void *send_msg(void *arg)
{
    int serv_sock = *((int*)arg);
    char msg[BUF_SIZE+1];
    char name_msg[MAX_NAME_LEN+BUF_SIZE+1];

    while (true) {
        fgets(msg, BUF_SIZE, stdin);
        if (!strcmp(msg, "q\n") || !strcmp(msg, "Q\n")) {
            close(serv_sock);
            exit(0);
        }
        sprintf(name_msg, "[%s]: %s", name, msg);
        write(serv_sock, name_msg, strlen(name_msg));
    }
    return NULL;
}

void *recv_msg(void *arg)
{
    int serv_sock = *((int*)arg);
    char msg[MAX_NAME_LEN+BUF_SIZE+1];

    int str_len;
    while (true) {
        str_len = read(serv_sock, msg, MAX_NAME_LEN+BUF_SIZE);
        if (str_len == -1) {
            return (void*)-1;
        }
        msg[str_len] = '\0';
        printf("%s", msg);
    }
    return NULL;
}