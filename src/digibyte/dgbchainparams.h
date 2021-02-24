// Copyright (c) 2014-2021 The Digibyte developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef DIGIBYTE_CHAINPARAMS_H
#define DIGIBYTE_CHAINPARAMS_H

#include <chainparams.h>
#include <digibyte/dgbconsensus.h>

class DGBChainParams
{
protected:
    DGBConsensus::Params consensus;
public:
    DGBChainParams() {}
    const DGBConsensus::Params& GetConsensus() const { return consensus; }
};

const DGBChainParams &DGBParams();
void SelectDGBParams(DGBChainParams& env, const std::string& chain);
void InitialiseDGBParams(const std::string& chain);

#endif // DIGIBYTE_CHAINPARAMS_H
