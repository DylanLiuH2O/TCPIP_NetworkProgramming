/*
 * @Author: dylan
 * @Date: 2021-06-20 16:56:16
 * @LastEditTime: 2021-06-27 15:39:17
 * @LastEditors: dylan
 * @Description: chat server based on
 *               multithread
 * @FilePath: /TCPIP_NetworkProgramming/ch18/chat_server.c
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
#define MAX_CLNT_NUM 65536

int clnt_cnt = 0;
int clnt_socks[MAX_CLNT_NUM];
pthread_mutex_t mutex;

void error_handling(char *message);
void *handle_clnt(void *arg);
void *send_msg(char *msg, int len);

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
    socklen_t addr_sz;

    /* register sockert */
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

    pthread_mutex_init(&mutex, NULL);

    while (true) {
        addr_sz = sizeof(clnt_addr);
        clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &addr_sz);
        if (clnt_sock == -1) {
            error_handling("accept() error");
        }

        /* add clnt_sock to connetced list */
        pthread_mutex_lock(&mutex);
        clnt_socks[clnt_cnt++] = clnt_sock;
        pthread_mutex_unlock(&mutex);

        /* create thread to process client */
        pthread_t t_id;
        int status = pthread_create(&t_id, NULL, handle_clnt, (void*)&clnt_sock);
        if (status != 0) {
            error_handling("pthread_create() error");
        }
        pthread_detach(t_id);
        printf("new client connected, ip: %s\n", inet_ntoa(clnt_addr.sin_addr));
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

void *handle_clnt(void *arg)
{
    int clnt_sock = *((int*)arg);
    char buf[BUF_SIZE];
    int str_len;

    /* receive message from client, then send it to all clients */
    while ((str_len = read(clnt_sock, buf, sizeof(buf))) != 0) {
        send_msg(buf, str_len);
    }

    /* remove disconnected client */
    pthread_mutex_lock(&mutex);
    for (int i = 0; i < clnt_cnt; i++) {
        if (clnt_socks[i] == clnt_sock) {
            while (i < clnt_cnt-1) {
                clnt_socks[i] = clnt_socks[i+1];
            }
        }
    }
    clnt_cnt--;
    pthread_mutex_unlock(&mutex);

    close(clnt_sock);
    
    return NULL;
}

void *send_msg(char *msg, int len)
{
    pthread_mutex_lock(&mutex);
    for (int i = 0; i < clnt_cnt; i++) {
        write(clnt_socks[i], msg, len);
    }
    pthread_mutex_unlock(&mutex);

    return NULL;
}