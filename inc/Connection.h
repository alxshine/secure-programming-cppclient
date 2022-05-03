#pragma once
#include <string>

struct Connection
{
    virtual void send(std::string) = 0;
    virtual std::string receive() = 0;
};