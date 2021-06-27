/*
 * @Author: dylan
 * @Date: 2021-06-19 17:18:32
 * @LastEditTime: 2021-06-27 16:35:13
 * @LastEditors: dylan
 * @Description: test transmission
 *               performance of I/O
 *               fucntion in system 
 * @FilePath: /TCPIP_NetworkProgramming/ch15/syscpy.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

int BUF_SIZE = 50;

void error_handling(char *message);

int main(int argc, char *argv[])
{
    if (argc == 2) {
        BUF_SIZE = atoi(argv[1]);
    }
    int fd1, fd2;
    char buf[BUF_SIZE];

    clock_t t1, t2;
    int len;


    fd1 = open("data.txt", O_RDONLY);
    fd2 = open("cpy.txt", O_WRONLY | O_CREAT | O_TRUNC, 
                          S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
    if (fd1 == -1 || fd2 == -1) {
        error_handling("open() error");
    }

    puts("copying...");

    t1 = clock();
    while ((len = read(fd1, buf, sizeof(buf))) > 0) {
        write(fd2, buf, len);
    }
    t2 = clock();

    printf("syscpy time: %.4lfs\n", (double)(t2-t1)/CLOCKS_PER_SEC);

    close(fd1);
    close(fd2);

    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

