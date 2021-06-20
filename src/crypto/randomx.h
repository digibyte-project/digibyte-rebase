// Copyright (c) 2020 barrystyle
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef DIGIBYTE_RANDOMX_H
#define DIGIBYTE_RANDOMX_H

#include <crypto/randomx/randomx.h>
#include <crypto/seedmanager.h>
#include <uint256.h>

#include <map>

class uint256;
class CBlockIndex;
class CBlockHeader;
class SeedManager;
class RandomXHasher;

extern SeedManager seedmanager;
extern RandomXHasher* blk_reader;

class RandomXHasher {
private:
    bool is_vm_init { false };
    bool is_cache_init { false };
    bool seed_changed { false };
    bool debug { true };

    randomx_flags flags {};
    randomx_vm* vm { nullptr };
    randomx_cache* cache { nullptr };

public:
    uint256 lastseed {};
    uint256 currentseed {};
    std::map<int, uint256> seedcache;

    void init();
    bool hasseedchanged();
    void cacheinit();
    void cacherebuild();
    void vminit();
    void shutoff();
    void hash(const char* input, char* output, int len, int height);
};

#endif // DIGIBYTE_RANDOMX_H
