// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2019 The Bitcoin Core developers
// Copyright (c) 2014-2021 The DigiByte developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <primitives/block.h>

#include <arith_uint256.h>
#include <crypto/hashgroestl.h>
#include <crypto/hashodo.h>
#include <crypto/hashqubit.h>
#include <crypto/hashskein.h>
#include <crypto/scrypt.h>
#include <primitives/moneroheader.h>
#include <digibyte/multialgo.h>
#include <hash.h>
#include <tinyformat.h>

std::map<int, uint256> seedcache;

void CBlockHeader::SetAlgo(int algo)
{
    nVersion |= GetVersionForAlgo(algo);
}

uint256 CBlockHeader::GetHash() const
{
    return SerializeHash(*this);
}

uint256 CBlockHeader::GetPoWHash(int height) const
{
    if (!powHash.IsNull())
        return powHash;

    uint256 thash;
    const int hashAlgo = GetAlgo(this->nVersion);
    const DGBConsensus::Params& params = DGBParams().GetConsensus();

    //! maintain seedcache conservatively
    if (height % params.nEpochLength == 0)
        seedcache[height] = this->hashMerkleRoot;

    switch (hashAlgo) {
        case ALGO_SHA256D: {
            const uint256 cache = GetHash();
            SetCache(cache);
            return cache;
        }
        case ALGO_SCRYPT: {
            scrypt_1024_1_1_256(((char*)&(nVersion)), ((char*)&(thash)));
            SetCache(thash);
            return thash;
        }
        case ALGO_GROESTL: {
            const uint256 cache = HashGroestl(((char*)&(nVersion)), ((char*)&((&(nNonce))[1])));
            SetCache(cache);
            return cache;
        }
        case ALGO_SKEIN: {
            const uint256 cache = HashSkein(((char*)&(nVersion)), ((char*)&((&(nNonce))[1])));
            SetCache(cache);
            return cache;
        }
        case ALGO_QUBIT: {
            const uint256 cache = HashQubit(((char*)&(nVersion)), ((char*)&((&(nNonce))[1])));
            SetCache(cache);
            return cache;
        }
        case ALGO_ODO: {
            uint32_t key = OdoKey(params, nTime);
            const uint256 cache = HashOdo(((char*)&(nVersion)), ((char*)&((&(nNonce))[1])), key);
            SetCache(cache);
            return cache;
        }
        case ALGO_RANDOMX: {
            seedmanager.updateHeight(height);
            serialize_monero_hash((const char*)this, ((char*)&(thash)), blk_reader, height);
            SetCache(thash);
            return thash;
        }
        case ALGO_UNKNOWN:
            return ArithToUint256(~arith_uint256(0));
    }
    assert(false);
    return GetHash();
}

std::string CBlock::ToString() const
{
    std::stringstream s;
    s << strprintf("CBlock(hash=%s, ver=0x%08x, pow_algo=%d, hashPrevBlock=%s, hashMerkleRoot=%s, nTime=%u, nBits=%08x, nNonce=%u, vtx=%u)\n",
        GetHash().ToString(),
        nVersion,
        GetAlgo(nVersion),
        hashPrevBlock.ToString(),
        hashMerkleRoot.ToString(),
        nTime, nBits, nNonce,
        vtx.size());
    for (const auto& tx : vtx) {
        s << "  " << tx->ToString() << "\n";
    }
    return s.str();
}
