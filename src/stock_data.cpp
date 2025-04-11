#include "stock_data.h"

uint64_t date2timestamp(std::string date)
{
    std::regex date_regex(R"((\d\d\d\d)-(\d\d)-(\d\d))");
    std::smatch captured;
    if (std::regex_match(date, captured, date_regex))
    {
        u_int32_t year = std::stoi(captured[1].str());
        u_int32_t month = std::stoi(captured[2].str());
        u_int32_t day = std::stoi(captured[3].str());

        std::tm timeinfo = {0};
        timeinfo.tm_year = year - 1900;
        timeinfo.tm_mon = month - 1;
        timeinfo.tm_mday = day;
        return std::mktime(&timeinfo);
    }
    else
    {
        std::cerr << "Can't match the date form" << std::endl;
        return 0;
    }
}