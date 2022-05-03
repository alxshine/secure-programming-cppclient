#include "TCP.h"
#include <iostream>

using namespace std;

int main(void)
{
    cout << "Hello" << endl;
    auto tcp = TCP("example.mitmproxy.org", "8443");

    tcp.send("test");
    tcp.receive();
}