// Copyright (c) 2014-2021 The Digibyte developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef DIGIBYTE_CONSENSUS_PARAMS_H
#define DIGIBYTE_CONSENSUS_PARAMS_H

#include <consensus/params.h>
#include <uint256.h>

#include <limits>
#include <map>

namespace DGBConsensus {

struct Params {

    std::map<int, uint256> initialTarget;

    int64_t nTargetTimespan;
    int64_t nTargetSpacing;
    int64_t nInterval;
    int64_t nDiffChangeTarget;
    int64_t nTargetTimespanRe;
    int64_t nTargetSpacingRe;
    int64_t nIntervalRe;
    int64_t patchBlockRewardDuration;
    int64_t patchBlockRewardDuration2;

    int64_t nAveragingInterval;
    int64_t multiAlgoTargetSpacing;
    int64_t multiAlgoTargetSpacingV4;
    int64_t nAveragingTargetTimespan;
    int64_t nAveragingTargetTimespanV4;

    int64_t nMaxAdjustDown;
    int64_t nMaxAdjustUp;
    int64_t nMaxAdjustDownV3;
    int64_t nMaxAdjustUpV3;
    int64_t nMaxAdjustDownV4;
    int64_t nMaxAdjustUpV4;

    int64_t nMinActualTimespan;
    int64_t nMaxActualTimespan;
    int64_t nMinActualTimespanV3;
    int64_t nMaxActualTimespanV3;
    int64_t nMinActualTimespanV4;
    int64_t nMaxActualTimespanV4;

    int64_t nLocalTargetAdjustment;
    int64_t nLocalDifficultyAdjustment;

    int64_t multiAlgoDiffChangeTarget;
    int64_t alwaysUpdateDiffChangeTarget;
    int64_t workComputationChangeTarget;
    int64_t algoSwapChangeTarget;
    int64_t maxConcurrentAlgorithms;

    int nEpochLength;
    uint32_t nOdoShapechangeInterval;
};

} // namespace DGBConsensus

#endif // DIGIBYTE_CONSENSUS_PARAMS_H
