// Copyright (c) 2021 The Digibyte developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <digibyte/chaincache.h>

//! for chaincache
FILE* cachefile;
bool cacheExists{false};
bool cacheComplete{false};
uint8_t* ptr{nullptr};

inline fs::path cache_location()
{
    std::string cache_filename = "chainwork.bin";
    const fs::path datadir = GetDataDir();
    return fs::path(datadir / cache_filename);
}

bool test_cacheexists()
{
    if (access(cache_location().string().c_str(), F_OK) == 0)
        return true;
    return false;
}

bool init_createcache(const DGBConsensus::Params& params)
{
    cachefile = fopen(cache_location().string().c_str(), "w+");
    if (cachefile == nullptr)
        return false;
    uint8_t chunk[32];
    memset(chunk,0,sizeof(chunk));
    for (int i=0; i< params.maxCacheHeight; i++) {
         fwrite(&chunk, sizeof(chunk), 1, cachefile);
    }
    fclose(cachefile);
    return true;
}

bool init_cachefile(const DGBConsensus::Params& params)
{
    //! test if file exists and is right size
    if (!cacheExists) {
        if (test_cacheexists()) {
            struct stat st;
            stat(cache_location().string().c_str(), &st);
            if (st.st_size == params.maxCacheHeight * 32) {
                cacheExists = true;
            }
        }
    }

    //! if not, create it
    if (!cacheExists) {
        if (!init_createcache(params)) {
            LogPrintf("Error creating the cache file\n");
            return false;
        }
    }

    //! open once we know its safe to do so
    if ((cachefile = fopen(cache_location().string().c_str(), "r+")) == nullptr)
        return false;

    //! create storage space (12.5m headers ~ 400mb)
    ptr = (uint8_t*)malloc(params.maxCacheHeight * 32);
    if (!ptr) return false;
    memset(ptr, 0, params.maxCacheHeight * 32);

    //! read in what we have
    arith_uint256 chainWorkSum{0};
    for (int n = params.workComputationChangeTarget; n < params.maxCacheHeight; n++) {
        fseek(cachefile, n * 32, SEEK_SET);
        fread(&ptr[n * 32], 32, 1, cachefile);
        arith_uint256* p = (arith_uint256*)&ptr[n * 32];
        chainWorkSum += *p;
    }

    cacheComplete = chainWorkSum == UintToArith256(uint256S("0000000000000000000000000000000000000000000b300fe763a06e895cc480"));

    LogPrintf("chainwork %s @ height %d (complete %s)\n", chainWorkSum.ToString(), params.maxCacheHeight, cacheComplete ? "Y" : "N");

    return true;
}

arith_uint256* returnChainWork(int nHeight)
{
    return (arith_uint256*)&ptr[nHeight * 32];
}

void writeAtHeight(int nHeight, arith_uint256 data)
{
    if (nHeight >= maxCacheHeight)
        return;
    fseek(cachefile, nHeight * 32, SEEK_SET);
    fwrite(&data, 32, 1, cachefile);
}
