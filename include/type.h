#include <string>
#include <vector>
#include <list>
#include <memory>
#include <chrono>
#include <fstream>
#include "config.h"

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

    StockData() : last_updated_timestamp(0), currency_unit(USD), prices(std::make_unique<std::vector<StockPrice>>()) {}
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

    StockDataBase() : stocks(std::make_unique<std::list<StockData>>()) {}
    StockDataBase(const StockDataBase& other)
        : stocks(std::make_unique<std::list<StockData>>(*other.stocks)) {}
    StockDataBase(StockDataBase&& other) noexcept
        : stocks(std::move(other.stocks)) {}
    ~StockDataBase() = default;

    void add_stock(std::string ticker, std::string db_path = BASIC_STOCK_DB_PATH) {
        if(db_path.back() != DIR_SEPARATOR) db_path.push_back(DIR_SEPARATOR);

        std::ifstream stock_file(db_path+ticker+".json");
        //working
    }
};
