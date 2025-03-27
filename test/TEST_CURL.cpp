#include <iostream>
#include <fstream>
#include <string>
#include <curl/curl.h>

// curl 콜백 함수: 데이터를 받아서 처리하는 함수
size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

// 주식 데이터 요청 함수
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
    std::string api_key = "YOUR_API_KEY";  // Alpha Vantage API 키
    std::string url = "https://www.alphavantage.co/query?function=TIME_SERIES_DAILY&symbol=" + symbol + "&apikey=" + api_key;

    std::string response_data;
    
    // 주식 데이터 요청
    if (getStockData(url, response_data)) {
        std::cout << "Data received successfully!\n";

        // JSON 형식의 데이터를 그대로 파일에 저장
        std::ofstream outfile("stock_data.json");
        if (outfile.is_open()) {
            outfile << response_data;  // JSON 데이터 그대로 저장
            outfile.close();
            std::cout << "JSON data saved to stock_data.json!" << std::endl;
        } else {
            std::cerr << "Unable to open file for writing." << std::endl;
        }
    } else {
        std::cerr << "Failed to fetch data.\n";
    }

    return 0;
}
