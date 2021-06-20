// Copyright (c) 2020 barrystyle
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef DIGIBYTE_SEEDMGR_H
#define DIGIBYTE_SEEDMGR_H

#include <uint256.h>
#include <util/system.h>

class uint256;
class SeedManager;

class SeedManager {
private:
    int lastEpoch{0};
    uint256 lastseed{};
    uint256 currentseed{};

public:
    int getLastEpoch();
    void setLastEpoch(int epoch);
    int currentEpoch(int height);
    void setSeedhash(uint256 hash);
    uint256 getLastSeed();
    uint256 getSeedHash(int epoch);
    void updateHeight(int height);
};

#endif // DIGIBYTE_SEEDMGR_H
