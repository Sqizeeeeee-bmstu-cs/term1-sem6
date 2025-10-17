#include "helpers.h"


int main() {
    std::string s = "<div> </div> <p> </p>";

    try {
        bool res = task1(s);
        std::cout <<std::boolalpha << res << "\n";
    }
    catch (const std::exception& e) {
        std::cout << "false " << "Ошибка: " << e.what() << std::endl;
    }
}