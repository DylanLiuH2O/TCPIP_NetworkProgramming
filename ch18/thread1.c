/*
 * @Author: dylan
 * @Date: 2021-06-20 14:08:18
 * @LastEditTime: 2021-06-27 15:39:44
 * @LastEditors: dylan
 * @Description: test pthread
 * @FilePath: /TCPIP_NetworkProgramming/ch18/thread1.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void error_handling(char *message);
void *threadA(void *arg);

int main(int argc, char *argv[])
{
    pthread_t t_id;
    int thread_param = 5;

    if (pthread_create(&t_id, NULL, threadA, (void*)&thread_param) != 0) {
        error_handling("pthread_create() error");
    }
    /* the statement below is not the appropriate 
       way to wait for the end of thread */
    sleep(10);
    puts("end of main");

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

    for (int i = 0; i < cnt; i++) {
        sleep(1);
        puts("thread is running...");
    }

    return NULL;
}