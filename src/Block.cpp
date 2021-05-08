#include <ctime>

#include "Block.hpp"
#include "sha256.hpp"

#ifdef DEBUG
#include <iostream>
#endif

qb::Block::Block(std::string data, std::string prevBlockHash)
    :data(data)
    ,prevBlockHash(prevBlockHash)
    {
    this->timestamp = std::chrono::system_clock::now();
    this->setHash();
}

void qb::Block::setHash() {
    std::string _timestamp = std::to_string(std::chrono::system_clock::to_time_t(this->timestamp));
    this->hash = qb::sha256(this->prevBlockHash + this->data + _timestamp);
}

#ifdef DEBUG
void qb::Block::print() {
    std::cout << "Prev. hash: " << std::hex << this->prevBlockHash << "\n";
    std::cout << "Data: " << std::hex << this->data << "\n";
    std::cout << "Hash: " << std::hex << this->hash << "\n";
    std::cout << "\n";
}
#endif

qb::BlockChain::BlockChain() {
    this->list = std::list<qb::Block>();
    this->list.push_back(qb::Block("Genesis Block", ""));
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
    qb::Block newBlock(data, this->list.back().hash);
    this->list.push_back(newBlock);
}