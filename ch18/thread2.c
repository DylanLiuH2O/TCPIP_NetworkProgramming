/*
 * @Author: dylan
 * @Date: 2021-06-20 14:46:02
 * @LastEditTime: 2021-06-27 15:39:51
 * @LastEditors: dylan
 * @Description: test pthread_join()
 * @FilePath: /TCPIP_NetworkProgramming/ch18/thread2.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

void error_handling(char *message);
void *threadA(void *arg);

int main(int argc, char *argv[])
{
    pthread_t t_id;
    int thread_param = 5;
    void *t_ret;

    if (pthread_create(&t_id, NULL, threadA, (void*)&thread_param) != 0) {
        error_handling("pthread_create() error");
    }

    if (pthread_join(t_id, &t_ret) != 0) {
        error_handling("pthread_join() error");
    }

    printf("thread return message: %s", (char*)t_ret);

    free(t_ret);

    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

void *threadA(void *arg)
{
    int cnt = *((int*)arg);
    char *msg;

    msg = (char*)malloc(50*sizeof(char));

    strcpy(msg, "I am a thread.\n");

    for (int i = 0; i < cnt; i++) {
        sleep(1);
        puts("thread is running...");
    }

    return (void*)msg;
}
