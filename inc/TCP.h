#pragma once
#include "Connection.h"

class TCP : public Connection
{
public:
    TCP(std::string hostname, std::string port);
    ~TCP() noexcept;
    void send(std::string) override;
    std::string receive() override;

private:
    int sock_fd;
    std::string hostname, port;
};