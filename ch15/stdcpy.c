/*
 * @Author: dylan
 * @Date: 2021-06-19 17:51:29
 * @LastEditTime: 2021-06-27 17:00:28
 * @LastEditors: dylan
 * @Description: test transmission
 *               performance of standard
 *               I/O function
 * @FilePath: /TCPIP_NetworkProgramming/ch15/stdcpy.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int BUF_SIZE = 50;

void error_handling(char *message);

int main(int argc, char *argv[])
{
    if (argc == 2) {
        BUF_SIZE = atoi(argv[1]);
    }
    FILE *fp1 = NULL;
    FILE *fp2 = NULL;
    char buf[BUF_SIZE];

    clock_t t1, t2;


    fp1 = fopen("data.txt", "r");
    fp2 = fopen("cpy.txt", "w");
    if (fp1 == NULL || fp2 == NULL) {
        error_handling("fopen() error");
    }

    puts("copying...");

    t1 = clock();
    while (fgets(buf, BUF_SIZE, fp1) != NULL) {
        fputs(buf, fp2);
    }
    fflush(fp2);
    t2 = clock();

    printf("stdcpy time: %.4lfs\n", (double)(t2-t1)/CLOCKS_PER_SEC);

    fclose(fp1);
    fclose(fp2);

    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
