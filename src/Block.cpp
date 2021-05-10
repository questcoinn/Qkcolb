#include <ctime>

#include "Block.hpp"
#include "sha256.hpp"

#ifdef DEBUG
#include <iostream>
#endif

qb::Block::Block(std::string data, std::string prevBlockHash, int64 targetBit)
    :data(data)
    ,prevBlockHash(prevBlockHash)
{
    this->timestamp = std::chrono::system_clock::now();
    this->setHash(targetBit);
}

void qb::Block::setHash(int64 targetBit) {
    std::string _timestamp = std::to_string(std::chrono::system_clock::to_time_t(this->timestamp));
    std::string targetHash = "";
    for(int i = 0; i < 64; i++) {
        if(i != (targetBit - 1) / 4) {
            targetHash += '0';
        }
        else if(targetBit % 4 == 0) {
            targetHash += '1';
        }
        else if(targetBit % 4 == 3) {
            targetHash += '2';
        }
        else if(targetBit % 4 == 2) {
            targetHash += '4';
        }
        else {
            targetHash += '8';
        }
    }

#ifdef DEBUG
    std::cout << "Mining the block containing \"" << this->data << "\"\n";
#endif
    for(int64 salt = 0; salt < INT64_MAX; salt++) {
        std::string _salt = std::to_string(salt);
        std::string newHash = qb::sha256(this->prevBlockHash + this->data + _timestamp + _salt);
#ifdef DEBUG
        std::cout << "\r" << newHash;
#endif
        if(newHash < targetHash) {
            this->hash = newHash;
            this->nonce = salt;
            break;
        }
    }
#ifdef DEBUG
    std::cout << "\n\n";
#endif
}

bool qb::Block::isValid() {
    std::string _timestamp = std::to_string(std::chrono::system_clock::to_time_t(this->timestamp));
    std::string _nonce = std::to_string(this->nonce);
    return this->hash == qb::sha256(this->prevBlockHash + this->data + _timestamp + _nonce);
}

#ifdef DEBUG
void qb::Block::print() {
    std::cout << "Prev. hash: " << std::hex << this->prevBlockHash << "\n";
    std::cout << "Data: " << std::hex << this->data << "\n";
    std::cout << "Hash: " << std::hex << this->hash << "\n";
    std::cout << "\n";
}
#endif

qb::BlockChain::BlockChain(int64 targetBit)
    :targetBit(targetBit)
{
    this->list = std::list<qb::Block>();
    this->list.push_back(qb::Block("Genesis Block", "", this->targetBit));
}

std::list<qb::Block>::iterator &qb::BlockChain::begin() {
    this->iterator = this->list.begin();
    return this->iterator;
}

std::list<qb::Block>::iterator &qb::BlockChain::end() {
    this->iterator = this->list.end();
    return this->iterator;
}

std::size_t qb::BlockChain::size() {
    return this->list.size();
}

void qb::BlockChain::addBlock(std::string data) {
    qb::Block newBlock(data, this->list.back().hash, this->targetBit);
    if(newBlock.isValid()) {
        this->list.push_back(newBlock);
    }
#ifdef DEBUG
    else {
        std::cout << "Failed mining for some reason\n";
    }
#endif
}