#include "TradePair.h"

//constructor
TradePair::TradePair(std::string name, bool bitrex, bool bitfinex, bool gdax){ 
	name_ = name;
    checkBitrex_ = bitrex;
    checkBitfinex_ = bitfinex;
    checkGdax_ = gdax;

    if (bitrex)
	   bitrexPair_ = new BittrexTradePair(name);
    if (bitfinex)
       bitfinexPair_ = new BitfinexTradePair(name);
    if (gdax)
       gdaxPair_ = new GdaxTradePair(name);

    TradePair::updateVolumes();
    TradePair::updatePrices();
}

//destructor
TradePair::~TradePair(){
}

std::string TradePair::getName(){
    return name_;
}

void TradePair::updateVolumes(){
    if (checkBitrex_)
        bitrexPair_->setVolume(bitrexPair_->fetchVolume());
    if (checkBitfinex_)
        bitfinexPair_->setVolume(bitfinexPair_->fetchVolume());
    if (checkGdax_)
        gdaxPair_->setVolume(gdaxPair_->fetchVolume());
}

void TradePair::updatePrices(){
    if (checkBitrex_)
        bitrexPair_->setPrice(bitrexPair_->fetchPrice());
    if (checkBitfinex_)
        bitfinexPair_->setPrice(bitfinexPair_->fetchPrice());
    if (checkGdax_)
        gdaxPair_->setPrice(gdaxPair_->fetchPrice());
}

std::string TradePair::getVolumeChanges(){
    std::stringstream ss;

    if (checkBitrex_)
        ss << bitrexPair_->fetchVolumeChange() << " (Bittrex)" << std::endl;

    if (checkBitfinex_)
        ss << bitfinexPair_->fetchVolumeChange() << " (Bitfinex)" << std::endl;

    if (checkGdax_)
        ss << gdaxPair_->fetchVolumeChange() << " (GDax)" << std::endl;

    return ss.str();
}

std::string TradePair::getPriceChanges(){
    std::stringstream ss;

    if (checkBitrex_)
        ss << bitrexPair_->fetchPriceChange() << " (Bittrex)" << std::endl;

    if (checkBitfinex_)
        ss << bitfinexPair_->fetchPriceChange() << " (Bitfinex)" << std::endl;

    if (checkGdax_)
        ss << gdaxPair_->fetchPriceChange() << " (GDax)" << std::endl;

    return ss.str();
}

std::string TradePair::getVolumes(){
    std::stringstream ss;

    if (checkBitrex_)
        ss << bitrexPair_->getVolume() << " (Bittrex)" << std::endl;

    if (checkBitfinex_)
        ss << bitfinexPair_->getVolume() << " (Bitfinex)" << std::endl;

    if (checkGdax_)
        ss << gdaxPair_->getVolume() << " (GDax)" << std::endl;

    return ss.str();
}

std::string TradePair::getPrices(){
    std::stringstream ss;

    ss << bitrexPair_->getPrice() << " (Bittrex)" << std::endl;
    ss << bitfinexPair_->getPrice() << " (Bitfinex)" << std::endl;
    ss << gdaxPair_->getPrice() << " (GDax)" << std::endl;

    return ss.str();
}
