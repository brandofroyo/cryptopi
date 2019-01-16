#pragma once

#include <iostream>
#include <libbittrex/client.h> 

class BittrexTradePair{

	private:
		std::string name_;
		double volume_;
		double price_;
	public:
  		BittrexTradePair(std::string name);
		~BittrexTradePair();
		///getters and setters
		std::string getName();
		/**this function gets the volume from the public library the key and 
		*secret are not used but needed to compile the code we dont use them because
		* we dont need identification since we are not trading
		*summary creates the object of type summary and then vol gets exactly
		*what we want from that summary then returns it*/
		double fetchVolume();
		///creates new volume then compares to old volume to get volume change
		double fetchVolumeChange();
		double getVolume();
		void setVolume(double vol);
		/**this function gets the price from the public library the key and 
		*secret are not used but needed to compile the code we dont use them because
		* we dont need identification since we are not trading
		*summary creates the object of type summary and then vol gets exactly
		*what we want from that summary then returns it*/
		double fetchPrice();
		///creates a new price then compares to old price to get price change
		double fetchPriceChange();
		double getPrice();
		void setPrice(double pri);
		///returns our price and volume as an ostream
  		friend std::ostream& operator<<(std::ostream& os, const BittrexTradePair& vp);
};

