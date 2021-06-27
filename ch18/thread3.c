/*
 * @Author: dylan
 * @Date: 2021-06-20 15:29:08
 * @LastEditTime: 2021-06-27 15:40:00
 * @LastEditors: dylan
 * @Description: multithread access
 *               shared variable
 * @FilePath: /TCPIP_NetworkProgramming/ch18/thread3.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int sum  = 0;

void error_handling(char *message);
void *thread_sum(void *arg);

int main(int argc, char *argv[])
{
    pthread_t t1_id;
    pthread_t t2_id;

    int range1[] = { 1, 5000 };
    int range2[] = { 5001, 10000};
    
    int ret1 = pthread_create(&t1_id, NULL, thread_sum, (void*)range1);
    int ret2 = pthread_create(&t2_id, NULL, thread_sum, (void*)range2);
    if (ret1 != 0 || ret2 != 0) {
        error_handling("pthread_create() error");
    }

    ret1 = pthread_join(t1_id, NULL);
    ret2 = pthread_join(t2_id, NULL);
    
    printf("sum: %d\n", sum);

    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

void *thread_sum(void *arg)
{
    int start = ((int*)arg)[0];
    int end   = ((int*)arg)[1];

    for (int i = start; i <= end; i++) {
        sum += i;
    }

    return NULL;
}
