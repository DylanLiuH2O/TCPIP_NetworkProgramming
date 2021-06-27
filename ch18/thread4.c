/*
 * @Author: dylan
 * @Date: 2021-06-20 15:45:50
 * @LastEditTime: 2021-06-27 15:40:07
 * @LastEditors: dylan
 * @Description: verify the problem causeed 
 *               by critical area
 * @FilePath: /TCPIP_NetworkProgramming/ch18/thread4.c
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREAD 100
long long sum  = 0;

void error_handling(char *message);
void *thread_inc(void *arg);
void *thread_dec(void *arg);

int main(int argc, char *argv[])
{
    pthread_t t_id[NUM_THREAD];

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
    for (int i = 0; i < 50000000; i++) {
        sum += i;
    }
    return NULL;
}

void *thread_dec(void *arg)
{
    for (int i = 0; i < 50000000; i++) {
        sum -= i;
    }
    return NULL;
}
