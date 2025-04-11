#include <fstream>
#include <iostream>

#include "config.h"
#include "single_include/nlohmann/json.hpp"
#include "stock_data.h"

int main() {

    std::ifstream file("data/stock/AAPL.json");
    if (!file) std::cerr << "파일을 열 수 없습니다!" << std::endl;

    nlohmann::json aapl_json;
    file >> aapl_json;

    std::cout << aapl_json["Meta Data"]["3. Last Refreshed"] << std::endl;
    std::cout << aapl_json["Time Series (Daily)"]["2025-03-13"]["1. open"]
              << std::endl;
    std::string test(
        aapl_json["Meta Data"]["3. Last Refreshed"].get<std::string>());

    std::cout << test[0];

    for (auto it = aapl_json["Time Series (Daily)"].begin();
         it != aapl_json["Time Series (Daily)"].end(); it++) {
        std::cout << it.key() << std::endl;
    }

    StockDataBase mybase;
    mybase.add_stock("AAPL");
	for(auto it = mybase.stocks.front().prices.begin(); it != mybase.stocks.front().prices.end(); it++) {
		std::cout<<it->volume<<std::endl;
	}
    return 0;
}