#define BOOST_TEST_MODULE BittrexApiTest
#include <iostream>
#include <vector>
#include <libbittrex/client.h>
#include <boost/test/included/unit_test.hpp>
#include "TradePair.cpp"


namespace bittrex {
namespace test {

std::string key = "";
std::string secret = "";
const std::string &MARKET = "BTC-LTC";
bittrex::Client btxcli(key, secret);
TradePair* p = new TradePair(MARKET);
//auto p = TradePair.TradePair("BTC-LTC");



BOOST_AUTO_TEST_SUITE(TestLTC)

BOOST_AUTO_TEST_CASE(TestingfetchVolume) {
    BOOST_REQUIRE_NO_THROW(p->fetchVolume());
    auto volume = p->fetchVolume();
    BOOST_CHECK(volume!=0);

}

BOOST_AUTO_TEST_CASE(TestingfetchVolumeChange) {
    BOOST_CHECK_NO_THROW(p->fetchVolumeChange());
}

BOOST_AUTO_TEST_CASE(TestingfetchPrice) {
    BOOST_REQUIRE_NO_THROW(p->fetchPrice());
    auto price = p->fetchPrice();
    BOOST_CHECK(price!=0);
}

BOOST_AUTO_TEST_CASE(TestingfetchPriceChange) {
    BOOST_CHECK_NO_THROW(p->fetchPriceChange());
}



BOOST_AUTO_TEST_SUITE_END()
}
}