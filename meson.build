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

executable('cat.lef', cat_src, install : true)
executable('echo.lef', echo_src, install : true)
executable('rm.lef', rm_src, install : true)
executable('ls.lef', ls_src, link_args : ['-llemon'], install : true)