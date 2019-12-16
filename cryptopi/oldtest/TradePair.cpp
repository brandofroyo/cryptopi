#include "TradePair.h"

//constructor
TradePair::TradePair(std::string name){ 
	name_ = name;
	volume_ = TradePair::fetchVolume();
	price_ = TradePair::fetchPrice();
}

//destructor
TradePair::~TradePair(){
}

std::string TradePair::getName(){
    return name_;
}

double TradePair::getVolume(){
    return volume_;
}

void TradePair::setVolume(double vol){
    volume_ = vol;
}

// to grab the volume for a specific pair passed in by the front end
double TradePair::fetchVolume(){
    std::string key="";
    std::string secret="";
    bittrex::Client btxcli(key,secret);

    auto summary =  btxcli.public_api().get_market_summary(name_);
	Double vol = summary.base_volume;
	return (double)vol;  //convert to double and return
}

double TradePair::fetchVolumeChange(){
    double newVol = TradePair::getVolume();
    return newVol / volume_;
}

double TradePair::getPrice(){
    return price_;
}

void TradePair::setPrice(double pri){
    price_ = pri;
}

// to grab the volume for a specific pair passed in by the front end
double TradePair::fetchPrice(){
    std::string key="";
    std::string secret="";
    bittrex::Client btxcli(key,secret);

    auto summary =  btxcli.public_api().get_market_summary(name_);
	Double pri = summary.last;
	return (double)pri;  //convert to double and return
}

double TradePair::fetchPriceChange(){
    double newpri = TradePair::getPrice();
    return newpri / price_;
}

std::ostream& operator<<(std::ostream& os, const TradePair& tp)  {
    os << "Volume \"" << tp.name_ << "\": " << tp.volume_ << std::endl;
    os << "Price \"" << tp.name_ << "\": " << tp.price_;
    return os;
} 
