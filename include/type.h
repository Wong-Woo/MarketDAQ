#include <string>
#include <vector>
#include <list>
#include <memory>
#include <chrono>
#include <iostream>
#include <fstream>
#include <regex>
#include "config.h"
#include "single_include/nlohmann/json.hpp"

enum CurrencyUnit {
    USD, EUR, CNY, GBP, JPY, KRW, BTC
};

uint64_t date2timestamp(std::string date) {
    std::regex date_regex(R"(\d\d\d\d)-(\d\d)-(\d\d)");
    std::smatch captured;
    if(std::regex_match(date, captured, date_regex)) {
        u_int32_t year = std::stoi(captured[1].str());
        u_int32_t month = std::stoi(captured[2].str());
        u_int32_t day = std::stoi(captured[3].str());

        std::tm timeinfo = {0};
        timeinfo.tm_year = year - 1900;
        timeinfo.tm_mon = month - 1;
        timeinfo.tm_mday = day;
        return std::mktime(&timeinfo);
    } else {
        std::cerr << "Can't match the date form" << std::endl;
        return 0;
    }
}

class StockPrice {
    public:
    uint64_t timestamp;
    double open, high, low, close, volume;

    StockPrice(uint64_t timestamp, double open, double high, double low, double close, double volume) 
        : timestamp(timestamp), open(open), high(high), low(low), close(close), volume(volume) {}
    StockPrice(const StockPrice& other) = default;
    StockPrice(StockPrice&& other) noexcept = default;
    ~StockPrice() = default;
};

class StockData {
public:
    uint64_t last_updated_timestamp;
    std::string ticker;
    std::unique_ptr<std::vector<StockPrice>> prices;
    CurrencyUnit currency_unit;
    StockData(nlohmann::json&& stock_json) 
        : ticker(stock_json["Meta Data"]["2. Symbol"]), prices(std::make_unique<std::vector<StockPrice>>()) {
        // initialize last updated timestamp
        std::string last_updated_date = stock_json["Meta Data"]["Last Refreshed"].get<std::string>();
        last_updated_timestamp = date2timestamp(last_updated_date);

        // initialize currency_unit
        // usd only yet
        currency_unit = USD;

        // initialize prices
        auto stock_data_series = stock_json["Time Series (Daily)"];
        for(auto it = stock_data_series.begin(); it != stock_data_series.end(); it++) {
            StockPrice price(date2timestamp(it.key()),(*it)["1. open"].get<double>(),(*it)["2. high"].get<double>(),(*it)["3. low"].get<double>(), (*it)["4. close"].get<double>(),(*it)["5. volume"].get<double>());
            (*prices).push_back(price);
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
public:
    std::unique_ptr<std::list<StockData>> stocks;
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
        (*stocks).push_back(stock_data);
    }
};
