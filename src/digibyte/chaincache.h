// Copyright (c) 2021 The Digibyte developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef DIGIBYTE_CHAINCACHE_H
#define DIGIBYTE_CHAINCACHE_H

#include <chain.h>
#include <digibyte/dgbchainparams.h>
#include <digibyte/multialgo.h>
#include <pow.h>

#include <sys/stat.h>

extern bool cacheComplete;

const int maxCacheHeight = 12500000;

bool init_cachefile(const DGBConsensus::Params& params);
arith_uint256* returnChainWork(int nHeight);
void writeAtHeight(int nHeight, arith_uint256 data);

#endif // DIGIBYTE_CHAINCACHE_H
