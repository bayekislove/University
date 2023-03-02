/* Kacper Bajkiewicz 314438 */

#include <netinet/ip.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#ifndef WRAPPERS
#define WRAPPERS

int Socket(int domain, int type, int proto)
{
    int sockfd = socket(domain, type, proto);
    if (sockfd < 0) {
		fprintf(stderr, "socket error: %s\n", strerror(errno)); 
        return -1;
    }
    return sockfd;
}

ssize_t Recvfrom(int fd, void* buf, size_t n, int flags, struct sockaddr* sender, socklen_t* sender_len)
{
    ssize_t packet_len = recvfrom(fd, buf, n, flags, sender, sender_len);
    if (packet_len < 0) {
	    fprintf(stderr, "recvfrom error: %s\n", strerror(errno)); 
	    return EXIT_FAILURE;
	}
    return packet_len;
}

int Setsockopt(int sockfd, int level, int optname, const void* optval, socklen_t optlen)
{
    int result = setsockopt(sockfd, level, optname, optval, optlen);
    if(result < 0){
        fprintf(stderr, "setsockopt error: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int Sendto(int sockfd, const void *buf, size_t len, int flags, const struct sockaddr *destaddr, socklen_t addrlen)
{
    int bytes_sent = sendto(sockfd, buf, len, flags, destaddr, addrlen);
    if(bytes_sent < 0){
        fprintf(stderr, "sendto error: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }
    return bytes_sent;
}

int Select(int nfds, fd_set *restrict readfds, fd_set *restrict writefds, fd_set *restrict exceptfds, struct timeval *restrict timeout)
{
    int ready_descriptors = select(nfds, readfds, writefds, exceptfds, timeout);
    if(ready_descriptors < 0){
        fprintf(stderr, "select error: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }
    return ready_descriptors;
}

#endif