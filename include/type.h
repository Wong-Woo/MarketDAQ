#include <string>
#include <vector>
#include <list>
#include <memory>
#include <chrono>

/*
STOCK DATA TYPE DESIGN
- design stock data sereialized for performance.
- design stock data base as double linked list for ram efficiency.
    - not used stock data will be deleted from memory.
*/

enum CurrencyUnit {
    USD,
    EUR,
    CNY,
    GBP,
    JPY,
    KRW,
    BTC,
};

class StockPrice {
    uint64_t timestamp;
    double open;
    double high;
    double low;
    double close;
    double volume;
};

class StockData {
    std::string ticker;
    uint64_t last_updated_timestamp;
    CurrencyUnit currency_unit;
    std::unique_ptr<std::vector<StockPrice>> prices;
};

class StockDataBase {
    std::unique_ptr<std::list<StockData>> stocks;
};