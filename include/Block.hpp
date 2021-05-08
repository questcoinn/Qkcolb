#ifndef QB_BLOCK_HPP
#define QB_BLOCK_HPP

#include <chrono>
#include <list>
#include <string>

namespace qb {
    class Block {
    public:
        Block(std::string data, std::string prevBlockHash);
        ~Block() = default;

#ifdef DEBUG
    public:
        void print();
#endif

    private:
        void setHash();

    private:
        std::chrono::_V2::system_clock::time_point timestamp;
        std::string data;
        std::string prevBlockHash;
        std::string hash;

        friend class BlockChain;
    };

    class BlockChain {
    public:
        BlockChain();
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
    };
}

#endif