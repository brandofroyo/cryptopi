#pragma once

#include <iostream>
#include <libbittrex/client.h> 
#include <sstream>
#include "BittrexTradePair.h"
#include "BitfinexTradePair.h"
#include "GdaxTradePair.h"

class TradePair{

	private:
		std::string name_;
		BittrexTradePair* bitrexPair_;
		BitfinexTradePair* bitfinexPair_;
		GdaxTradePair* gdaxPair_;
		bool checkBitrex_, checkBitfinex_, checkGdax_;
	public:
		TradePair(std::string name, bool bitrex, bool bitfinex, bool gdax);
		~TradePair();
		
		std::string getName();
		
		void updateVolumes();
		std::string getVolumeChanges();
		std::string getVolumes();

		void updatePrices();
		std::string getPriceChanges();
		std::string getPrices();
};
