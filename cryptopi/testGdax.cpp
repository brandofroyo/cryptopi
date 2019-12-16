#include "client_gdax.h"
#include "GdaxTradePair.h"

int main(int argc, const char *argv[])
{	
	std::string key("Insert your key here");
	std::string secret("Insert your secret here");
	std::string pass_phrase("Insert your passphrase here");

	client_gdax client(key,secret,pass_phrase);
	
	/*****************************  this section works with client_gdax.h  *********/
	
	std::string input;
	std::cout << "Enter pair in the format such as LTC-BTC" << std::endl;
	std::cin >> input; 
	std::string x = "ETH-BTC";


	std::cout<<"response from getting the volume data of ETH-BTC (hardcoded)"<<std::endl<<std::endl<<client.get_volume_info(x)<<std::endl<<std::endl;
	
	std::cout<<"response from getting the price data of ETH-BTC (hard coded) "<<std::endl<<std::endl<<client.get_price_info(x)<<std::endl<<std::endl;

	std::cout<<"response from getting the volume data of INPUT "<<std::endl<<std::endl<<client.get_volume_info(input)<<std::endl<<std::endl;
	
	std::cout<<"response from getting the price data of INPUT "<<std::endl<<std::endl<<client.get_price_info(input)<<std::endl<<std::endl;
	
	/*****************************  this section works with GdaxTradePair*********/
	std::string pair = "LTC-BTC";
	GdaxTradePair *gtp = new GdaxTradePair(pair);
	double volume = gtp->fetchVolume();
	double price = gtp->fetchPrice();

	std::cout<<"response GDAX TRADE PAIR VOLUME (LTC-BTC)  "<<std::endl<< volume <<std::endl<<std::endl;
	
	std::cout<<"response GDAX TRADE PAIR price (LTC-BTC)  "<<std::endl<< price <<std::endl<<std::endl;
	
	
	return 0;
}
