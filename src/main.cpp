#include <iostream>

#ifndef DEBUG
#define DEBUG
#endif
#include "Block.hpp"

int main() {
    qb::BlockChain bc(16);

    bc.addBlock("Send 1 BTC to Ivan");
    bc.addBlock("Send 2 more BTC to Ivan");

    for(auto it = bc.begin(); it != bc.end(); ++it) {
        it->print();
    }

    return 0;
}