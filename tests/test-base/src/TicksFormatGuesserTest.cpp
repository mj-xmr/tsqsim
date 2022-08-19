#include "pch_test.h"

#include "TicksProviderFactory.h"
#include "TicksFormatGuesser.h"
#include "TicksProviderFake.h"

#include <Util/Str.hpp>
#include <Util/CoutBuf.hpp>
#include <Template/CorradePointer.h>
#include <UnitTest++/UnitTest++.h>

using namespace EnjoLib;

TEST(TicksFormatGuesser_Fake)
{
    const TicksFormatGuesser    guesser;
    const TicksProviderFake     provFake;
    const VecStr & gen = provFake.Generate();

    const TicksFormat expected  = TicksFormat::FMT_FX;
    const TicksFormat guessed   = guesser.Run(gen);
    CHECK_EQUAL(int(expected), int(guessed));
}

TEST(TicksFormatGuesser_FakeXMR)
{
    const TicksFormatGuesser    guesser;
    const TicksProviderXMRFake  provFake;
    const VecStr & gen = provFake.Generate();

    const TicksFormat expected  = TicksFormat::FMT_TIMESTAMP_VALUE;
    const TicksFormat guessed   = guesser.Run(gen);
    CHECK_EQUAL(int(expected), int(guessed));
}

TEST(TicksFormatGuesser_FakeOrderedSeries)
{
    const TicksFormatGuesser    guesser;
    const TicksProviderOrderedSeriesFake  provFake;
    const VecStr & gen = provFake.Generate();

    const TicksFormat expected  = TicksFormat::FMT_ORDERED_SERIES;
    const TicksFormat guessed   = guesser.Run(gen);
    CHECK_EQUAL(int(expected), int(guessed));
}

TEST(TicksFormatGuesser_Uknown)
{
    const TicksFormatGuesser    guesser;
    VecStr gen;
    const Str line = "123,242,452,32";
    gen.push_back(line);
    gen.push_back(line);

    const TicksFormat expected  = TicksFormat::FMT_UNKNOWN;
    const TicksFormat guessed   = guesser.Run(gen);
    CHECK_EQUAL(int(expected), int(guessed));
}

TEST(TicksFormatGuesser_UknownLong)
{
    const TicksFormatGuesser    guesser;
    VecStr gen;
    const Str line = "123,242,452,777,777,777,777,777,777,777,777,777,777,777,777";
    gen.push_back(line);
    gen.push_back(line);

    const TicksFormat expected  = TicksFormat::FMT_UNKNOWN;
    const TicksFormat guessed   = guesser.Run(gen);
    CHECK_EQUAL(int(expected), int(guessed));
}
