#include <functional>
#include <string>
class Update_Text {
private:
    std::function<std::string(void)> update_func;

public:
    Update_Text(std::function<std::string(void)> f) { update_func = f; }
    inline std::string get_text() const { return update_func(); }
};