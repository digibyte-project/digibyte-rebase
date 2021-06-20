// Copyright (c) 2020 barrystyle
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#include <digibyte/dgbchainparams.h>

int SeedManager::getLastEpoch()
{
    return lastEpoch;
}

void SeedManager::setLastEpoch(int epoch)
{
    lastEpoch = epoch;
}

int SeedManager::currentEpoch(int height)
{
    const int epochlen = DGBParams().GetConsensus().nEpochLength;
    return (height / epochlen) * epochlen;
}

void SeedManager::setSeedhash(uint256 hash)
{
    lastseed = currentseed;
    currentseed = hash;
}

uint256 SeedManager::getLastSeed()
{
    return lastseed;
}

uint256 SeedManager::getSeedHash(int epoch)
{
    uint256 seedhash {};
    const auto it = seedcache.find(epoch);
    if (it != seedcache.end())
        seedhash = it->second;
    return seedhash;
}

void SeedManager::updateHeight(int height)
{
    const int epoch = currentEpoch(height);
    if (epoch != this->getLastEpoch()) {
        uint256 newseed = getSeedHash(epoch);
        LogPrintf("%s - seed changed from %s to %s\n", __func__, lastseed.ToString(), newseed.ToString());
        lastseed = newseed;
        setLastEpoch(epoch);
    }
}
