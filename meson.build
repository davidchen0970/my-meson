project('demo', 'cpp', version : '1.0.0')

enable_debug_print = get_option('enable_debug')
if enable_debug_print
    add_project_arguments('-DDEBUG_MODE', language : 'cpp')
endif

# 全域宣告 include 目錄並宣告為變數
global_inc = include_directories('include')

subdir('src')