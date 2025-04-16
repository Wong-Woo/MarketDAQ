#ifndef TIMECONV_H
#define TIMECONV_H_H

#include <string>
#include <memory>

uint64_t date2timestamp(std::string date);
std::unique_ptr<std::string> timestamp_to_date(uint64_t timestamp);

#endif // TIMECONV_H_H