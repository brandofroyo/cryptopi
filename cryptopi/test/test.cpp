#define BOOST_TEST_MODULE BittrexApiTest
#include <boost/test/included/unit_test.hpp>
#include "TradePair.h"


namespace bittrex {
namespace test {

///testing LTC stats...
BOOST_AUTO_TEST_SUITE(TestLTC)

///test case for the fetchVolume function...
BOOST_AUTO_TEST_CASE(TestingfetchVolume) {
    auto p = TradePair("BTC-LTC");
    BOOST_REQUIRE_NO_THROW(p.fetchVolume());
    auto volume = p.fetchVolume();
    ///make sure volume isn't 0 (null)
    BOOST_CHECK(volume!=0);

}

///test case for the fetchVolumeChange function...
BOOST_AUTO_TEST_CASE(TestingfetchVolumeChange) {
    auto p = TradePair("BTC-LTC");
    ///handle exception if volume change is null
    BOOST_CHECK_NO_THROW(p.fetchVolumeChange());
}

///test case for the fetchPrice function...
BOOST_AUTO_TEST_CASE(TestingfetchPrice) {
    auto p = TradePair("BTC-LTC");
    BOOST_REQUIRE_NO_THROW(p.fetchPrice());
    auto price = p.fetchPrice();
    ///make sure price isn't 0 (null)
    BOOST_CHECK(price!=0);
}

///test case for the fetchPriceChange function...
BOOST_AUTO_TEST_CASE(TestingfetchPriceChange) {
    auto p = TradePair("BTC-LTC");
    ///handle exception if volume change is null
    BOOST_CHECK_NO_THROW(p.fetchPriceChange());
}


///end of the testing...
BOOST_AUTO_TEST_SUITE_END()
}
}
