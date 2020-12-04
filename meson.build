project('LemonUtils')

add_languages('c', 'cpp')

cat_src = [
    'utils/cat.cpp',
]

echo_src = [
    'utils/echo.cpp',
]

ls_src = [
    'utils/ls.cpp',
]

rm_src = [
    'utils/rm.cpp',
]

uname_src = [
    'utils/uname.cpp',
]

hexdump_src = [
    'utils/hexdump.cpp',
]

ps_src = [
    'utils/ps.cpp',
]

utils_cpp_args = [
    '-Wno-unused-parameter',
]

add_project_arguments(utils_cpp_args, language : 'cpp')

executable('cat.lef', cat_src, cpp_args : utils_cpp_args, install : true)
executable('echo.lef', echo_src, cpp_args : utils_cpp_args, install : true)
executable('rm.lef', rm_src, cpp_args : utils_cpp_args, install : true)
executable('ls.lef', ls_src, cpp_args : utils_cpp_args, install : true)
executable('uname.lef', uname_src, cpp_args : utils_cpp_args, install : true)
executable('hexdump.lef', hexdump_src, cpp_args : utils_cpp_args, install : true)
executable('ps.lef', ps_src, cpp_args : utils_cpp_args, link_args : [ '-llemon' ], install : true)
