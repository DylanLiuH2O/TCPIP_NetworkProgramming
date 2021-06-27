/*
 * @Author: dylan
 * @Date: 2021-06-20 15:59:49
 * @LastEditTime: 2021-06-27 15:39:35
 * @LastEditors: dylan
 * @Description: use semaphore to deal
 *               with producer-consumer
 *               problem
 * @FilePath: /TCPIP_NetworkProgramming/ch18/semaphore.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

static sem_t sem_itemsnum;
static sem_t sem_freespace;
static int num;

void error_handling(char *message);
void *input(void *arg);
void *add(void *arg);

int main(int argc, char *argv[])
{
    pthread_t t1_id;
    pthread_t t2_id;

    sem_init(&sem_itemsnum, 0, 0);
    sem_init(&sem_freespace, 0, 1);

    int ret1 = pthread_create(&t1_id, NULL, input, NULL);
    int ret2 = pthread_create(&t2_id, NULL, add, NULL);
    if (ret1 != 0 || ret2 != 0) {
        error_handling("pthread_create() error");
    }

    pthread_join(t1_id, NULL);
    pthread_join(t2_id, NULL);

    sem_destroy(&sem_itemsnum);
    sem_destroy(&sem_freespace);

    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

void *input(void *arg)
{
    for (int i = 0; i < 5; i++) {
        printf("Input num: ");
        sem_wait(&sem_freespace);
        scanf("%d", &num);
        sem_post(&sem_itemsnum);
    }
    return NULL;
}

void *add(void *arg)
{
    int sum = 0;
    for (int i = 0; i < 5; i++) {
        sem_wait(&sem_itemsnum);
        sum += num;
        sem_post(&sem_freespace);
    }
    printf("result: %d\n", sum);
    return NULL;
}