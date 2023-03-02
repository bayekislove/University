tar -cJf archive.tar.xz dir1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <arpa/inet.h>
#include <netdb.h>

#include <sys/select.h>
#include <sys/time.h>

#include <assert.h>
#include <errno.h>
#include <unistd.h>

#include "icmp.c"
#include "wrappers.c"

#define MAX_HOPS 30

#ifndef TRACEROUTE
#define TRACEROTUE

uint8_t validate_ip_address(char* ip)
{
    struct sockaddr_in sa;
    return (inet_pton(AF_INET, ip, &(sa.sin_addr)) > 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

// uint8_t ip_from_hostname(char* hostname, char* ip)
// {
//     struct hostent* hostentry;
//     struct in_addr* addr;

//     if((hostentry = gethostbyname(hostname)) == NULL)
//         return EXIT_FAILURE;
	
// 	if((addr = (struct in_addr *) hostentry->h_addr_list[0]) != NULL)
//     {
// 		strcpy(ip, inet_ntoa(*addr));
// 	}
//     return EXIT_SUCCESS;
// }

uint8_t validate_input_converting_host(int input_args_counter, char* input, char* ip)
{
    if(input_args_counter != 2)
    {
        fprintf(stderr, "./traceroute [ip-address] should take exactly one argument\n"); 
        exit(EXIT_FAILURE);
    }

    if(validate_ip_address(input) == EXIT_SUCCESS)
    {
        strcpy(ip, input);
    }
    else
    {
        fprintf(stderr, "./traceroute [ip-address|hostname] was given invalid ip address or hostname\n"); 
        exit(EXIT_FAILURE);
    }

    // else if (ip_from_hostname(input, ip) == EXIT_FAILURE)
    // {
    //     fprintf(stderr, "./traceroute [ip-address|hostname] was given invalid ip address or hostname\n"); 
    //     exit(EXIT_FAILURE);
    // }
    fprintf(stdout, "traceroute to %s (%s), %d hops max\r\n", ip, ip, MAX_HOPS);
    return EXIT_SUCCESS;
}

int main(int argc, char* argv[])
{
    char ip[20];
    char received_ip[20];
    char previous_ip[20];
    validate_input_converting_host(argc, *(argv + 1), ip); //get user input, validate it and convert to ip if it's host

    int socketfd = Socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    for(int ttl = 1; ttl <= MAX_HOPS; ttl++)
    {
        fd_set rfds;
        FD_ZERO(&rfds);
        FD_SET(socketfd, &rfds);

        uint8_t received = 0; //how many correct packages do we have?
        struct timeval sum = {0};
        struct timeval start = {0};
        struct timeval end = {0};
        struct timeval interval = {0};
        interval.tv_sec = 1;
        interval.tv_usec = 0;

        struct icmp header = {0};

        icmp_send(ttl, socketfd, ip);
        icmp_send(ttl, socketfd, ip);
        icmp_send(ttl, socketfd, ip);

        gettimeofday(&start, NULL);
        while(received < 3)
        {
            if(Select(socketfd + 1, &rfds, NULL, NULL, &interval) == 0) //no response after 1 sec
            {
                if(received == 0)
                {
                    printf("%d *\n", ttl);
                }
                else if(received < 3)
                {
                    printf("???\n");
                }
                break;
            }
            gettimeofday(&end, NULL);
            timersub(&end, &start, &interval);
            timeradd(&interval, &sum, &sum);

            memcpy(&previous_ip, &received_ip, sizeof(previous_ip));
            uint8_t type = icmp_receive(socketfd, &header, received_ip);
            if((header.icmp_id == (uint16_t)getpid()) && (header.icmp_seq == ttl))
            {
                received++;
                if(received == 1)
                    printf("%d %s ", ttl, received_ip);
                else if(received > 2)
                {
                    if(strcmp(previous_ip, received_ip) != 0)
                        printf(" %s ", received_ip);
                }
                if(received == 3)
                {
                    printf(" %ldms\n", sum.tv_usec / 3000); //sekundy chyba bez sensu dodawac w tym przypadku
                    if(type == ICMP_ECHOREPLY)
                        exit(EXIT_SUCCESS);
                    else
                        break;
                }
            }
        }
    };
}

#endif