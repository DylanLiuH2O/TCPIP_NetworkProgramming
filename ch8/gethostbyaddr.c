/*
 * @Author: dylan
 * @Date: 2021-06-11 20:07:24
 * @LastEditTime: 2021-06-26 16:32:12
 * @LastEditors: dylan
 * @Description: test function gethostbyaddr()
 * @FilePath: /TCPIP_NetworkProgramming/ch8/gethostbyaddr.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>

void error_handling(char *message);

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("usage: %s <ip>\n", argv[0]);
        exit(1);
    }

    struct hostent *hostinfo = NULL;
    struct sockaddr_in addr;

    memset(&addr, 0, sizeof(addr));
    addr.sin_addr.s_addr = inet_addr(argv[1]);
    hostinfo             = gethostbyaddr((char*)&addr.sin_addr, 4, AF_INET);

    if (hostinfo == NULL) {
        error_handling("gethostbyaddr() error, "
                       "check your address plz.");
    }

    /* display info */
    printf("Official name: %s\n", hostinfo->h_name);
    for (int i = 0; hostinfo->h_aliases[i] != NULL; i++) {
        printf("Aliases %d: %s\n", i+1, hostinfo->h_aliases[i]);
    }
    printf("Address type: %s\n", 
      (hostinfo->h_addrtype == AF_INET) ? "AF_INET" : "AF_INET6");
    for (int i = 0; hostinfo->h_addr_list[i] != NULL; i++) {
        printf("IP address %d: %s\n", i+1, 
                inet_ntoa(*(struct in_addr*)hostinfo->h_addr_list[i]));
    }

    return 0;
}

void error_handling(char *message)
{
    fputs(message, stdout);
    fputc('\n', stdout);
    exit(1);
}