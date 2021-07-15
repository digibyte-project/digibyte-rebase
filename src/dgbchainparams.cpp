// Copyright (c) 2014-2021 The Digibyte developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <digibyte/dgbchainparams.h>

#include <chainparams.h>
#include <digibyte/multialgo.h>
#include <tinyformat.h>
#include <util/system.h>
#include <util/strencodings.h>
#include <versionbitsinfo.h>

#include <assert.h>

#include <limits>

/**
 * Main network
 */
class CMainParams : public DGBChainParams {
public:
    CMainParams() {
        consensus.initialTarget[ALGO_ODO] = uint256S("0000000000ffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nDiffChangeTarget = 67200;
        consensus.patchBlockRewardDuration = 10080;
        consensus.patchBlockRewardDuration2 = 80160;
        consensus.nTargetTimespanRe = 1 * 60;
        consensus.nTargetSpacingRe = 1 * 60;
        consensus.nTargetTimespan =  0.10 * 24 * 60 * 60; // 2.4 hours
        consensus.nTargetSpacing = 60; // 60 seconds
        consensus.nInterval = consensus.nTargetTimespan / consensus.nTargetSpacing;
        consensus.nIntervalRe = consensus.nTargetTimespanRe / consensus.nTargetSpacingRe;
        consensus.nAveragingInterval = 10;
        consensus.multiAlgoTargetSpacing = 30 * NUM_ALGOS;
        consensus.multiAlgoTargetSpacingV4 = 15 * NUM_ALGOS;
        consensus.nAveragingTargetTimespan = consensus.nAveragingInterval * consensus.multiAlgoTargetSpacing;
        consensus.nAveragingTargetTimespanV4 = consensus.nAveragingInterval * consensus.multiAlgoTargetSpacingV4;
        consensus.nMaxAdjustDown = 40;
        consensus.nMaxAdjustUp = 20;
        consensus.nMaxAdjustDownV3 = 16;
        consensus.nMaxAdjustUpV3 = 8;
        consensus.nMaxAdjustDownV4 = 16;
        consensus.nMaxAdjustUpV4 = 8;
        consensus.nMinActualTimespan = consensus.nAveragingTargetTimespan * (100 - consensus.nMaxAdjustUp) / 100;
        consensus.nMaxActualTimespan = consensus.nAveragingTargetTimespan * (100 + consensus.nMaxAdjustDown) / 100;
        consensus.nMinActualTimespanV3 = consensus.nAveragingTargetTimespan * (100 - consensus.nMaxAdjustUpV3) / 100;
        consensus.nMaxActualTimespanV3 = consensus.nAveragingTargetTimespan * (100 + consensus.nMaxAdjustDownV3) / 100;
        consensus.nMinActualTimespanV4 = consensus.nAveragingTargetTimespanV4 * (100 - consensus.nMaxAdjustUpV4) / 100;
        consensus.nMaxActualTimespanV4 = consensus.nAveragingTargetTimespanV4 * (100 + consensus.nMaxAdjustDownV4) / 100;
        consensus.nLocalTargetAdjustment = 4;
        consensus.nLocalDifficultyAdjustment = 4;
        consensus.multiAlgoDiffChangeTarget = 145000;
        consensus.alwaysUpdateDiffChangeTarget = 400000;
        consensus.workComputationChangeTarget = 1430000;
        consensus.algoSwapChangeTarget = 9100000;
        consensus.nOdoShapechangeInterval = 10*24*60*60;
        consensus.nEpochLength = std::numeric_limits<int>::max();
        consensus.maxCacheHeight = 13250000;
    }
};

/**
 * Testnet (v3)
 */
class CTestNetParams : public DGBChainParams {
public:
    CTestNetParams(const DGBChainParams& params = CMainParams()) {
        memcpy(this, &params, sizeof(params));
    }
};

/**
 * Signet
 */
class SigNetParams : public DGBChainParams {
public:
    SigNetParams(const DGBChainParams& params = CMainParams()) {
        memcpy(this, &params, sizeof(params));
    }
};

/**
 * Regression test
 */
class CRegTestParams : public DGBChainParams {
public:
    CRegTestParams(const DGBChainParams& params = CMainParams()) {
        memcpy(this, &params, sizeof(params));
    }
};

/**
 * Globally accessible class
 */
DGBChainParams globalDgbParams;

const DGBChainParams &DGBParams() {
    return globalDgbParams;
}

void SelectDGBParams(DGBChainParams& env, const std::string& chain) {
    if (chain == CBaseChainParams::MAIN) {
        env = CMainParams();
    } else if (chain == CBaseChainParams::TESTNET) {
        env = CTestNetParams();
    } else if (chain == CBaseChainParams::SIGNET) {
        env = SigNetParams();
    } else if (chain == CBaseChainParams::REGTEST) {
        env = CRegTestParams();
    }
}

void InitialiseDGBParams(const std::string& chain) {
    SelectDGBParams(globalDgbParams, chain);
}
