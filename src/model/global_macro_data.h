#include <string>
#include <list>

enum Category {
    Consumption,
    Employment,
    Production,
    Housing,
    Price,
    Investment,
    Monetary,
    Trade,
    Government,
    Other
};

class MacroValue {
    public:
    double value;
    std::string unit;
    uint64_t timestamp;
};

class MacroData {
    public:
    Category category;
    std::string name;
    MacroValue value;
};

class MacroDataBase {
    public:
    std::list<MacroData> macro_data;
};