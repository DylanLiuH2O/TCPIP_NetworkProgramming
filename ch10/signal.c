/*
 * @Author: dylan
 * @Date: 2021-06-13 11:51:46
 * @LastEditTime: 2021-06-26 17:30:51
 * @LastEditors: dylan
 * @Description: call alarm() and signal()
 * @FilePath: /TCPIP_NetworkProgramming/ch10/signal.c
 */
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void timeout(int sig)
{
    if (sig == SIGALRM) {
        puts("time out");
    }
    alarm(2);
}

void keycontrol(int sig)
{
    if (sig == SIGINT) {
        puts("CTRL+C pressed");
    }
}

int main(int argc, char *argv[])
{
    signal(SIGALRM, timeout);
    signal(SIGINT, keycontrol);
    alarm(2);

    for (int i = 0; i < 3; i++) {
        puts("wait...");
        sleep(100);
    }

    return 0;
}