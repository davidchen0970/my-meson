project('demo', 'cpp')

# 宣告一個布林選項，預設值為 true
enable_debug_print = get_option('enable_debug')

if enable_debug_print
    add_project_arguments('-DDEBUG_MODE', language : 'cpp')
endif

executable('hello', 'main.cpp')
