/*
 * @Author: dylan
 * @Date: 2021-06-13 13:44:50
 * @LastEditTime: 2021-06-26 17:30:15
 * @LastEditors: dylan
 * @Description: multiprocess echo server
 * @FilePath: /TCPIP_NetworkProgramming/ch10/echo_mpserv.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define BUF_SIZE 50
void error_handling(char *message);
void read_childproc(int sig);

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
    char buf[BUF_SIZE];
    pid_t pid;

    /* register signal handler */
    struct sigaction act;
    act.sa_handler = read_childproc; 
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGCHLD, &act, 0);

    /* register socket */
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

    while (true) {
        /* main process accept a new request */
        addr_sz = sizeof(clnt_addr);
        clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &addr_sz);
        if (clnt_sock == -1) {
            puts("accept() fail");
            continue;
        } else {
            puts("new client connected...");
        }

        /* fork a child process to process request */
        pid = fork();
        if (pid == -1) {
            close(clnt_sock);
            continue;
        }

        if (pid == 0) {
            /* release unused resource in child proc */
            close(serv_sock);

            /* read data until receive an EOF whose length is zero */
            int str_len = 0;
            while ((str_len = read(clnt_sock, buf, BUF_SIZE)) != 0) {
                write(clnt_sock, buf, str_len);
                /* write data to stdout to display result */
                write(1, buf, str_len);
            }

            /* release resource */
            close(clnt_sock);
            puts("client disconnected...");
            return 0;
        } else {
            close(clnt_sock);
        }
    } /* end while */
    close(serv_sock);

    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

void read_childproc(int sig)
{
    int status;
    pid_t pid;
    pid = waitpid(-1, &status, WNOHANG);
    if (WIFEXITED(status) == true) {
        printf("removed proc id: %d\n", pid);
        printf("child sent: %d\n", WEXITSTATUS(status));
    }
}