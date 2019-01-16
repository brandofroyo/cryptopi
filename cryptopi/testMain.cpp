#include "TradePair.h"

int main(){

	TradePair* t = new TradePair("BTC-LTC", true, true, true);

	std::cout << t -> getVolumes() << std::endl;
	std::cout << t -> getPrices() << std::endl;

return 0;


}
