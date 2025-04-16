#include "timeconv.h"
#include <chrono>
#include <iostream>
#include <regex>
#include <string>
#include <iomanip>

uint64_t date2timestamp(std::string date)
{
    std::regex date_regex(R"((\d\d\d\d)-(\d\d)-(\d\d))");
    std::smatch captured;
    if (std::regex_match(date, captured, date_regex))
    {
        uint32_t year = std::stoi(captured[1].str());
        uint32_t month = std::stoi(captured[2].str());
        uint32_t day = std::stoi(captured[3].str());

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

std::unique_ptr<std::string> timestamp_to_date(uint64_t timestamp) {
    // Unix 타임스탬프를 std::chrono::seconds로 변환
    std::chrono::seconds sec(timestamp);
    std::chrono::system_clock::time_point tp(sec);

    // 시스템 시간으로 변환
    std::time_t time = std::chrono::system_clock::to_time_t(tp);
    
    // std::tm 구조체로 변환
    std::tm* tm_info = std::localtime(&time);
    
    // YYYY-MM-DD 형식으로 출력
    std::stringstream ss;
    ss << std::put_time(tm_info, "%Y-%m-%d");
    
    return std::make_unique<std::string>(ss.str());
}