#include <iostream>
#include "helper.hpp"

int main() {
    #ifdef DEBUG_MODE
    std::cout << "[Debug] 模組化模式已啟動！" << std::endl;
    #endif
    say_hello();
    return 0;
}
