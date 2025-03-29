#include <string>
#include <vector>
#include <memory>
#include <chrono>

class StockPrice {
    std::time_t timestamp;
    double open;
    double high;
    double low;
    double close;
    double volume;
};

class StockData {
    std::string symbol;
    std::string last_updated;
    std::string time_zone;
    std::string time_unit;
    std::string price_unit;

    std::vector<std::unique_ptr<StockPrice>> prices;
};