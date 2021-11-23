#include "pch_test.h"
#include <UnitTest++/UnitTest++.h>

#include <Statistical/KMeans1d.hpp>
#include <Statistical/KMeans1dCluster.hpp>

#include <Template/Array.hpp>
#include <STD/VectorCpp.hpp>

using namespace std;
using namespace EnjoLib;

TEST(KMeans1d_1000_members)
{
    KMeans1d kms;
    kms.AddObservation(1.1129);
    kms.AddObservation(1.1132);
    kms.AddObservation(1.1201);
    kms.AddObservation(1.1204);
    kms.AddObservation(1.1464);

    const EnjoLib::Array<KMeans1dCluster> & clust = kms.ReduceGetClusters(4);
    {
        int result = clust.at(0).GetMembersLevels().size();
        int expected = 5;
        CHECK_EQUAL(expected, result);
    }
}
