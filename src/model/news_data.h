#include <string>
#include <queue>

class NewsData{
    std::string title;
    std::string content;
    uint64_t last_updated_timestamp;
};

class NewsDataBase {
public:
    std::queue<NewsData> news_data;
};