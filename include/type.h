#include <string>
#include <vector>
#include <list>
#include <memory>
#include <chrono>
#include <iostream>
#include <fstream>
#include "config.h"
#include "single_include/nlohmann/json.hpp"

enum CurrencyUnit {
    USD, EUR, CNY, GBP, JPY, KRW, BTC
};

class StockPrice {
private:
    uint64_t timestamp;
    double open, high, low, close, volume;

    StockPrice() : timestamp(0), open(0), high(0), low(0), close(0), volume(0) {}
    StockPrice(const StockPrice& other) = default;
    StockPrice(StockPrice&& other) noexcept = default;
    ~StockPrice() = default;
};

class StockData {
private:
    uint64_t last_updated_timestamp;
    std::string ticker;
    std::unique_ptr<std::vector<StockPrice>> prices;
    CurrencyUnit currency_unit;

public:
    StockData(nlohmann::json&& stock_json) : ticker(stock_json["Meta Data"]["2. Symbol"]) {
        // initialize last updated timestamp
        // gonna make magic number to constant number(literal)
        std::string last_updated_date = stock_json["Meta Data"]["Last Refreshed"].get<std::string>();
        std::tm timeinfo = {0};
        timeinfo.tm_year = std::stoi(last_updated_date.substr(0,4)) - 1900;
        timeinfo.tm_mon = std::stoi(last_updated_date.substr(5,2));
        timeinfo.tm_mday = std::stoi(last_updated_date.substr(8,2));
        last_updated_timestamp = std::mktime(&timeinfo);

        // initialize currency_unit
        // usd only yet
        currency_unit = USD;

        // initialize prices
        for(auto it = stock_json["Time Series (Daily)"].begin(); it != stock_json["Time Series (Daily)"].end(); it++) {
            std::cout<< *it <<std::endl;
        }
    }
    StockData(const StockData& other)
        : last_updated_timestamp(other.last_updated_timestamp),
          ticker(other.ticker),
          currency_unit(other.currency_unit),
          prices(std::make_unique<std::vector<StockPrice>>(*other.prices)) {}
    StockData(StockData&& other) noexcept
        : last_updated_timestamp(other.last_updated_timestamp),
          ticker(std::move(other.ticker)),
          currency_unit(other.currency_unit),
          prices(std::move(other.prices)) {}
    ~StockData() = default;
};

class StockDataBase {
private:
    std::unique_ptr<std::list<StockData>> stocks;
public:
    StockDataBase() : stocks(std::make_unique<std::list<StockData>>()) {}
    StockDataBase(const StockDataBase& other)
        : stocks(std::make_unique<std::list<StockData>>(*other.stocks)) {}
    StockDataBase(StockDataBase&& other) noexcept
        : stocks(std::move(other.stocks)) {}
    ~StockDataBase() = default;

    void add_stock(std::string ticker, std::string db_path = BASIC_STOCK_DB_PATH) {
        if(db_path.back() != DIR_SEPARATOR) db_path.push_back(DIR_SEPARATOR);

        std::ifstream stock_file(db_path + ticker + ".json");
        // if(!stock_file) // try http-get request from alpha-vantage server
        if(!stock_file) std::cerr << "can not find \"" << ticker << ".json\" in \"" << db_path << "\"."<<std::endl;

        nlohmann::json stock_json; stock_file >> stock_json;
        
        StockData stock_data(std::move(stock_json));

    }
};
