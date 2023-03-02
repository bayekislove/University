/* Kacper Bajkiewicz 314438 */

#include <netinet/ip.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sstream>
#include <string>
#include <iostream>
#include <cstring>

#include "wrappers.cpp"
#include "window.cpp"

#ifndef UDP
#define UDP

#define PACKET_LEN 1000

int clientSend(int32_t sockfd, sockaddr_in* server_address, int32_t start_byte, int32_t len)
{
	std::stringstream message;
    message << "GET " << std::to_string(start_byte) << " " << std::to_string(len) << "\n";

    const char* message_cstr = message.str().c_str();
	ssize_t message_len = strlen(message_cstr);

	return Sendto(sockfd, message_cstr, message_len, 0, (struct sockaddr*) server_address, sizeof(*server_address));
}

std::pair<int32_t, int32_t> clientReceive(int32_t sockfd, uint8_t* ret_buffer, sockaddr_in* server_address)
{
    struct sockaddr sender;
    socklen_t senderlen = sizeof(sender);

    uint8_t buffer[IP_MAXPACKET];
    if(Recvfrom(sockfd, buffer, IP_MAXPACKET, MSG_DONTWAIT, &sender, (socklen_t*) &senderlen) == -1)
    {
        return std::make_pair<int32_t, int32_t>(-1, -1);
    }

    if((((sockaddr_in*)&sender)->sin_port != server_address->sin_port) || 
       (((sockaddr_in*)&sender)->sin_addr.s_addr != server_address->sin_addr.s_addr))
        {
           return std::make_pair<int32_t, int32_t>(-1, -1);
        }

    std::stringstream message_stream;
    message_stream << buffer;
    std::string header_str;
    message_stream >> header_str; //get rid of DATA

    int32_t start, len;

    message_stream >> header_str; //handle start bit
    start = std::stoi(header_str);

    message_stream >> header_str; // handle data length
    len = std::stoi(header_str);
    std::pair<int32_t, int32_t> returned_pair = 
            std::make_pair<int32_t, int32_t>(std::move(start), std::move(len));

    uint8_t* data_ptr = (uint8_t*)memchr(buffer, '\n', IP_MAXPACKET) + 1; //find where header ends
    std::memcpy(ret_buffer, data_ptr, len); //discard header and put only part of file in buffer

    return returned_pair;
}

#endif
