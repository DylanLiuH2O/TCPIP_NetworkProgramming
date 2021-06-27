/*
 * @Author: dylan
 * @Date: 2021-06-20 15:55:24
 * @LastEditTime: 2021-06-27 15:39:27
 * @LastEditors: dylan
 * @Description: add mutex based on 
 *               ch18/thread4.c
 * @FilePath: /TCPIP_NetworkProgramming/ch18/mutex.c
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREAD 100
long long sum  = 0;
pthread_mutex_t mutex;

void error_handling(char *message);
void *thread_inc(void *arg);
void *thread_dec(void *arg);

int main(int argc, char *argv[])
{
    pthread_t t_id[NUM_THREAD];

    pthread_mutex_init(&mutex, NULL);
    for (int i = 0; i < NUM_THREAD; i++) {
        if (i % 2) {
            pthread_create(&(t_id[i]), NULL, thread_inc, NULL);
        } else {
            pthread_create(&(t_id[i]), NULL, thread_dec, NULL);
        }
    }

    for (int i = 0; i < NUM_THREAD; i++) {
        pthread_join(t_id[i], NULL);
    }
    pthread_mutex_destroy(&mutex);

    printf("sum: %lld\n", sum);

    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

void *thread_inc(void *arg)
{
    pthread_mutex_lock(&mutex);
    for (int i = 0; i < 50000000; i++) {
        sum += i;
    }
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void *thread_dec(void *arg)
{
    pthread_mutex_lock(&mutex);
    for (int i = 0; i < 50000000; i++) {
        sum -= i;
    }
    pthread_mutex_unlock(&mutex);
    return NULL;
}