#include "GdaxTradePair.h"


///constructor
GdaxTradePair::GdaxTradePair(std::string name){
	name_ = name;
	volume_ = GdaxTradePair::fetchVolume();
	price_ = GdaxTradePair::fetchPrice();
}

///destructor
GdaxTradePair::~GdaxTradePair(){
}
/// this function will return the name
std::string GdaxTradePair::getName(){
    return name_;
}
/// this function will return volume
double GdaxTradePair::getVolume(){
    return volume_;
}
/// this function will set the volume
void GdaxTradePair::setVolume(double vol){
    volume_ = vol;
}

/** this function creats a fdax object then uses that object to fetch the volume
* after that is done the volume is returned. key secret and pass phrase
* are not used by us since we arnt trying to have people trade, however we still need 
* them to create a class object */
double GdaxTradePair::fetchVolume(){
    std::string key=("");
    std::string secret=("");
    std::string pass_phrase=("");
    
    client_gdax client(key,secret,pass_phrase);
    double volume =  0;
    volume = client.get_volume_info(name_);
    return volume;
}
///gets a new volume then divides by old volume to get price change
double GdaxTradePair::fetchVolumeChange(){
    double newVol = GdaxTradePair::getVolume();
    return newVol / volume_;
}
///returns the price
double GdaxTradePair::getPrice(){
    return price_;
}
///sets the price
void GdaxTradePair::setPrice(double pri){
    price_ = pri;
}

/// very similar to the fetch volume except it gets the price
double GdaxTradePair::fetchPrice(){
  std::string key=("");
  std::string secret=("");
  std::string pass_phrase("");
  client_gdax client(key,secret,pass_phrase);
  double price =  0;
  price = client.get_price_info(name_);
  return price;  
}
/// does the same as fetch volume change except for price
double GdaxTradePair::fetchPriceChange(){
    double newpri = GdaxTradePair::getPrice();
    return newpri / price_;
}
///simple function to output our results as an ostream
std::ostream& operator<<(std::ostream& os, const GdaxTradePair& tp)  {
    os << "Volume \"" << tp.name_ << "\": " << tp.volume_ << std::endl;
    os << "Price \"" << tp.name_ << "\": " << tp.price_;
    return os;
}
