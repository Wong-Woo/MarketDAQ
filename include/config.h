#ifndef MARKETDAQ_CONFIG_H
#define MARKETDAQ_CONFIG_H
#include <filesystem>

constexpr char DIR_SEPARATOR = std::filesystem::path::preferred_separator;
constexpr char BASIC_STOCK_DB_PATH[] = {'d','a','t','a',DIR_SEPARATOR,'s','t','o','c','k',DIR_SEPARATOR,'\0'};

#endif