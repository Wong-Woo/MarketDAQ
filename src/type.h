#include <chrono>
#include <fstream>
#include <iostream>
#include <list>
#include <memory>
#include <regex>
#include <string>
#include <vector>

#include "config.h"
#include "single_include/nlohmann/json.hpp"

enum CurrencyUnit { USD, EUR, CNY, GBP, JPY, KRW, BTC };

uint64_t date2timestamp(std::string date);

class StockPrice {
   public:
    uint64_t timestamp;
    double open, high, low, close, volume;

    StockPrice(uint64_t timestamp, double open, double high, double low, double close, double volume)
        : timestamp(timestamp),
          open(open),
          high(high),
          low(low),
          close(close),
          volume(volume) {}
    StockPrice(const StockPrice &other) = default;
    ~StockPrice() = default;
};

class StockData {
   public:
    uint64_t last_updated_timestamp;
    std::string ticker;
    std::vector<StockPrice> prices;
    CurrencyUnit currency_unit;
    StockData(nlohmann::json &&stock_json)
        : ticker(stock_json["Meta Data"]["2. Symbol"]),
          prices(std::vector<StockPrice>()) {
        // initialize last updated timestamp
        std::string last_updated_date =
            stock_json["Meta Data"]["3. Last Refreshed"].get<std::string>();
        last_updated_timestamp = date2timestamp(last_updated_date);
        // initialize currency_unit
        // usd only yet
        currency_unit = USD;

        // initialize prices
        auto stock_data_series = stock_json["Time Series (Daily)"];
        for (auto it = stock_data_series.begin(); it != stock_data_series.end();
             it++) {
            StockPrice price(date2timestamp(it.key()),
                             std::stod((*it)["1. open"].get<std::string>()),
                             std::stod((*it)["2. high"].get<std::string>()),
                             std::stod((*it)["3. low"].get<std::string>()),
                             std::stod((*it)["4. close"].get<std::string>()),
                             std::stod((*it)["5. volume"].get<std::string>()));
            prices.push_back(price);
        }
    }
    StockData(const StockData &other)
        : last_updated_timestamp(other.last_updated_timestamp),
          ticker(other.ticker),
          currency_unit(other.currency_unit),
          prices(std::vector<StockPrice>(other.prices)) {}
    StockData(StockData &&other) noexcept
        : last_updated_timestamp(other.last_updated_timestamp),
          ticker(std::move(other.ticker)),
          currency_unit(other.currency_unit),
          prices(std::move(other.prices)) {}
    ~StockData() = default;
};

class StockDataBase {
   public:
    std::list<StockData> stocks;
    StockDataBase() : stocks(std::list<StockData>()) {}
    StockDataBase(const StockDataBase &other)
        : stocks(std::list<StockData>(other.stocks)) {}
    StockDataBase(StockDataBase &&other) noexcept
        : stocks(std::move(other.stocks)) {}
    ~StockDataBase() = default;

    void add_stock(std::string ticker,
                   std::string db_path = BASIC_STOCK_DB_PATH) {
        if (db_path.back() != DIR_SEPARATOR) db_path.push_back(DIR_SEPARATOR);

        std::ifstream stock_file(db_path + ticker + ".json");
        // if(!stock_file) // try http-get request from alpha-vantage server
        if (!stock_file)
            std::cerr << "can not find \"" << ticker << ".json\" in \""
                      << db_path << "\"." << std::endl;

        nlohmann::json stock_json;
        stock_file >> stock_json;

        StockData stock_data(std::move(stock_json));
        stocks.push_back(stock_data);
    }
};
