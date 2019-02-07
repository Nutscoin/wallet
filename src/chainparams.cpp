// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
// Copyright (c) 2018 The NUTS developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "libzerocoin/Params.h"
#include "chainparams.h"
#include "random.h"
#include "util.h"
#include "utilstrencodings.h"
#include "masternode.h"

#include <assert.h>

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
    (0, uint256("000002c9131c15e37b47c77abea2fc9ac755bafa55ec9b33bc158e454a5c3b91"));
static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1547418980, // * UNIX timestamp of last checkpoint block
    0,          // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    100         // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256("0x001"));
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1547418980,
    0,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0x001"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1547418980,
    0,
    100};

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        pchMessageStart[0] = 0x7e;
        pchMessageStart[1] = 0x82;
        pchMessageStart[2] = 0x3f;
        pchMessageStart[3] = 0x4a;
        vAlertPubKey = ParseHex("0b880fb82967fbe513d9199d679f32431f3c629d91f2d868fb08be277024345b63c4b73c149fdf773a2243934aa3d11497483259c347df4996828b020b23c1f38d");
        nDefaultPort = 31500;
        bnProofOfWorkLimit = ~uint256(0) >> 20; // NUTS starting difficulty is 1 / 2^12
        nSubsidyHalvingInterval = 210000;
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // NUTS: 1 day
        nTargetSpacing = 1 * 60;  // NUTS: 1 minute
        nLastPOWBlock = 300;
        nMaturity = 59;
        nMasternodeCountDrift = 20;

        nModifierUpdateBlock = 615800;
        nMaxMoneyOut = 13000000 * COIN;

        const char* pszTimestamp = "Earth 13/Jan/2019 have no fear, monkey is here... monkey loves bananas...";

        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 50 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("02ce4fd2b310faed0247f03c4aeab3a67a872a81e568eec9d59dc3d0335c258b58") << OP_CHECKSIG;
	genesis.vtx.push_back(txNew); 
        genesis.hashPrevBlock = 0; 
        genesis.hashMerkleRoot = genesis.BuildMerkleTree(); 
        genesis.nVersion = 1;
        genesis.nTime = 1547418980;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 18181; 

		//Generating genesis block
/*
        genesis.nNonce   = 0;
        do {
            genesis.nNonce++;
            hashGenesisBlock = genesis.GetHash();
        } while(hashGenesisBlock > uint256("0x0001000000000000000000000000000000000000000000000000000000000000"));
	std::cout << "txNew:" << std::endl << txNew.ToString() << std::endl << std::endl;
        std::cout <<"hashGenesisBlock:" << std::endl;
        std::cout << hashGenesisBlock.ToString() << std::endl << std::endl;
 
        std::cout <<"genesis:" << std::endl << std::endl;
        std::cout << genesis.ToString() << std::endl;   
 
*/
        //End generating genesis block/
		
        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("000002c9131c15e37b47c77abea2fc9ac755bafa55ec9b33bc158e454a5c3b91"));
        assert(genesis.hashMerkleRoot == uint256("0e8de3e080db5e1d5111fb6ec889dcf3cb57c1f08402a645d87513709eb233a5"));

        vSeeds.push_back(CDNSSeedData("nuts.seed.simianlabs.net", "nuts.seed.simianlabs.net"));         // Single node address
        vSeeds.push_back(CDNSSeedData("94.46.130.130", "94.46.130.130"));      // Lisbon
        vSeeds.push_back(CDNSSeedData("159.65.34.188", "159.65.34.188"));      // New York
        vSeeds.push_back(CDNSSeedData("104.248.207.221", "104.248.207.221"));  // Amsterdam
        vSeeds.push_back(CDNSSeedData("138.68.252.193", "138.68.252.193"));    // San Francisco
        vSeeds.push_back(CDNSSeedData("167.179.67.201", "167.179.67.201"));    // Tokyo
        vSeeds.push_back(CDNSSeedData("207.148.80.233", "207.148.80.233"));    // Sydney

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 53);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 13);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 179);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x33).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        // 	BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x77).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = false;		// default true
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = true;		// default false
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        //strSporkKey = "0488207ddc1c73a064e636d80ff776f81bdcd6f4a898c9783d128bf487c33db39a6fd2d44b194b141bcc0425d5c3cbd6db561dcf129a8188eefc15d0667317f27d";
        strSporkKey = "04d056a49e870f6678bd610ede4aa2ffa401f59af85ee09e5cfa3eacb349716d94837584e2ac0017290223e6aa7bfb71085e7baf26b1f73f8646862d36b2e85723";
        strObfuscationPoolDummyAddress = "NUAncQ3Z8CEG3FUErSyXdU9vDnwvHigB6b";

        nStartMasternodePayments = 1547418980; 
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

std::string CChainParams::GetDevFeeRewardAddress()
{
	return "Nj82wRhtCkuidJ4YYxZzaWW9rvfba2HA5F";
}

CScript CChainParams::GetScriptForDevFeeDestination() {
    CBitcoinAddress address(GetDevFeeRewardAddress().c_str());
    assert(address.IsValid());

    CScript script = GetScriptForDestination(address.Get());
    return script;
}

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
        pchMessageStart[0] = 0x31;
        pchMessageStart[1] = 0x3d;
        pchMessageStart[2] = 0x4e;
        pchMessageStart[3] = 0x98;
        vAlertPubKey = ParseHex("0b880fb82967fbe513d9199d679f32431f3c629d91f2d868fb08be277024345b63c4b73c149fdf773a2243934aa3d11497483259c347df4996828b020b23c1f38d");
        nDefaultPort = 25136;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // NUTS: 1 day
        nTargetSpacing = 1 * 60;  // NUTS: 1 minute
        nLastPOWBlock = 300;
        nMaturity = 15;
        nMasternodeCountDrift = 4;

        nModifierUpdateBlock = 51197; //approx Mon, 17 Apr 2017 04:00:00 GMT
        nMaxMoneyOut = 10000000 * COIN;

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1547418980;
        genesis.nNonce = 18181;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("000002c9131c15e37b47c77abea2fc9ac755bafa55ec9b33bc158e454a5c3b91"));


        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet NUTS addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet NUTS script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet NUTS BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet NUTS BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet NUTS BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = true;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKey = "04d056a49e870f6678bd610ede4aa2ffa401f59af85ee09e5cfa3eacb349716d94837584e2ac0017290223e6aa7bfb71085e7baf26b1f73f8646862d36b2e85723";
        strObfuscationPoolDummyAddress = "NUAncQ3Z8CEG3FUErSyXdU9vDnwvHigB6b";
        nStartMasternodePayments = 1547418980; //Fri, 09 Jan 2015 21:05:58 GMT
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
        pchMessageStart[0] = 0x2d;
        pchMessageStart[1] = 0x53;
        pchMessageStart[2] = 0x6f;
        pchMessageStart[3] = 0x40;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // NUTS: 1 day
        nTargetSpacing = 1 * 60;        // NUTS: 1 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nBits = 0x1e0ffff0;
        genesis.nTime = 1547418980;
        genesis.nNonce = 18181;

        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 25135;
        assert(hashGenesisBlock == uint256("000002c9131c15e37b47c77abea2fc9ac755bafa55ec9b33bc158e454a5c3b91"));

        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
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
        nDefaultPort = 25134;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval) { nSubsidyHalvingInterval = anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
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
