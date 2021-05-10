#ifndef QB_BLOCK_HPP
#define QB_BLOCK_HPP

#include <chrono>
#include <list>
#include <string>

#include "types.hpp"

namespace qb {
    class Block {
    public:
        Block(std::string data, std::string prevBlockHash, int64 targetBit);
        ~Block() = default;

    public:
        bool isValid();
#ifdef DEBUG
        void print();
#endif

    private:
        void setHash(int64 targetBit);

    private:
        std::chrono::_V2::system_clock::time_point timestamp;
        std::string data;
        std::string prevBlockHash;
        std::string hash;
        int64 nonce;

        friend class BlockChain;
    };

    class BlockChain {
    public:
        BlockChain(int64 targetBit);
        ~BlockChain() = default;

    public:
        std::list<Block>::iterator &begin();
        std::list<Block>::iterator &end();
        std::size_t size();

    public:
        void addBlock(std::string data);

    private:
        std::list<Block> list;
        std::list<Block>::iterator iterator;
        int64 targetBit;
    };
}

#endif