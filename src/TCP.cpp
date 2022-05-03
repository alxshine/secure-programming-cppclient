#include "TCP.h"
#include <stdexcept>
#include <sys/socket.h> // for getaddrinfo, connect
#include <sys/types.h>  // for getaddrinfo
#include <netdb.h>
#include <fcntl.h>
#include <unistd.h>
#include <memory>

#include <iostream>

TCP::TCP(std::string hostname, std::string port) : hostname(hostname), port(port)
{
    struct addrinfo hints;
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    struct addrinfo *address_info; // TODO: wrap in mini class
    int status = getaddrinfo(hostname.c_str(), port.c_str(), &hints, &address_info);
    if (status != 0)
    {
        // FIXME: addrinfo may leak
        throw std::runtime_error("error getting address info");
    }

    sock_fd = socket(address_info->ai_family, address_info->ai_socktype, address_info->ai_protocol);
    if (sock_fd < 0)
    {
        freeaddrinfo(address_info);
        throw std::runtime_error("error creating socket");
    }

    status = connect(sock_fd, address_info->ai_addr, address_info->ai_addrlen);
    if (status < 0)
    {
        freeaddrinfo(address_info);
        throw std::runtime_error("error connecting to remote");
    }

    int flags = fcntl(sock_fd, F_GETFL, 0);
    if (flags < 0)
    {
        freeaddrinfo(address_info);
        throw std::runtime_error("error getting flags");
    }

    flags = fcntl(sock_fd, F_SETFL, flags | O_NONBLOCK);
    if (flags < 0)
    {
        freeaddrinfo(address_info);
        throw std::runtime_error("error setting flags");
    }
}

TCP::~TCP() noexcept
{
    if (sock_fd)
        close(sock_fd);
}

void TCP::send(std::string message)
{
    std::cout << "hello, this is TCP::send" << message << std::endl;
}

std::string TCP::receive()
{
    return "hello, this is TCP:receive";
}