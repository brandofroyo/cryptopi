#include "BitfinexTradePair.h"
#include <iostream>       // std::cout
#include <string>         // std::string
#include <locale>         // std::locale, std::tolower
#include <unistd.h>


// TODO MIGHT NEED THE INCLUDES FOR BOOST IN HERE, OR KEEP THEM IN MAIN LIKE example.cpp


///constructor
BitfinexTradePair::BitfinexTradePair(std::string name){
  //TODO CREATE FUNCTION TO CONVERT FORMAT THAT IS ACCEPTABLE EX: btcusd
	name_ = pairConvert(name);
	volume_ = BitfinexTradePair::fetchVolume();
	price_ = BitfinexTradePair::fetchPrice();
}

///destructor
BitfinexTradePair::~BitfinexTradePair(){
}

/** this function will change the input into an acceptable input for bitfinex
* since bitfinux only accepts input as "btcusd" type and we only use "BTC-USD"
* we need to change the input for bitfiniex to retrieve the information*/

std::string BitfinexTradePair::pairConvert(std::string str){
 std::locale loc;
 std::string newstr="xxxxxxx";
 for (std::string::size_type i=3; i<str.length(); i++){
   str[i]=str[i+1];
 }
 for (std::string::size_type i=0; i<str.length(); ++i){
   newstr[i] = std::tolower(str[i],loc);
 }
 return newstr;
}
/// this function returns the name of the trade pair
std::string BitfinexTradePair::getName(){
    return name_;
}
/// this function returns the volume of the trade pair
double BitfinexTradePair::getVolume(){
    return volume_;
}
/// this function sets the volume of the trade pair
void BitfinexTradePair::setVolume(double vol){
    volume_ = vol;
}

/** this function will get us the volume from the bitfinex library
* this library however return the information as a string
* which means that we have to use boost and get whatever we went out of that
* string */
double BitfinexTradePair::fetchVolume(){
    BfxAPI::BitfinexAPI bfxAPI;
    double volume =  0;
    bfxAPI.getTicker(name_);
    string x = bfxAPI.strResponse();
    std::stringstream ss;
    ss << x;
    boost::property_tree::ptree info;
    boost::property_tree::read_json(ss,info);
    volume_ = info.get<double>("volume");
    return volume;
}
/// this function will return the volume change by geting a new volume and dividing it by old volume
double BitfinexTradePair::fetchVolumeChange(){
    double newVol = BitfinexTradePair::getVolume();
    return newVol / volume_;
}
/// returns price
double BitfinexTradePair::getPrice(){
    return price_;
}
///sets price
void BitfinexTradePair::setPrice(double pri){
    price_ = pri;
}

/** this function will get us the price from the bitfinex library
* this library however return the information as a string
* which means that we have to use boost and get whatever we went out of that
* string */
double BitfinexTradePair::fetchPrice(){
  BfxAPI::BitfinexAPI bfxAPI;
  bfxAPI.getTicker(name_);
  string x = bfxAPI.strResponse();
  double price =  0;
  std::stringstream ss;
  ss << x;
  boost::property_tree::ptree info;
  boost::property_tree::read_json(ss,info);
  price_ = info.get<double>("last_price");
  return price;
}
/// this function will get a new price and then divide our old price by the new price to get price change
double BitfinexTradePair::fetchPriceChange(){
    double newpri = BitfinexTradePair::getPrice();
    return newpri / price_;
}
///simple function to output our results as an ostream
std::ostream& operator<<(std::ostream& os, const BitfinexTradePair& tp)  {
    os << "Volume \"" << tp.name_ << "\": " << tp.volume_ << std::endl;
    os << "Price \"" << tp.name_ << "\": " << tp.price_;
    return os;
}
