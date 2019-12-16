#include "BittrexTradePair.h"

//constructor
BittrexTradePair::BittrexTradePair(std::string name){ 
	name_ = name;
	volume_ = BittrexTradePair::fetchVolume();
	price_ = BittrexTradePair::fetchPrice();
}

//destructor
BittrexTradePair::~BittrexTradePair(){
}

std::string BittrexTradePair::getName(){
    return name_;
}

double BittrexTradePair::getVolume(){
    return volume_;
}

void BittrexTradePair::setVolume(double vol){
    volume_ = vol;
}

// to grab the volume for a specific pair passed in by the front end
double BittrexTradePair::fetchVolume(){
    std::string key="";
    std::string secret="";
    bittrex::Client btxcli(key,secret);

    auto summary =  btxcli.public_api().get_market_summary(name_);
	Double vol = summary.base_volume;
	return (double)vol;  //convert to double and return
}

double BittrexTradePair::fetchVolumeChange(){
    double newVol = BittrexTradePair::getVolume();
    return newVol / volume_;
}

double BittrexTradePair::getPrice(){
    return price_;
}

void BittrexTradePair::setPrice(double pri){
    price_ = pri;
}

// to grab the volume for a specific pair passed in by the front end
double BittrexTradePair::fetchPrice(){
    std::string key="";
    std::string secret="";
    bittrex::Client btxcli(key,secret);

    auto summary =  btxcli.public_api().get_market_summary(name_);
	Double pri = summary.last;
	return (double)pri;  //convert to double and return
}

double BittrexTradePair::fetchPriceChange(){
    double newpri = BittrexTradePair::getPrice();
    return newpri / price_;
}

std::ostream& operator<<(std::ostream& os, const BittrexTradePair& tp)  {
    os << "Volume \"" << tp.name_ << "\": " << tp.volume_ << std::endl;
    os << "Price \"" << tp.name_ << "\": " << tp.price_;
    return os;
} 
