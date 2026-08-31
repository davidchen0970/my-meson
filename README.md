# my-meson

一個用 **Meson + Ninja** 建置的 C++ 範例專案。它展示了一套小而完整的 modern C++ 專案該有的基本樣貌：

- 乾淨的模組化結構（`src/` + `include/`）
- 透過 **WrapDB** 管理第三方依賴（`nlohmann_json`）
- 可透過 Meson option 切換的建置選項（debug 模式）
- 內建的整合測試（`meson test`）
- GitHub CI： Linux / Windows MinGW 交叉編譯，並在打上 `v*` tag 時自動 release

## 主要功能

| 功能 | 說明 |
| ---- | ---- |
| 建置系統 | Meson + Ninja |
| 語言標準 | C++（使用 gcc） |
| JSON 依賴 | `nlohmann_json`，從 WrapDB 自動取得 |
| 模組化 | `helper` 模組，header 放在 `include/` |
| 除錯選項 | `-Denable_debug=true` 會定義 `DEBUG_MODE` |
| 測試 | `meson test` 跑基本整合測試 |
| CI | Linux 原生 + Windows MinGW 交叉編譯 |
| Release | 標籤 `v*` 自動附上二進位檔 |

## 環境需求

- **Meson**（≥ 1.0）
- **Ninja**
- 一個 C++ 編譯器（Linux 用 `g++`，Windows 目標用 MinGW-w64）

Ubuntu 安裝範例：

```bash
sudo apt-get install -y meson ninja-build
```

## 建置與執行

首次需要先取得 `nlohmann_json` 的 Wrap 依賴（需要網路，WrapDB）：

```bash
mkdir -p subprojects
meson wrap install nlohmann_json
```

建立建置目錄並編譯：

```bash
meson setup build -Denable_debug=true
meson compile -C build
```

執行產物：

```bash
./build/src/hello
```

預期輸出（debug 開啟時）：

```bash
[Debug] JSON 測試模式已啟動！
Hello from helper module!
Generated JSON:
{
    "features": [
        "debug",
        "modular",
        "fast"
    ],
    "project": "Meson Demo",
    "version": 1.0
}
```

## 建置選項

| Option | 型別 | 預設值 | 說明 |
| ------ | ---- | ----- | ---- |
| `enable_debug` | boolean | `true` | 開啟時會加上 `-DDEBUG_MODE` 給編譯器 |

設定方法：

```bash
meson setup build -Denable_debug=true    # 開啟
meson setup build -Denable_debug=false   # 關閉
```

開啟時，`main.cpp` 內以 `#ifdef DEBUG_MODE` 包住的 JSON 測試訊息才會印出。

## 資料夾結構

```
├── include/          # 公開標頭檔
│   └── helper.hpp
├── src/              # source code
│   ├── main.cpp
│   ├── helper.cpp
│   └── meson.build   # 定義 executable 與 test
├── meson.build       # 專案 root 建置檔
├── meson_options.txt # 宣告 build option
├── .github/
│   └── workflows/
│       └── build.yml # CI / Release 工作流
└── README.md
```

`src/meson.build` 透過 `subdir('src')` 被根目錄的 `meson.build` 引用，並用 `include_directories('include')` 注入全域 include path。

## 依賴管理（WrapDB）

`meson.build` 中：

```meson
json_dep = dependency('nlohmann_json',
                     fallback : ['nlohmann_json', 'nlohmann_json_dep'])
```

`fallback` 的意思是：先去系統裡找 `pkg-config`/`cmake` 有沒有裝這套件；**若沒有，就自動從 WrapDB 下載編譯**。你也可以手動執行：

```bash
meson wrap install nlohmann_json
```

這樣會在 `subprojects/` 產生 `.wrap` 檔，讓專案在離線或 CI 環境也能重現。

## 測試

```bash
meson test -C build
```

目前定義的測試在 `src/meson.build`：

```meson
test('basic_json_test', hello_exe)
```

它執行 `hello` 程式，只要程式正常結束（回傳 0）即視為通過。

## CI 與發佈

`.github/workflows/build.yml` 在每次 push / PR 時會：

1. 安裝 Meson、Ninja 與 Wrap 依賴
2. 建置 **Linux** 原生執行檔
3. 用 MinGW-w64 交叉編譯 **Windows** 執行檔
4. 兩者壓縮成 zip 上傳為 artifact

當你**推送一個 `v*` tag**（例如 `v1.0.0`）時，還會自動建立 GitHub Release：

```bash
git tag -a v1.0.0 -m "release v1.0.0"
git push origin v1.0.0
```

## Windows 交叉編譯（本機操作）

CI 內使用一份 cross-file 來告訴 Meson 要用 `x86_64-w64-mingw32-*` 系列工具。本機操作需先安裝 MinGW：

```bash
sudo apt-get install -y mingw-w64
```

之後用 `--cross-file` 建立建置目錄，即可產出 `hello.exe`。

## Troubleshooting

**「neither a subproject directory nor a nlohmann_json.wrap file was found」**
表示 `subprojects/` 還沒有 Wrap 檔，先執行 `meson wrap install nlohmann_json`（需要網路）。

**「The source directory is the current directory」或其他 Meson 設定錯誤**
Meson 不允許在 source 目錄內直接建置，永遠要在獨立資料夾（如 `build/`）跑 `meson setup`。
