// Copyright (c) 2021 The Digibyte developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <digibyte/digiassets.h>

void ReadBlockFromDiskFast(CBlock& block, const CBlockIndex* pindex)
{
    CAutoFile filein(OpenBlockFile(pindex->GetBlockPos(), true), SER_DISK, CLIENT_VERSION);
    filein >> block;
}

void digithread(const Consensus::Params& consensusParams)
{
    int height = 9000000;
    int nowHeight = ::ChainActive().Height();
    while (height++ < nowHeight) {
        CBlock block;
        CBlockIndex* pindex = ::ChainActive()[height];
        ReadBlockFromDiskFast(block, pindex);
        {
            for (unsigned int z = 0; z < block.vtx.size(); z++) {
                const CTransaction& tx = *(block.vtx[z]);
                for (unsigned int o = 0; o < tx.vout.size(); o++) {
                    const CScript& outScript = tx.vout[o].scriptPubKey;
                    // unspendable, but not the segwit commitment (6a24aa..)
                    if (outScript.IsUnspendable() && (outScript[1] != 0x24 && outScript[2] != 0xaa)) {
                        LogPrintf("height %d tx %s vout %d script %s\n", height, tx.GetHash().ToString(), o, HexStr(outScript));
                    }
                }
            }
        }
    }
}
