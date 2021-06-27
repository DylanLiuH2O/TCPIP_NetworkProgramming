/*
 * @Author: dylan
 * @Date: 2021-06-13 12:40:55
 * @LastEditTime: 2021-06-26 17:30:43
 * @LastEditors: dylan
 * @Description: call sigaction() which
 *               is better and more compatible
 * @FilePath: /TCPIP_NetworkProgramming/ch10/sigaction.c
 */
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

/*
strcut sigaction {
    void (*sa_handler)(int);
    sigset_t sa_mask;
    int sa_flags;
}
*/

void timeout(int sig)
{
    if (sig == SIGALRM) {
        puts("time out");
    }
    alarm(2);
}

int main(int argc, char *argv[])
{
    struct sigaction act;
    act.sa_handler = timeout;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    sigaction(SIGALRM, &act, 0);
    alarm(2);

    for (int i = 0; i < 3; i++) {
        puts("wait...");
        sleep(10);
    }

    return 0;
}
