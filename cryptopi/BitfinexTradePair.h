#pragma once
#include <iostream>
#include "bfx-api-cpp/BitfinexAPI.hpp"
#include <boost/variant.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include <boost/algorithm/string.hpp>


class BitfinexTradePair {

private:
	std::string name_;
	double volume_;
	double price_;
public:
	BitfinexTradePair(std::string name);
	~BitfinexTradePair();
	/** this function will change the input into an acceptable input for bitfinex
	* since bitfinux only accepts input as "btcusd" type and we only use "BTC-USD"
	* we need to change the input for bitfiniex to retrieve the information*/
	std::string pairConvert(std::string str);
	///returns the name
	std::string getName();
	/** this function will get us the volume from the bitfinex library
	* this library however return the information as a string
	* which means that we have to use boost and get whatever we went out of that
	* string */
	double fetchVolume();
	///returns the volume change by creating a new volume first
	double fetchVolumeChange();
	///returns the volume
	double getVolume();
	/// sets the volume
	void setVolume(double vol);
	/** this function will get us the price from the bitfinex library
	* this library however return the information as a string
	* which means that we have to use boost and get whatever we went out of that
	* string */
	double fetchPrice();
	///returns the price change by creating a new price first
	double fetchPriceChange();
	///returns the price
	double getPrice();
	///sets the price
	void setPrice(double pri);
	///simple method to return output as ostream
	friend std::ostream& operator<<(std::ostream& os, const BitfinexTradePair& vp);  // might need to adjust this

};
