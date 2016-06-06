all: findLCS

findLCS: main.cpp
	g++ -std=c++11 main.cpp -o findLCS
