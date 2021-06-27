/*
 * @Author: dylan
 * @Date: 2021-06-11 20:07:07
 * @LastEditTime: 2021-06-26 16:25:29
 * @LastEditors: dylan
 * @Description: call gethostbyname() to get info of host
 * @FilePath: /TCPIP_NetworkProgramming/ch8/gethostbyname.c
 */

/*
#include <netdb.h>
struct hostnet {
	char *h_name;		// official name
	char **h_aliases;	// alias list
	int h_addrtype;		// host address type
	int h_length;		// address length
    char **h_addr_list;	// address list
};
    //hostname --> IP address
struct hostnet *gethostbyname(const char *hostname);
    //Ip address --> hostname
struct hostnet *gethostbyaddr(const char *addr, socklen_t len, int family);
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>

void error_handling(char *message);

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("usage: %s <hostname>\n", argv[0]);
        exit(1);
    }

    struct hostent *hostinfo;

    hostinfo = gethostbyname(argv[1]);

    if (hostinfo == NULL) {
        error_handling("gethostbyname() error, "
                       "check your hostname plz.");
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