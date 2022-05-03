#pragma once

#include "Connection.h"

class TLS : public Connection
{
public:
    TLS(Connection conn);
}