/*
 * @Author: dylan
 * @Date: 2021-06-26 13:32:48
 * @LastEditTime: 2021-06-26 14:16:12
 * @LastEditors: dylan
 * @Description: endian convert
 * @FilePath: /TCPIP_NetworkProgramming/ch3/endian_conv.c
 */
#include <stdio.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
    unsigned short host_port = 0x1234;
    unsigned short net_port;
    unsigned long host_addr = 0x12345678;
    unsigned long net_addr;

    net_port = htons(host_port);
    net_addr = htonl(host_addr);

    printf("host ordered port:       %#x\n", host_port);
    printf("network ordered port:    %#x\n", net_port);
    printf("host ordered address:    %#lx\n", host_addr);
    printf("network ordered address: %#lx\n", net_addr);

    return 0;
}
