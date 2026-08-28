#include <iostream>
#include <nlohmann/json.hpp>
#include "helper.hpp"

// 簡化命名空間
using json = nlohmann::json;

int main() {
    #ifdef DEBUG_MODE
    std::cout << "[Debug] JSON 測試模式已啟動！" << std::endl;
    #endif

    say_hello();

    // 建立一個 JSON 物件
    json j;
    j["project"] = "Meson Demo";
    j["version"] = 1.0;
    j["features"] = {"debug", "modular", "fast"};

    // 印出格式化後的 JSON 字串
    std::cout << "Generated JSON:\n" << j.dump(4) << std::endl;

    return 0;
}
