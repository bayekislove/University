/* Kacper Bajkiewicz 314438 */

#include <iostream>
#include <arpa/inet.h>
#include <fcntl.h>
#include <string>
#include <cassert>

#include "udp.cpp"

static inline int32_t getLen(int32_t bytes_saved, int32_t file_size)
{
    return bytes_saved < file_size - WINDOW_ENTRY_SIZE ? WINDOW_ENTRY_SIZE : file_size - bytes_saved;
}

static inline int32_t getNextStartByte(int32_t start_byte)
{
    return start_byte + WINDOW_ENTRY_SIZE;
}

void saveToFile(FILE* file, uint8_t* buffer, uint32_t len)
{
    ssize_t bytes = std::fwrite(buffer, sizeof(uint8_t), len, file);
    assert(bytes == len);
}

//this code is disgusting and I'm terribly sorry for anyone who'll have to read it
int main(int argc, char** argv)
{
    struct sockaddr_in server_address;
	bzero(&server_address, sizeof(server_address));
    server_address.sin_family = AF_INET;
	server_address.sin_port = htons(std::stoi(argv[2]));

    if(inet_pton(AF_INET, argv[1], &server_address.sin_addr) != 1)
    {
        fprintf(stderr, "Transport needs valid address to run\n");
    }

    int32_t file_len = std::stoi(argv[4]);

    int32_t socketfd;
    if((socketfd = Socket(AF_INET, SOCK_DGRAM, 0)) < 0) 
    {
		return EXIT_FAILURE;
	}

    FILE* output;
    output = fopen(argv[3], "w");
    
    int32_t saved_bytes = 0;
    int32_t max_byte_sent = -WINDOW_ENTRY_SIZE;

    std::map<int32_t, uint8_t*> _window;
    std::unordered_set<int32_t> acknowledged;

    struct timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = 200;

    while(saved_bytes < file_len)
    {
        fd_set rfds;
        FD_ZERO(&rfds);
        FD_SET(socketfd, &rfds);

        while(_window.size() < MAX_WINDOW_SIZE && getNextStartByte(max_byte_sent) < file_len)
        {
            max_byte_sent = getNextStartByte(max_byte_sent);
            //clientSend(socketfd, &server_address, max_byte_sent, getLen(max_byte_sent, file_len));
            _window[max_byte_sent] = nullptr;
        }

        for(auto const& entry : _window)
        {
            if(acknowledged.find(entry.first) == acknowledged.end())
            {
                clientSend(socketfd, &server_address, entry.first, getLen(entry.first, file_len));
            }
        }

        for(;;) //read while its anything to read
        {   
            if(Select(socketfd + 1, &rfds, NULL, NULL, &timeout) == 0) //no response after 1 sec, resend all unack datagrams
            {   
                timeout.tv_sec = 0;
                timeout.tv_usec = 500; //set new timeout
            }

            uint8_t* file_buffer = new uint8_t[1000];
            std::pair<int32_t, int32_t> start_len = clientReceive(socketfd, file_buffer, &server_address);

            if(start_len.first == -1) //nothing was read
            {
                delete file_buffer;
                break;
            }

            if(acknowledged.find(start_len.first) == acknowledged.end()) //this package was not yet received
            {
                _window[start_len.first] = file_buffer;
                acknowledged.insert(start_len.first);
            }
            else 
            {
                delete file_buffer;
            }

            while(acknowledged.find(saved_bytes) != acknowledged.end()) //n first acknowledged datagrams can be saved to a file
            {
                saveToFile(output, _window[saved_bytes], getLen(saved_bytes, file_len));
                delete _window[saved_bytes];
                _window.erase(saved_bytes);
                saved_bytes = getNextStartByte(saved_bytes);
                std::cout << "I received " << ((float)saved_bytes / (float)file_len)*100.0 << "% bytes" << std::endl; 
            }
        }
    }

    fclose(output);
    return EXIT_SUCCESS;
}