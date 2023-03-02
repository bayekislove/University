#include <iostream>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sstream>
#include <limits.h>
#include <stdlib.h>

#include "HttpResponse.cpp"

#define ERROR(str) { fprintf(stderr, "%s: %s\n", str, strerror(errno)); exit(EXIT_FAILURE); }
#define BUFFER_SIZE 10000000    // 10 MB

uint8_t recv_buffer[BUFFER_SIZE+1];
uint8_t resp_buffer[BUFFER_SIZE+1];

int checkIfDirectory(std::string path)
{
    struct stat st;
    if(stat(path.c_str(), &st) == 0)
    {
        return st.st_mode & S_IFDIR;
    }
    return 0;
}

int checkIfValidFile(std::string path)
{
    struct stat st;
    return stat(path.c_str(), &st) == 0;
}

int checkIfSameDomain(std::string dir1, std::string dir2, std::string core)
{
    try
    {
        std::string pathcore = std::string(realpath(core.c_str(), NULL));
        std::string d1_realpath = std::string(realpath(dir1.c_str(), NULL));
        std::string d2_realpath = std::string(realpath(dir2.c_str(), NULL));
        d1_realpath = d1_realpath.substr(pathcore.length() + 1);
        d2_realpath = d2_realpath.substr(pathcore.length() + 1);

        d1_realpath = d1_realpath.substr(0, d1_realpath.find("/"));
        d2_realpath = d2_realpath.substr(0, d2_realpath.find("/"));

        return d1_realpath == d2_realpath;
    }
    catch(const std::exception& e)
    {
        return true;
    }
}

void inline printInvocationError()
{
    fprintf(stderr, "./webserver [port] [directory]\n");
    exit(EXIT_FAILURE);
}

ssize_t recv_till_separator(int fd, uint8_t *buffer, size_t buffer_size, unsigned int timeout)
{
    struct timeval tv; tv.tv_sec = timeout; tv.tv_usec = 0;

    fd_set descriptors;
    FD_ZERO(&descriptors);
    FD_SET(fd, &descriptors);
    int ready = select(fd + 1, &descriptors, NULL, NULL, &tv);
    if (ready < 0)
        ERROR("select error");
    if (ready == 0)
        return -2;

    ssize_t bytes_read = recv(fd, buffer, buffer_size, 0);
    if (bytes_read < 0)
        ERROR("recv error");

    return bytes_read;
}

void send_all (int sockfd, uint8_t* buffer, size_t n)
{
    size_t n_left = n;
    while (n_left > 0) {
        ssize_t bytes_sent = send(sockfd, buffer, n_left, 0);
        if (bytes_sent < 0)
            ERROR("send error");
        n_left -= bytes_sent;
        buffer += bytes_sent;
    }
}

int main(int argc, char** argv)
{
    if(argc != 3)
    {
        printInvocationError();
    }
    int32_t port;
    try
    {
        port = std::stoi(argv[1]);
    }
    catch(const std::exception& e)
    {
        fprintf(stderr, "Error while resolving port number\n");
        printInvocationError();
    }
    
    std::string path = argv[2];
    std::string domain = "";
    if(!checkIfDirectory(path))
    {
        fprintf(stderr, "Not a directory\n");
        printInvocationError();
    }

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        ERROR("socket error");

    struct sockaddr_in server_address;
    bzero(&server_address, sizeof(server_address));
    server_address.sin_family      = AF_INET;
    server_address.sin_port        = htons(port);
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(sockfd, (struct sockaddr*) &server_address, sizeof(server_address)) < 0)
        ERROR("bind error");

    if (listen(sockfd, 64) < 0)
        ERROR("listen error");

    for (;;) {

        int connected_sockfd = accept(sockfd, NULL, NULL);
        if (connected_sockfd < 0)
            ERROR("accept error")

        ssize_t bytes_read = recv_till_separator(connected_sockfd, recv_buffer, BUFFER_SIZE, 1);
        if (bytes_read == -2)
        {
            printf("Timeout\n");
        } 
        else if (bytes_read == 0)
        {
            printf("Client closed connection");
        }
        else
        {
            std::stringstream req_stream;
            req_stream << recv_buffer;
            std::string req_string;
            req_stream >> req_string;

            if(req_string != "GET")
            {
                send_all(connected_sockfd, (uint8_t*) NotImplementedReponse().c_str(), NotImplementedReponse().size());
            }
            std::string domain_path;
            req_stream >> domain_path;

            req_stream >> req_string;
            req_stream >> req_string;
            req_stream >> domain;
            domain = domain.substr(0, domain.find_first_of(":"));
            domain_path = path + "/" + domain + domain_path;

            while(req_string != "Connection:" && ((req_stream.rdbuf()->in_avail()) > 0))
            {
                req_stream >> req_string;
            }
            req_stream >> req_string;

            std::string resp;

            if(!checkIfSameDomain(path + '/' + domain, domain_path, path))
            {
                resp = ForbiddenReponse();
            }
            else if(checkIfDirectory(domain_path))
            {
                resp = MovedPermanentlyResponse();
            }
            else if(checkIfValidFile(domain_path))
            {
                resp = OkResponse(domain_path);
            }
            else
            {
                resp = NotFoundReponse();
            }
            send_all(connected_sockfd, (uint8_t*) resp.c_str(), resp.size());

            if (close(connected_sockfd) < 0)
               ERROR("close error");
        }
    }
}
