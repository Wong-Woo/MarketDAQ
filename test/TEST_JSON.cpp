#include <iostream>
#include <fstream>
#include "single_include/nlohmann/json.hpp"
#include "config.h"

int main()
{
    std::ifstream file("data/stock/AAPL.json");
    if (!file)
        std::cerr << "파일을 열 수 없습니다!" << std::endl;

    nlohmann::json aapl_json;
    file >> aapl_json;
    std::cout << "JSON 데이터:\n" << aapl_json.dump(4) << std::endl;

    return 0;
}