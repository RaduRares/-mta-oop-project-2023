#pragma once
#include"PC.h"
#include<iostream>

class Switch {
public:
    void ConnectPC(PC& pc, int port) {
        if (port >= 0 && port < numPorts) {
            // Connect the PC to the specified port
            connectedPCs[port] = &pc;
        }
    }

private:
    static const int numPorts = 2;
    PC* connectedPCs[numPorts] = { nullptr, nullptr };
};
