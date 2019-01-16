#pragma once
#include <iostream>
#include "client_gdax.h"




class GdaxTradePair {

private:
	std::string name_;
	double volume_;
	double price_;
public:
	GdaxTradePair(std::string name);
	~GdaxTradePair();
	///returns the price pair name
	std::string getName();
	/** this function creats a fdax object then uses that object to fetch the volume
	* after that is done the volume is returned. key secret and pass phrase
	* are not used by us since we arnt trying to have people trade, however we still need
	* them to create a class object */
	double fetchVolume();
	///returns the volume change
	double fetchVolumeChange();
	///returns the volume
	double getVolume();
	///sets the volume
	void setVolume(double vol);
	/** this function creats a fdax object then uses that object to fetch the price
	* after that is done the volume is returned. key secret and pass phrase
	* are not used by us since we arnt trying to have people trade, however we still need
	* them to create a class object */
	double fetchPrice();
	///returns the price change
	double fetchPriceChange();
	///returns price
	double getPrice();
	///sets price
	void setPrice(double pri);
	///simple function to return output as an ostream
	friend std::ostream& operator<<(std::ostream& os, const GdaxTradePair& vp);  // might need to adjust this

};
