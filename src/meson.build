hello_exe = executable('hello',
             ['main.cpp', 'helper.cpp'],
             include_directories : global_inc,
             dependencies : json_dep,
             install : true)

test('basic_json_test', hello_exe)