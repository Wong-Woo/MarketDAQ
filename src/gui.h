void plot_window();
void select_window();
void news_window();

class BaseWindow{
public:
    std::string name;
    float width, height;
    bool is_open;

    BaseWindow();
};