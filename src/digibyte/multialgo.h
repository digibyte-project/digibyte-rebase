// Copyright (c) 2014-2021 The Digibyte developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef DIGIBYTE_MULTIALGO_H
#define DIGIBYTE_MULTIALGO_H

#include <consensus/params.h>
#include <digibyte/dgbchainparams.h>
#include <util/system.h>

class CBlockIndex;

enum {
    ALGO_UNKNOWN = -1,
    ALGO_SHA256D = 0,
    ALGO_SCRYPT = 1,
    ALGO_GROESTL = 2,
    ALGO_SKEIN = 3,
    ALGO_QUBIT = 4,
    ALGO_ODO = 7,
    NUM_ALGOS_IMPL
};

enum {
    BLOCK_VERSION_DEFAULT = 2,
    BLOCK_VERSION_ALGO = (15 << 8),
    BLOCK_VERSION_SCRYPT = (0 << 8),
    BLOCK_VERSION_SHA256D = (2 << 8),
    BLOCK_VERSION_GROESTL = (4 << 8),
    BLOCK_VERSION_SKEIN = (6 << 8),
    BLOCK_VERSION_QUBIT = (8 << 8),
    BLOCK_VERSION_ODO = (14 << 8),
};

int GetAlgoWorkFactor(int nHeight, int algo);
int GetAlgo(int nVersion);
int GetVersionForAlgo(int algo);
std::string GetAlgoName(int Algo);
int GetAlgoByName(std::string strAlgo, int fallback);
int GetAlgoByIndex(const CBlockIndex* pindex);
std::string GetAlgoNameByIndex(const CBlockIndex* pindex);
uint32_t OdoKey(const DGBConsensus::Params& params, uint32_t nTime);

#endif // DIGIBYTE_MULTIALGO_H
