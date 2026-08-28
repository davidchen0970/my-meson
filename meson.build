project('demo', 'cpp', version : '1.0.0')

enable_debug_print = get_option('enable_debug')
if enable_debug_print
    add_project_arguments('-DDEBUG_MODE', language : 'cpp')
endif

global_inc = include_directories('include')

# --- 引入 nlohmann_json 依賴 ---
# fallback 的意思是：「先去系統裡找找看有沒有安裝這套件；如果沒有，就去 Meson WrapDB 自動下載編譯」
json_dep = dependency('nlohmann_json', fallback : ['nlohmann_json', 'nlohmann_json_dep'])

subdir('src')
