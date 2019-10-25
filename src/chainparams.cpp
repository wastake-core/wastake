// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2019 The PIVX developers
// Copyright (c) 2019 The WaStake Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>
#include <limits>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of
	    (    0, uint256("0000291ef347ef8397f27d71de2403b2ce26858d2f1899d6dfbfe63e964ed061"))
    ;

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1571810400, // * UNIX timestamp of last checkpoint block
    2631,       // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    202         // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet = boost::assign::map_list_of(0, uint256("0"));
static const Checkpoints::CCheckpointData dataTestnet = {&mapCheckpointsTestnet,
	1571853600, 
	0, 
	250
	};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest = boost::assign::map_list_of(0, uint256("0"));
static const Checkpoints::CCheckpointData dataRegtest = {&mapCheckpointsRegtest, 
	1571871600, 
	0, 
	0
	};

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0x92;
        pchMessageStart[1] = 0xc9;
        pchMessageStart[2] = 0x8e;
        pchMessageStart[3] = 0xae;
        vAlertPubKey = ParseHex("0447bab810cca0993580e9cae35106c3b0aeb7d1c8cfc82cb04b9dbb1402402cb2180a479e6eb7edf95d96201fbfc8b6e540a470aca6bb6387fd97fa31aa2429b9");
        vGMPubKey = ParseHex("04c775253c56d07bab1f4eab1c5cb4beabeec77b5374407a8ded5bb5b13d0d786c527f4482ab67168cd8c3a1bc409e133776a682bde0404df85e63305334fc0e18");

        nDefaultPort = 62852;
        bnProofOfWorkLimit = ~uint256(0) >> 20;
        bnStartWork = ~uint256(0) >> 24;

        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetSpacing = 1 * 60;  // 2 minute
        nTargetSpacingSlowLaunch = 1 * 60; // before block 100
        nPoSTargetSpacing = 60;  // 1 minute
        nMaturity = 50;
        nMasternodeCountDrift = 3;
        nMaxMoneyOut = 7700000  * COIN;
//		nNewMasternodeCollateral_StartBlock = 86201; // (approximately)
//	    nNewMasternodeCollateral_GPBlock = 87641; // 1 week grace period to allow for masternodes to activate using the new collateral
//      nNewMasternode_Collateral = 3000;
//      nOriginalMasternode_Collateral = 1000;

        /** Height or Time Based Activations **/
        nLastPOWBlock = 500;
        nModifierUpdateBlock = std::numeric_limits<decltype(nModifierUpdateBlock)>::max();

        const char* pszTimestamp = "WaStake - Multi Asset Wallet Staking - October 23, 2019"; 
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 0 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("047e016fa60fc176e381b4e97170afb937e7efba1cdebc9dc11e6e9ab1fd70b8996347081ea43c90587ccd45f9ac883d8fd9cc90d66140551cea0c99ab7c6036b5") << OP_CHECKSIG;
        txNew.blob = "Genesis Tx";
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1571810400; //  Wednesday, October 23, 2019 6:00:00
        genesis.nBits = 0x1e0ffff0; // 
        genesis.nNonce = 31312;
		
        hashGenesisBlock = genesis.GetHash();

        assert(genesis.hashMerkleRoot == uint256("74cb201deca22f616d4de7bd3ea1bba23de80bbc55db03fe2524f3d966ac5916"));
        assert(hashGenesisBlock == uint256("0000291ef347ef8397f27d71de2403b2ce26858d2f1899d6dfbfe63e964ed061"));

        //vSeeds.clear();
	    vSeeds.push_back(CDNSSeedData("165.22.200.154", "165.22.200.154"));  // WaStake seed1
		vSeeds.push_back(CDNSSeedData("104.248.86.221", "104.248.86.221"));    // WaStake seed2

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,73);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,18);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,135);
        // WaStaKe BIP32 pubkeys start with 'xpub' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x33).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        // 	BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x98).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = true;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;

        nStakeInputMin = 1 * COIN;
        strDevFeeAddress = "WSkDeVfbQdf6eyM3RnZr1fKm4DCxXkWKnZ";

        strSporkKey = "041d4d3269ed00364ae63e1febd9b33b9f4c7922468e9f618ca01f9a94a1ed0132e9b4f3409649622ef406a23eafb4320838bf0cc373c66a1b655add8969618a73";
        strObfuscationPoolDummyAddress = "WZ1x6Ccym4tP9zBwMhcCeAdGMVAXr5io2J";
        nStartMasternodePaymentsBlock = 500;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0x7f;
        pchMessageStart[1] = 0xb3;
        pchMessageStart[2] = 0x8e;
        pchMessageStart[3] = 0xb7;
        vAlertPubKey = ParseHex("04719b54adae5a3bc9a4cf46f166e9e95311d92ed53c58e93a2d8554d67e6c053d4c62a1758c2666085d3db0038e081612a8dbc1cc098ac60b9720220dd0adadfc");
        vGMPubKey = ParseHex("046c6d7d9859d2242882ab302ecf9e061863cbd9bb702601acebd4d222ddd11b0a28fee1f684471fd3f9b53c9dbab61d3a869fa6294b0173cc467a69c76e840ce8");

        bnProofOfWorkLimit = ~uint256(0) >> 1;
        bnStartWork = bnProofOfWorkLimit;

        nDefaultPort = 82852;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetSpacing = 1 * 60;  // 1 minute
        nMaturity = 15;
        nMasternodeCountDrift = 4;
        nModifierUpdateBlock = std::numeric_limits<decltype(nModifierUpdateBlock)>::max();
        nMaxMoneyOut = 15400000 * COIN;

        genesis.nTime = 1571853600;
        genesis.nNonce = 64008;

        hashGenesisBlock = genesis.GetHash();

        assert(hashGenesisBlock == uint256("0000627739e0ba4b730d31b2dd910f2a94636f41d8574612c619c21d4016252e"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,135);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,21);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
        // Testnet wastake BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet wastake BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet wastake BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0xc9).convert_to_container<std::vector<unsigned char> >();

        //convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        nStakeInputMin = 1 * COIN;
        strDevFeeAddress = "wSKte34nsqUsiFhCSx7FVo8DTF1mfhdd4k";

        strSporkKey = "0449b497e18aeea34ac2ce1c753b5344479662cf3a9b1f126c8b8ae9bf6bf157352643532326a25634f9281c41516f7badfe25d233f4aa88b8a7e81caae90678a6";
        strObfuscationPoolDummyAddress = "wZM1uVwFhWXZsj8V5CgcQ5c39pKJzssiUq";
//      nStartMasternodePayments = 1567484300 + 500;

    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        strNetworkID = "regtest";
        pchMessageStart[0] = 0xdd;
        pchMessageStart[1] = 0xc9;
        pchMessageStart[2] = 0xa1;
        pchMessageStart[3] = 0xcd;

        bnStartWork = ~uint256(0) >> 20;

        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetSpacing = 1 * 60;
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1567570700;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 20012;

        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 82876;

        //assert(hashGenesisBlock == uint256("00005b9e2574ca2edce61f001a98bc04ff8c1a9b162dbb0fb7aed2f965a027d3"));

        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 82878;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fMineBlocksOnDemand = true;


    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    case CBaseChainParams::UNITTEST:
        return unitTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
