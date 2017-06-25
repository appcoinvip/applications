// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "txdb.h"
#include "main.h"
#include "uint256.h"


static const int nCheckpointSpan = 500;

namespace Checkpoints
{

    //
    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    // + Contains no strange transactions
    //
    MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of
            ( 0,  uint256("0x00000d498e37f3531ed93b66128f562dd38faf46974daee738b89eaae384a745") ) // Params().HashGenesisBlock())
            ( 1,  uint256("0x000004b58f31d33ae05e7edcd9c76006dcd34a28274f1fd1e1895dfcd621dc1e") )
            ( 900,  uint256("0x00000d45345bce8ba109966132d020793e7f6dc3dc6c8e5d061e02a32a808a81") )
            ( 5000,  uint256("0x71b6479e55eb8020480544981b346ecaf3569e705485cdc1912643c50cbe6619") )
            ( 10000,  uint256("0x000001c92c3d092482c36272310e9e7eba9e09f0194d293a39be143a30940a9a") )
            ( 20000,  uint256("0x2856d047dc5099bf5dfa354c24987a70b06bcd2bd041d8e97e5a433b40adb42b") )
            ( 30000,  uint256("0xd554a0072d4e2c4b858021dc3a7af07a4ff732bf71532645ce1c0cd30173f016") )
            ( 40000,  uint256("0x5be2bc259a6b20b0cf8c1c34bc03488e7d17b78e1ab8a7ac55357d645b7f7f76") )
            ( 50000,  uint256("0xdbffa23fb885b4040a48761de9fd76490a9924873326743d75ce8f08548fcde5") )
        ( 60000,  uint256("0x69cc04ba341aaeb2ad67af758834975a29f2b434e8ec251a6d030f7573fa9957") )
        ( 70000,  uint256("0xa2e89a41f1f48653fd38ed797f2117dd2519eb1d83ad1d73a84c5feb5bab7ac1") )
        ( 80000,  uint256("0x4ba5f9eb03b15f7663f34a9abfd04a264bc426f265e4ff092d79ee06faeb542f") )
        ( 90000,  uint256("0xca486d214aa3258651a7d5ecf855e2ba03d941853528d4ff99eb56b2fade68f4") )
        ( 100000, uint256("0x88ba4385cb8516ff7e4107e8ef63df39e6ab3fa38e8d2da06b43c934f9da419b") )
        ( 110000, uint256("0x698afe50e7d4ac26444fd84830b60429a2690aa9865131f2251fbbf6cec0b15b") )
        ( 120000, uint256("0x877c5e9945b13400b6a492fc715941f1fa4d50676c3d44e56663f90a3430e9bc") )
        ( 130000, uint256("0xbf50f477695eb192370d5d936acf5465b5b14694687fb2298226b5e5515ddb23") )
        ( 140000, uint256("0x7ddc3baaa60ef8bc9e68c4a078fdf16b466c63b4eb38ae11b344b7ce5e3cda2e") )
        ( 150000, uint256("0x45c75916d849e606594c9ce67036f219d438d0616b233449dc8fd4caa9abf2a8") )
      ( 200000, uint256("0x5c271dc4bf00675e3406db6241dc2aa8a51b654b8f58eaad34b13f2d562df4e5") )
        ( 250000, uint256("0xde784f9866ecd0b0d7d452a3ab3f10ec2c2009d6a5c526093112b60c4841c0d3") )
        ( 300000, uint256("0xa4daa5279d28f904e81a9877df1d4f2467ad5abc4446a187011e4439099ce0e5") )
        ( 350000, uint256("0x332cd8cb3a1f7411f919155181de0e9cc256d440b2a43f8a1b5f8d4e59c0da80") )
        ( 200000, uint256("0xd9af28b1b16e20aff1bdafdbdeaa793af8475681e3c2b5b6ad13d28ae6da6b1e") )
        ( 245000, uint256("0xe075bf70c40a7c18cc7bf305b2922ca690a13473b6edf05b4a452a85539fe50c") )
        ( 250000, uint256("0x19a6a7fe4d2b6db91160a2b0e46bf5045e8b9f3c3e15016c48e77657cadaa5b8") )
        ( 300000, uint256("0xb7f4f3b08a10eb7045cdfc7070856530dfae6fa4630b983b2922be80dfd91f3e") )
        ( 350000, uint256("0x27e5167742fa86a107a7823eac252985199fcf4e0aa8fa438af3d9b0e609824f") )
        ( 400000, uint256("0xc3da3d67f9743aae8344c85e5a6864ab7bcd2a230ec6d9e113814059d7561f6c") )
      /*  ( 500000, uint256("0xa85a7561b73c2549bf909fb3b51b384d915b8f83c321fc4977b201d4be2a8a0b") )
        ( 590000, uint256("0x680d2a36efdf4989c82cf144c36ba7ca398d0ba557f00ae51de07cba649823b4") )
        ( 765000, uint256("0x40fd13a50feaca5a54dd7834b97b2ddce2fee85b42a95ea2079edd3a81f22857") )
   */
         ;

    // TestNet has no checkpoints
    MapCheckpoints mapCheckpointsTestnet;

    bool CheckHardened(int nHeight, const uint256& hash)
    {
        MapCheckpoints& checkpoints = (fTestNet ? mapCheckpointsTestnet : mapCheckpoints);

        MapCheckpoints::const_iterator i = checkpoints.find(nHeight);
        if (i == checkpoints.end())
            return true;
        return hash == i->second;
    }

    int GetTotalBlocksEstimate()
    {
        MapCheckpoints& checkpoints = (fTestNet ? mapCheckpointsTestnet : mapCheckpoints);

        if (checkpoints.empty())
            return 0;
        return checkpoints.rbegin()->first;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        MapCheckpoints& checkpoints = (fTestNet ? mapCheckpointsTestnet : mapCheckpoints);

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, checkpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
        }
        return NULL;
    }

    CBlockThinIndex* GetLastCheckpoint(const std::map<uint256, CBlockThinIndex*>& mapBlockThinIndex)
    {
        MapCheckpoints& checkpoints = (fTestNet ? mapCheckpointsTestnet : mapCheckpoints);

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, checkpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockThinIndex*>::const_iterator t = mapBlockThinIndex.find(hash);
            if (t != mapBlockThinIndex.end())
                return t->second;
        }
        return NULL;
    }


    // Automatically select a suitable sync-checkpoint 
    const CBlockIndex* AutoSelectSyncCheckpoint()
    {
        const CBlockIndex *pindex = pindexBest;
        // Search backward for a block within max span and maturity window
        while (pindex->pprev && pindex->nHeight + nCheckpointSpan > pindexBest->nHeight)
            pindex = pindex->pprev;
        return pindex;
    }

    // Automatically select a suitable sync-checkpoint - Thin mode
    const CBlockThinIndex* AutoSelectSyncThinCheckpoint()
    {
        const CBlockThinIndex *pindex = pindexBestHeader;
        // Search backward for a block within max span and maturity window
        while (pindex->pprev && pindex->nHeight + nCheckpointSpan > pindexBest->nHeight)
            pindex = pindex->pprev;
        return pindex;
    }

    // Check against synchronized checkpoint
    bool CheckSync(int nHeight)
    {
        if(nNodeMode == NT_FULL)
        {
            const CBlockIndex* pindexSync = AutoSelectSyncCheckpoint();

            if (nHeight <= pindexSync->nHeight)
                return false;
        }
        else {
            const CBlockThinIndex *pindexSync = AutoSelectSyncThinCheckpoint();

            if (nHeight <= pindexSync->nHeight)
                return false;
        }
        return true;
    }
}
