#!/bin/bash

.PHONY: build

CPP_FILES = main.cpp TradePair.cpp BittrexTradePair.cpp BitfinexTradePair.cpp GdaxTradePair.cpp client_gdax.cpp
OBJECTS = main.o TradePair.o BittrexTradePair.o BitfinexTradePair.o GdaxTradePair.o client_gdax.o
INCLUDES = -Ibfx-cpp-api/app/include/
LINKS = -lwthttp -lwt -lbittrex -lcurl -lcrypto -lpthread -lboost_system -lboost_filesystem -lboost_date_time -lcryptopp
GXX = g++ -Wall -std=c++14

build: $(CPP_FILES)
	$(GXX) -c $(CPP_FILES) $(INCLUDES)
	$(GXX) $(OBJECTS) -o main $(LINKS)

run:
	./main --docroot . --http-address 0.0.0.0 --http-port 9090
