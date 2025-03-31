#include <iostream>
#include <fstream>
#include <filesystem>
#include "single_include/nlohmann/json.hpp"

int main(int argc, char *argv[])
{
    // 프로그램 실행 인자 테스트
    std::cout << argc << std::endl;
    for (int i = 0; i < argc; i++)
    {
        std::cout << argv[i] << std::endl;
    }

    // FSTREAM 테스트
    std::ifstream test_aapl("data/stock/AAPL.json");
    if (!test_aapl)
    {
        std::cerr << "파일을 찾을 수 없음" << std::endl;
        return -1;
    }
    std::stringstream content;
    content << test_aapl.rdbuf();
    std::cout << content.str();

    // PATH 편집 테스트
    std::string test_path("data/stock");
    if (test_path.back() != '/') test_path.push_back('/');
    std::cout << test_path << std::endl;
    
    // Path separator 테스트
    std::cout << "Path separator: " << std::filesystem::path::preferred_separator << std::endl;

    return 0;
}