#include <iostream>
#include <fstream>
#include <filesystem>

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
    std::string line;
    while (std::getline(test_aapl, line))
    {
        std::cout << line << std::endl;
    }
    test_aapl.close();

    // PATH 편집 테스트
    std::string test_path("data/stock");
    if (test_path.back() != '/') test_path.push_back('/');
    std::cout << test_path << std::endl;
    
    //
    std::cout << "Path separator: " << std::filesystem::path::preferred_separator << std::endl;
    return 0;
}