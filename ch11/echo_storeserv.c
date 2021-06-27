/*
 * @Author: dylan
 * @Date: 2021-06-13 22:46:26
 * @LastEditTime: 2021-06-26 19:49:20
 * @LastEditors: dylan
 * @Description: multiprocess echo server with
 *               function of saving message to file
 * @FilePath: /TCPIP_NetworkProgramming/ch11/echo_storeserv.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/wait.h>

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
    char buf[BUF_SIZE];

    /* register signal handler */
    struct sigaction act;
    act.sa_handler = read_childproc;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    int status = sigaction(SIGCHLD, &act, 0);
    if (status == -1) {
        error_handling("sigaction() error");
    }

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
    
    /* create pipe */
    int fds[2];
    pipe(fds);

    /* fork child proc to write data to file */
    pid_t pid;
    pid = fork();
    if (pid == -1) {
        error_handling("fork() error");
    }

    if (pid == 0) {
        FILE *fp = fopen("echomsg.txt", "wt");
        if (fp == NULL) {
            error_handling("fopen() error");
            exit(1);
        }
        char msgbuf[BUF_SIZE];

        // while (true) { <-- this doesn't work temporary
        for (int i = 0; i < 10; i++) {
            int len = read(fds[0], msgbuf, BUF_SIZE);
            fwrite((void*)msgbuf, 1, len, fp);
        }
        fclose(fp);
        return 0;
    }

    while (true) {
        socklen_t addr_sz = sizeof(clnt_sock);
        clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &addr_sz);
        if (clnt_sock == -1) {
            continue;
        } else {
            puts("new client connected...");
        }

        pid = fork();
        if (pid == -1) {
            close(clnt_sock);
            continue;
        }

        if (pid == 0) {
            close(serv_sock);

            int str_len = 0;
            while ((str_len = read(clnt_sock, buf, BUF_SIZE)) != 0) {
                write(clnt_sock, buf, str_len); //send back to client
                write(fds[1], buf, str_len);    //send data to child process
                write(1, buf, str_len);         //display data 
            }

            close(clnt_sock);
            puts("client disconnected...");
            return 0;
        } else {
            close(clnt_sock);
        }
    }
    
    /* release resource */
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