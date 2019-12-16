#include <iostream>
#include <libbittrex/client.h> 

class TradePair{

	private:
		std::string name_;
		double volume_;
		double price_;
	public:
  		TradePair(std::string name);
		~TradePair();
		
		std::string getName();
		double fetchVolume();
		double fetchVolumeChange();
		double getVolume();
		void setVolume(double vol);

		double fetchPrice();
		double fetchPriceChange();
		double getPrice();
		void setPrice(double pri);

  		friend std::ostream& operator<<(std::ostream& os, const TradePair& vp);
};
