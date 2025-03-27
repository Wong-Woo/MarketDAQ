#include <iostream>
#include <fstream>
#include <string>
#include <curl/curl.h>

// 콜백 함수: HTTP 응답을 받아서 처리하는 함수
size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

bool getStockData(const std::string& url, std::string& response_data) {
    CURL* curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);
        res = curl_easy_perform(curl);

        if(res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
            curl_easy_cleanup(curl);
            curl_global_cleanup();
            return false;
        }

        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
    return true;
}

int main() {
    std::string symbol = "AAPL";  // 예시로 Apple 주식 코드
    std::string api_key = "your key";  // Alpha Vantage API 키
    std::string url = "https://www.alphavantage.co/query?function=TIME_SERIES_DAILY&symbol=" + symbol + "&apikey=" + api_key;

    std::string response_data;
    
    // 주식 데이터 요청
    if (getStockData(url, response_data)) {
        std::cout << "Data received successfully!\n";
        
        // CSV 파일로 저장
        std::ofstream outfile("stock_data.csv");

        if (outfile.is_open()) {
            // 간단한 CSV 헤더 추가
            outfile << "Date,Open,High,Low,Close,Volume\n";

            // 예시로 JSON 파싱 후 CSV로 저장하는 방법
            // Alpha Vantage API에서 JSON 형식으로 데이터를 반환하므로 실제 JSON 파싱 라이브러리인 
            // nlohmann/json 같은 라이브러리를 사용하여 데이터를 파싱한 후 CSV로 변환합니다.
            // 여기서는 데이터 파싱을 생략한 간단한 예시입니다.
            
            outfile << "2025-03-26,140,145,139,142,1000000\n";
            outfile << "2025-03-25,138,143,137,141,1100000\n";

            outfile.close();
            std::cout << "CSV file saved successfully!\n";
        } else {
            std::cerr << "Unable to open file for writing.\n";
        }
    } else {
        std::cerr << "Failed to fetch data.\n";
    }

    return 0;
}
