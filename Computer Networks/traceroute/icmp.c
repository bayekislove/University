/* Kacper Bajkiewicz 314438 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <arpa/inet.h>

#include <assert.h>
#include <errno.h>
#include <unistd.h>

#include "wrappers.c"

#ifndef ICMP
#define ICMP 

u_int16_t icmp_checksum (const void *buff, int length)
{
	u_int32_t sum;
	const u_int16_t* ptr = buff;
	assert (length % 2 == 0);
	for (sum = 0; length > 0; length -= 2)
		sum += *ptr++;
	sum = (sum >> 16) + (sum & 0xffff);
	return (u_int16_t)(~(sum + (sum >> 16)));
}

void print_as_bytes (unsigned char* buff, ssize_t length)
{
	for (ssize_t i = 0; i < length; i++, buff++)
		printf ("%.2x ", *buff);	
}

uint8_t icmp_receive(int sockfd, struct icmp* header, char* ip_text)
{
	struct sockaddr_in 	sender;	
	socklen_t 			sender_len = sizeof(sender);
	u_int8_t 			buffer[IP_MAXPACKET];

	Recvfrom(sockfd, buffer, IP_MAXPACKET, MSG_DONTWAIT, (struct sockaddr*)&sender, &sender_len);

	struct ip* 			ip_header = (struct ip*) buffer;

	strcpy(ip_text, inet_ntoa(ip_header->ip_src));
	//printf("%s\n", ip_text);
	ssize_t				ip_header_len = 4 * ip_header->ip_hl;
    struct icmp*		header_help =  (struct icmp*)(buffer + ip_header_len);
	
	uint8_t result = header_help->icmp_type;
	if(header_help->icmp_type == 11)
	{
		struct ip* header2 = (struct ip*)(buffer + ip_header_len + 8);
		ip_header_len = 4 * header2->ip_hl;
		header_help = (struct icmp*)((void*)header2 + ip_header_len);
	}

	memcpy(header, header_help, sizeof(*header));
	return result;
}

int icmp_send(int ttl, int sockfd, char* ip)
{
    struct icmp header;
    header.icmp_type = ICMP_ECHO;
    header.icmp_code = 0;
    header.icmp_id = (uint16_t)getpid();
    header.icmp_seq = ttl;
    header.icmp_cksum = 0; //0 for computing the checksum
    header.icmp_cksum = icmp_checksum((u_int16_t*)&header, sizeof(header));

    struct sockaddr_in recipient;
    bzero(&recipient, sizeof(recipient));
    recipient.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &recipient.sin_addr);

    Setsockopt(sockfd, IPPROTO_IP, IP_TTL, &ttl, sizeof(int));
    ssize_t bytes_sent = Sendto(sockfd, &header, sizeof(header), 0, (struct sockaddr*)&recipient, sizeof(recipient));
	return bytes_sent;
}

#endif