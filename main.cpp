#include <iostream>

int main() {
    #ifdef DEBUG_MODE
    std::cout << "[Debug] 偵錯模式已開啟！" << std::endl;
    #endif

    std::cout << "Hello, Meson!" << std::endl;
    return 0;
}
